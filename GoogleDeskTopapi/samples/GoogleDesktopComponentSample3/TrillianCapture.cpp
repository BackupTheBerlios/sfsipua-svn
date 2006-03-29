// Copyright 2005 Google Inc.
// All Rights Reserved.
// 
// Sample Google Desktop plug-in for Trillian
//
#include "stdafx.h"
#include <atlstr.h>
#include <atlsafe.h>
#include <atlcoll.h>
#include <shobjidl.h>
#include <shlguid.h>
#include "plugin.h"

// This CLSID is used when interfacing with Google Desktop
const CLSID CLSID_ITrillianCapture = {0x5b4de43e,0x8104,0x4a56,{0x84,0x68,0x55,0xd1,0x67,0xfb,0x5c,0x31}};

// This GUID is used when interfacing with Trillian
#define TRILLIAN_PLUGIN_GUID "DB784D5C-813B-4083-9C27-E250F00C7C33"

// Some globals
int g_broadcast_id = -1;
plugin_function_send g_plugin_send = NULL;
HINSTANCE g_hinst = NULL;

// Needed so that when we have an outgoing message we can look up a buddy's nickname from their username
CSimpleMap<CStringW, CStringW> g_buddy_username_to_nickname;

// Needed so that when we have an incoming message, we can look up the nickname associated with that medium
CSimpleMap<CStringW, CStringW> g_connection_to_user_nickname;

// Forward declaration of Trillian callbacks
int broadCallback(int windowID, char *subwindow, char *event, void *data, void *userData);
int contactCallback(int windowID, char *subwindow, char *event, void *data, void *userData);

// Register the plugin with Google Desktop.
// This should only be done once, not each time this plugin starts.
HRESULT RegisterPlugin() {
  // Create our icon path 
  CStringW module_name;
  CStringW icon_name;
  ::GetModuleFileNameW(g_hinst, CStrBufW(module_name, 1024), 1023);
  icon_name.Format(L"%ls,%d", module_name, IDI_REGISTRATIONICON);

  return RegisterIndexingComponentHelper(CLSID_ITrillianCapture, 
                                         L"Trillian IM", 
                                         L"Indexes chat conversations", 
                                         icon_name, 0, NULL);
}

int WINAPI DllMain(HINSTANCE hinstDLL, unsigned long dwReason, void *reserved) {
  g_hinst = hinstDLL;
  return 1;
}

void __declspec( dllexport )unload();

int __declspec(dllexport)plugin_version(void) {
  return 2;
}
 
int __declspec(dllexport)plugin_main(char *event, void *data) {
  if (!_stricmp(event,"load")) {
    struct plugin_info_t *pi = (struct plugin_info_t *)data;
    if (pi) {
      // Fill in plugin information for Trillian
      lstrcpynA(pi->guid, TRILLIAN_PLUGIN_GUID, sizeof(pi->guid)); 
      lstrcpynA(pi->name, "Google Desktop", sizeof(pi->name)); 
      lstrcpynA(pi->company, "Google Inc.", sizeof(pi->company)); 
      lstrcpynA(pi->version, "1.0", sizeof(pi->version)); 
      lstrcpynA(pi->description, "Indexes chat conversations", sizeof(pi->description));

      g_plugin_send = pi->plugin_send; 
    }
  } else if (!_stricmp(event, "initialLoad")) {
    // This is a callback, so we don't know if the calling thread has initialized COM or not.
    HRESULT hr_coinit = CoInitialize(NULL);
    if (FAILED(hr_coinit) && hr_coinit != RPC_E_CHANGED_MODE)
      return 0;

    RegisterPlugin();
    if (SUCCEEDED(hr_coinit))
      CoUninitialize();
  } else if (!_stricmp(event, "finalUnload")) {
    HRESULT hr_coinit = CoInitialize(NULL);
    if (FAILED(hr_coinit) && hr_coinit != RPC_E_CHANGED_MODE)
      return 0;

    // Unregister our component with GDS
    HRESULT hr = UnregisterComponentHelper(CLSID_ITrillianCapture);

    if (SUCCEEDED(hr_coinit))
      CoUninitialize();
  } else if (!_stricmp(event, "start")) {
    // This gets called each time our plugin starts.  We will do two things:
    // First, find out the nickname of each buddy so we can include it with our events.
    // Second, ask Trillian to notify us whenever a message gets sent so we can index it.
    struct message_broadcast_t mbt;
    struct contactlist_enum_t cle;
    trillianInitialize(mbt);
    trillianInitialize(cle);

    cle.medium = "all";
    cle.connection_id = -1;
    cle.callback = contactCallback;
    g_plugin_send(TRILLIAN_PLUGIN_GUID, "contactlistEnumerate", &cle);

    if (g_broadcast_id == -1) {
      mbt.callback = broadCallback;
      g_broadcast_id = g_plugin_send(TRILLIAN_PLUGIN_GUID, "messageBroadcastEnable", &mbt);
    }
  } else if (!_stricmp(event,"stop") && g_plugin_send) {
    // When the plugin is stopped (ie Trillian is shutting down, or we're being uninstalled),
    // we need to tell Trillian to stop giving us message notifications.
    struct message_broadcast_t mbt;
    trillianInitialize(mbt);
    mbt.broadcast_id = g_broadcast_id;
    g_plugin_send(TRILLIAN_PLUGIN_GUID, "messageBroadcastDisable", &mbt);
    g_broadcast_id = -1;
  } else if (!_stricmp(event, "unload")) {
    g_plugin_send = NULL;
    return 0;
  }

  return 0;
}

int contactCallback(int windowID, char *subwindow, char *event, void *data, void *userData) {
  // Here we build a mapping between the usernames (i.e. joe@msn.com) and nicknames (i.e. Joe) of
  // buddies.  We use this data to set the buddy's nickname for outgoing messages.
  struct contactlist_entry_t *entry = (struct contactlist_entry_t *)data;
  if (!strcmp(event, "enum_add")) {
    g_buddy_username_to_nickname.Add(CStringW(entry->real_name) + CStringW(entry->medium), CStringW(entry->name));
  }

  return 0;
}

int broadCallback(int windowID, char *subwindow, char *event, void *data, void *userData){
  struct message_t *msg = (struct message_t *)data;

  if (!strcmp(event, "message_broadcast")) {
    HRESULT hr_coinit = CoInitialize(NULL);
    if (FAILED(hr_coinit) && hr_coinit != RPC_E_CHANGED_MODE)
      return 0;

    CStringW user_nickname, buddy, type(msg->type), medium(msg->medium);

    if (type.Find(_T("incoming")) != -1) {
      // On incoming messages we get a buddy's nickname and username.  Let's add it to our map
      // if it's not there already (i.e. if the buddy logged on/changed their nickname after we
      // enumerated the contacts).  We'll use it next time the user sends a message to this
      // buddy because Trillian doesn't give us the buddy's nickname then.
      CStringW buddy_username_with_medium(CStringW(msg->name) + medium);
      buddy = msg->display_name;
      if (g_buddy_username_to_nickname.FindKey(buddy_username_with_medium) == -1)
        g_buddy_username_to_nickname.Add(buddy_username_with_medium, buddy);

      // Get the user's nickname if we have it for this connection.  If we don't have it yet,
      // we can set it in future events.
      int index = g_connection_to_user_nickname.FindKey(medium);
      if (index != -1)
        user_nickname = g_connection_to_user_nickname.GetValueAt(index);
    } else if (type.Find(_T("outgoing")) != -1) {
      // On outgoing messages we have the user's nickname.  Add it to our map.
      user_nickname = msg->display_name;
      if (g_connection_to_user_nickname.FindKey(medium) == -1)
        g_connection_to_user_nickname.Add(medium, user_nickname);      

      // Trillian doesn't give us the buddy's nickname.  Let's see if we have it from our contact
      // enumeration or from previous incoming messages.  If not, we'll have to use the buddy's
      // username.  This is non-ideal, because then the conversation will be split up once we get
      // the nickname.  This should be rare though.
      int index = g_buddy_username_to_nickname.FindKey(CStringW(msg->name) + medium);
      if (index != -1) {
        buddy = g_buddy_username_to_nickname.GetValueAt(index);
      } else {
        buddy = CStringW(msg->name);
      }
    } else {
      // information message (ie from Trillian), we don't care about it so don't index it
      return 0;
    }

    // The native content for IMs needs to be: [sender's name]: [message text]
    CStringW conversation = CStringW(msg->display_name) + _T(": ") + CStringW(msg->text);

    // Open a new scope to ensure local com pointers are destroyed before CoUninitialize()
    {
      CComPtr<IGoogleDesktopEventFactory> spFactory;
      HRESULT hr = spFactory.CoCreateInstance(CLSID_GoogleDesktop, NULL, CLSCTX_INPROC);
      if (FAILED(hr))
        return 0;

      CComPtr<IDispatch> spEventDisp;
      hr = spFactory->CreateEvent(CComBSTR(CLSID_ITrillianCapture), CComBSTR(L"Google.Desktop.IM"), &spEventDisp);
      if (hr == E_COMPONENT_NOT_REGISTERED) {
        // GDS doesn't know about our component.  This could happen if the user uninstalled and then installed GDS.
        // So let's register our component again.
        RegisterPlugin();
        hr = spFactory->CreateEvent(CComBSTR(CLSID_ITrillianCapture), CComBSTR(L"Google.Desktop.IM"), &spEventDisp);
      }

      if (FAILED(hr))
        return 0;
      
      CComQIPtr<IGoogleDesktopEvent> spEvent(spEventDisp);
      ATLASSERT(spEventDisp && spEvent);
      if (spEvent == NULL)
        return 0;

      // Set the message time to be right now
      double varDate;
      SYSTEMTIME time_now;
      GetSystemTime(&time_now);
      SystemTimeToVariantTime(&time_now, &varDate);

      if (SUCCEEDED(hr))
        hr = spEvent->AddProperty(CComBSTR(L"message_time"), CComVariant(varDate, VT_DATE));

      if (SUCCEEDED(hr))
        hr = spEvent->AddProperty(CComBSTR(L"format"), CComVariant("text/html"));

      if (SUCCEEDED(hr))
        hr = spEvent->AddProperty(CComBSTR(L"content"), CComVariant(conversation));

      // Set buddyname.
      if (SUCCEEDED(hr))
          hr = spEvent->AddProperty(CComBSTR(L"buddy_name"), CComVariant(buddy));

      // set a title (optional) - if not present one will be generated by GDS
      if (SUCCEEDED(hr))
        hr = spEvent->AddProperty(CComBSTR(L"title"), CComVariant(buddy));

      // GDS will use this identifier to figure out if we should label this as a new conversation.  
      // If a unique conversation identifier is available (e.g. the handle for the IM conversation window)
      // set it here, otherwise don't set this property.
      int hwnd = msg->window_id;
      if (SUCCEEDED(hr))
        hr = spEvent->AddProperty(CComBSTR(L"conversation_id"), CComVariant(hwnd));

      // set the username (myself) if we have it
      if (SUCCEEDED(hr) && !user_nickname.IsEmpty())
        hr = spEvent->AddProperty(CComBSTR(L"user_name"), CComVariant(user_nickname));

      if (FAILED(hr))
        return 0;

      // send the indexable event
      hr = spEvent->Send(EventFlagIndexable);
      if (FAILED(hr))
        return 0;
    }

    if (SUCCEEDED(hr_coinit))
      CoUninitialize();
  }

  return 0;
}
