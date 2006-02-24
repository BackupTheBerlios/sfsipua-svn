/*++

Copyright © Microsoft Corporation

Module Name:

    RTCPresenceCore.cs

Abstract:

    This module utilizes the RTC platform presence functionality. It provides
    methods for UI to set local presence, add, remove, or poll buddy. It
    also sends messages to UI if there is new presence information.
	
--*/

////////////
//
// Begin RTC Functionality Code
//
// This code demonstrates Logging on/off and Add/Remove/Poll Buddy
//
////////////

using System;
using System.Collections;
using System.Text;
using System.Text.RegularExpressions;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.ComponentModel;
using System.Drawing;
using RTCCore;


namespace Microsoft.Rtc.Sdk.Samples.RtcPresence
{
    class RTCPresenceCore
    {
        #region Fields
        private RTCClientClass client;
        private IRTCProfile2 profile;
        private bool presenceEnabled;
        private RTC_REGISTRATION_STATE registrationState;
        private IRTCPresenceUI presenceUI;
        #endregion

        public RTCPresenceCore(IRTCPresenceUI presenceUI)
        {
            Trace.WriteLine("Entering RTCPresenceCore.RTCPresenceCore");

            this.presenceUI = presenceUI;
            this.presenceEnabled = false;
            this.registrationState = RTC_REGISTRATION_STATE.RTCRS_NOT_REGISTERED;

            try
            {
                this.client = new RTCClientClass();

                this.client.Initialize();

                // Set the event filter
                this.client.EventFilter = RTCConst.RTCEF_REGISTRATION_STATE_CHANGE |
                    RTCConst.RTCEF_CLIENT |
                    RTCConst.RTCEF_BUDDY |
                    RTCConst.RTCEF_BUDDY2 |
                    RTCConst.RTCEF_WATCHER |
                    RTCConst.RTCEF_WATCHER2 |
                    RTCConst.RTCEF_ROAMING |
                    RTCConst.RTCEF_PROFILE |
                    RTCConst.RTCEF_PRESENCE_PROPERTY | 
                    RTCConst.RTCEF_PRESENCE_DATA;

                this.client.IRTCEventNotification_Event_Event += new IRTCEventNotification_EventEventHandler(OnRTCEvent);

                this.client.ClientName = "RTCPresence";
                this.client.ClientCurVer = "1.0";

                // Don't Initialize presence status -- exception if called
                // RTC_E_PRESENCE_NOT_ENABLED 0x80EE0028L
                //DoSetPresence(RTC_PRESENCE_STATUS.RTCXS_PRESENCE_ONLINE);
            }
            catch(COMException ex1COM)
            {
                Trace.WriteLine("COMException " + ex1COM.Message); 
                    
                throw;
            }
        }

        public void DoAddBuddy(string uri)
        {
            Trace.WriteLine("Entering RTCPresenceCore.DoAddBuddy");

            if (uri == null || uri.Length == 0)
            {
                return;
            }

            try 
            {
                IRTCBuddy2 buddy2 = (IRTCBuddy2) this.client.get_Buddy(uri);

                try
                {
                    if (buddy2.SubscriptionType == RTC_BUDDY_SUBSCRIPTION_TYPE.RTCBT_SUBSCRIBED)
                    {
                        //the buddy is already subscribed
                        return;
                    }

                    //the buddy exists, but not subscribed
                    //we should remove the buddy. we then subscribe to it
                    this.DoRemoveBuddy(buddy2);
                }
                catch (COMException ex1COM)
                {
                    Trace.WriteLine("COMException " + ex1COM.Message); 
                }
            }
            catch(COMException)
            {
            }

            try 
            {
                //the returned buddy2 won't have correct presence status
                this.client.AddBuddyEx(
                    uri,
                    null,
                    null,
                    true, 
                    RTC_BUDDY_SUBSCRIPTION_TYPE.RTCBT_SUBSCRIBED,
                    profile,
                    0);
            }
            catch(COMException ex1COM)
            {
                Trace.WriteLine("COMException " + ex1COM.Message); 
            }
        }

        public bool DoShutdown( )
        {
            Trace.WriteLine("Entering RTCPresenceCore.DoShutdown");

            if (this.client != null)
            {
                this.client.PrepareForShutdown();

                //the UI should wait for shutdown
                return true;
            }

            return false;
        }
        public void DoLogOff()
        {
            Trace.WriteLine("Entering RTCPresenceCore.DoLogOff");

            if (this.profile == null)
            {
                this.DoDisablePresence();
                this.presenceUI.OnLoggedOff();
                return;
            }

            this.client.DisableProfile(profile);

            this.profile = null;
        }

        public void DoLogOn(AuthData authData)
        {
            Trace.WriteLine("Entering RTCPresenceCore.DoLogOn");

            if (authData == null || !authData.IsValid())
            {
                this.presenceUI.OnLoggedOff();
                return;
            }

            if (this.profile != null)
            {
                Trace.WriteLine("Already logged on");
                return;
            }

            Trace.WriteLine(authData);

            int lTransport = 0;

            try
            {
                if (authData.Transport != null)
                {
                    if (authData.Transport == "UDP")
                    {
                        lTransport = RTCConst.RTCTR_UDP;
                    }
                    else if (authData.Transport == "TCP")
                    {
                        lTransport = RTCConst.RTCTR_TCP;
                    }
                    else if (authData.Transport == "TLS")
                    {
                        lTransport = RTCConst.RTCTR_TLS;
                    }
                }

                this.client.GetProfile(
                    null,           // bstrUserAccount
                    null,           // bstrUserPassword
                    authData.Uri,        // bstrUserURI
                    authData.Server,     // bstrServer
                    lTransport,     // lTransport
                    0               // lCookie
                    );
            }
            catch (COMException ex1COM)
            {
                Trace.WriteLine("COMException " + ex1COM.Message); 
                    
                this.presenceUI.OnLoggedOff();
            }
        }

        public void DoPollBuddy(string uri)
        {
            Trace.WriteLine("Entering RTCPresenceCore.RTCPresenceCore.DoPollBuddy");
            Trace.WriteLine("URI = " + uri);

            if (uri == null || uri.Length == 0)
            {
                return;
            }

            IRTCBuddy2 buddy2 = null;
                
            try 
            {
                buddy2 = (IRTCBuddy2) this.client.get_Buddy(uri);

                try
                {
                    if (buddy2.SubscriptionType == RTC_BUDDY_SUBSCRIPTION_TYPE.RTCBT_POLL)
                    {
                        //this will cause RTC_BUDDY_EVENT_TYPE.RTCBET_BUDDY_STATE_CHANGE
                        //we will then update buddy presence state
                        buddy2.Refresh();
                    }
                    else
                    {
                        //the buddy is a subscribed buddy. its presence status is up to date
                        this.presenceUI.UpdateBuddy(buddy2);
                    }
                }
                catch (COMException ex1COM)
                {
                    Trace.WriteLine("COMException " + ex1COM.Message); 
                }
            }
            catch(COMException ex1COM)
            {
                Trace.WriteLine("COMException " + ex1COM.Message); 
                    
                try 
                {
                    //the buddy doesn't exist. we should add it as a poll buddy.
                    buddy2 = this.client.AddBuddyEx(
                        uri,
                        null,
                        null,
                        false, 
                        RTC_BUDDY_SUBSCRIPTION_TYPE.RTCBT_POLL,
                        profile,
                        0);
                }
                catch (COMException ex2COM)
                {
                    Trace.WriteLine("COMException " + ex2COM.Message); 
                }
            }

            //buddy2 will not contain useful information. so we don't return it
        }

        public void DoRemoveBuddy(IRTCBuddy buddy)
        {
            Trace.WriteLine("Entering RTCPresenceCore.DoRemoveBuddy"); 

            this.client.RemoveBuddy(buddy);
        }

        public void DoSetPresence(RTC_PRESENCE_STATUS presenceStatus)
        {
            Trace.WriteLine("Entering RTCPresenceCore.DoSetPresence");
            this.client.SetLocalPresenceInfo(presenceStatus, null);
        }

        public string GetUserURI()
        {
            if (profile != null)
            {
                return profile.UserURI;
            }

            return null;
        }

        void DoAuth(string uri, string account, string password)
        {
            Trace.WriteLine("Entering RTCPresenceCore.DoAuth");

            Trace.WriteLine("URI       " + uri );
            Trace.WriteLine("ACCOUNT   " + account );
            Trace.WriteLine("PASSWORD " + password );

            this.profile.SetCredentials(uri, account, password);

            this.DoRegister();
        }

        void DoDisablePresence()
        {    
            Trace.WriteLine("Entering RTCPresenceCore.DoDisablePresence");

            this.presenceUI.ClearBuddyList();

            if (presenceEnabled == false)
            {
                return;
            }

            this.client.DisablePresence();
            this.presenceEnabled = false;
        }

        void DoEnablePresence()
        {    
            Trace.WriteLine("Entering RTCPresenceCore.DoEnablePresence");

            this.presenceUI.ClearBuddyList();

            if (this.presenceEnabled == true)
            {
                return;
            }

            // Build the filename for presence storage
            // Replace all non-alphanumeric characters
            // in the URI with underscore
            string uri = Regex.Replace(profile.UserURI, @"\W", "_");
            StringBuilder sb = new StringBuilder();
            sb.Append("rtcpresence_").Append(uri).Append(".xml");

            // Enable presence
            this.client.EnablePresenceEx(profile, sb.ToString(), 0);

            // Set a presence property
            string name = "http://schemas.microsoft.com/rtc/rtcpresence";
            string val = "<name> rtcpresence </rtcpresence>";
            this.client.SetPresenceData(name, val);
		
            string deviceName = System.Environment.MachineName + " (RTCPresence)";
            this.client.set_PresenceProperty(RTC_PRESENCE_PROPERTY.RTCPP_DEVICE_NAME, deviceName);

            Trace.WriteLine("Enable Presence file=" + sb.ToString() + " device="+deviceName);

            this.client.OfferWatcherMode =  RTC_OFFER_WATCHER_MODE.RTCOWM_AUTOMATICALLY_ADD_WATCHER;
            this.presenceEnabled = true;
        }

        void DoRegister()
        {
            Trace.WriteLine("Entering RTCPresenceCore.DoRegister");

            this.DoEnablePresence();

            this.client.EnableProfileEx(profile, 
                RTCConst.RTCRF_REGISTER_ALL, 
                RTCConst.RTCRMF_BUDDY_ROAMING |
                RTCConst.RTCRMF_WATCHER_ROAMING |
                RTCConst.RTCRMF_PRESENCE_ROAMING |
                RTCConst.RTCRMF_PROFILE_ROAMING
                );
}

        void OnRTCBuddyEvent(IRTCBuddyEvent2 buddyEvent)
        {
            Trace.WriteLine("Entering RTCPresenceCore.OnRTCBuddyEvent  " + 
                buddyEvent.EventType);

            int statusCode = buddyEvent.StatusCode;

            IRTCBuddy2 buddy2 = (IRTCBuddy2) buddyEvent.Buddy;

            switch (buddyEvent.EventType)
            {
                case RTC_BUDDY_EVENT_TYPE.RTCBET_BUDDY_ADD:
                    //This buddy's properties have been added.
                    if (RTCHelp.IsSucceeded(statusCode))
                    {
                        this.presenceUI.UpdateBuddy(buddy2);
                    }
                    break;

                case RTC_BUDDY_EVENT_TYPE.RTCBET_BUDDY_REMOVE:
                    //This buddy has been successfully removed from the buddy list.
                    this.presenceUI.RemoveBuddy(buddy2);
                    break;

                case RTC_BUDDY_EVENT_TYPE.RTCBET_BUDDY_UPDATE:
                    //This buddy's properties have been updated. -- ignore
                    break;

                case RTC_BUDDY_EVENT_TYPE.RTCBET_BUDDY_SUBSCRIBED:
                    //This buddy's presence information is subscribed to -- ignore
                    break;

                case RTC_BUDDY_EVENT_TYPE.RTCBET_BUDDY_STATE_CHANGE:
                    //This buddy's presence state has changed.
                    this.presenceUI.UpdateBuddy(buddy2);
                    break;

                default:
                    break;
            }
        }

        void OnRTCClientEvent(IRTCClientEvent clientEvent)
        {
            Trace.WriteLine("Enter OnRTCClientEvent  " + clientEvent.EventType);

            RTC_CLIENT_EVENT_TYPE eventType = clientEvent.EventType;

            if ( eventType == RTC_CLIENT_EVENT_TYPE.RTCCET_ASYNC_CLEANUP_DONE )
            {
                // The RTC client has finished preparing for shutdown.
                this.profile = null;

                if (this.client != null)
                {
                    // Unadvise for events from the RTC client
                    this.client.IRTCEventNotification_Event_Event -= new IRTCEventNotification_EventEventHandler(OnRTCEvent);
                    this.client.Shutdown();
                    this.client = null;
                }
                this.presenceUI.CloseUI();
            }
        }

        void OnRTCEvent(RTC_EVENT rtcEventType, object rtcEvent)
        {
            Trace.WriteLine("Entering RTCPresenceCore.OnRTCEvent " + rtcEventType);
            switch (rtcEventType)
            {
                case RTC_EVENT.RTCE_REGISTRATION_STATE_CHANGE:
                    this.OnRTCRegistrationStateChangeEvent((IRTCRegistrationStateChangeEvent) rtcEvent);
                    break;

                case RTC_EVENT.RTCE_CLIENT:
                    this.OnRTCClientEvent((IRTCClientEvent)rtcEvent);
                    break;
                    
                case RTC_EVENT.RTCE_BUDDY:
                    this.OnRTCBuddyEvent((IRTCBuddyEvent2)rtcEvent);
                    break;
                    
                case RTC_EVENT.RTCE_ROAMING:
                    break;
                    
                case RTC_EVENT.RTCE_PROFILE:
                    this.OnRTCProfileEvent((IRTCProfileEvent2)rtcEvent);
                    break;

                case RTC_EVENT.RTCE_PRESENCE_PROPERTY:
                    break;
                    
                case RTC_EVENT.RTCE_PRESENCE_DATA:
                    break;
                    
                default:
                    break;
            }
        }

        void OnRTCProfileEvent(IRTCProfileEvent2 profileEvent)
        {
            Trace.WriteLine("Entering RTCPresenceCore.OnRTCProfileEvent  " + profileEvent.EventType);

            if (profileEvent.EventType == RTC_PROFILE_EVENT_TYPE.RTCPFET_PROFILE_GET)
            {
                if (RTCHelp.IsSucceeded(profileEvent.StatusCode))
                {
                    this.profile = (IRTCProfile2)profileEvent.Profile;
                    this.profile.AllowedAuth = RTCConst.RTCAU_USE_LOGON_CRED | 
                        RTCConst.RTCAU_NTLM | RTCConst.RTCAU_KERBEROS;
                    this.DoRegister();
                }
                else
                {
                    this.DoDisablePresence();
                    this.presenceUI.OnLoggedOff();
                    this.presenceUI.ShowMessage("Logon failed!", "Warning");
                }
            }            
        }

        void OnRTCRegistrationStateChangeEvent(IRTCRegistrationStateChangeEvent registerEvent)
        {
            Trace.WriteLine("Entering RTCPresenceCore.OnRTCRegistrationStateChangeEvent " 
                + registerEvent.State);

            switch(registerEvent.State)
            {
                case RTC_REGISTRATION_STATE.RTCRS_UNREGISTERING:
                    this.presenceUI.OnLoggingOff();
                    break;
                                
                case RTC_REGISTRATION_STATE.RTCRS_NOT_REGISTERED:
                    this.DoDisablePresence();
                    this.presenceUI.OnLoggedOff();
                    break;
                                
                case RTC_REGISTRATION_STATE.RTCRS_REGISTERING:
                    this.presenceUI.OnLoggingOn();
                    break;
            
                case RTC_REGISTRATION_STATE.RTCRS_REGISTERED:
                    this.presenceUI.OnLoggedOn();
                    break;
            
                case RTC_REGISTRATION_STATE.RTCRS_REJECTED:
                case RTC_REGISTRATION_STATE.RTCRS_ERROR:
                {
                    int statusCode = registerEvent.StatusCode;
            
                    Trace.WriteLine("RTCRS_REJECTED/ERROR " + statusCode);

                    // Logon failed. Most likely the server could no be found,
                    // or the user needs to authenticate.
                    if ((statusCode == RTCConst.RTC_E_STATUS_CLIENT_UNAUTHORIZED) ||
                        (statusCode == RTCConst.RTC_E_STATUS_CLIENT_PROXY_AUTHENTICATION_REQUIRED) ||
                        (statusCode == RTCConst.RTC_E_STATUS_CLIENT_FORBIDDEN) ||
                        (statusCode == RTCConst.RTC_E_STATUS_CLIENT_NOT_FOUND))
                    {
                        AuthData authData = this.presenceUI.ShowAuthDialog();

                        if (authData != null && authData.IsValid())
                        {
                            this.DoAuth(authData.Uri, authData.Account, authData.Password);
                        }
                        else
                        {
                            this.DoLogOff();
                            this.DoDisablePresence();
                            this.presenceUI.OnLoggedOff();
                            // If we were logging on the show error
                            if (registrationState == RTC_REGISTRATION_STATE.RTCRS_REGISTERING)
                            {
                                this.presenceUI.ShowMessage("Logon failed!", "Warning");
                            }
                            return;

                        }
                    }
                    else
                    {
                        // Logon failed
                        this.DoLogOff();
                        this.DoDisablePresence();
                        this.presenceUI.OnLoggedOff();
                        // If we were logging on the show error
                        if (this.registrationState == RTC_REGISTRATION_STATE.RTCRS_REGISTERING)
                        {
                            this.presenceUI.ShowMessage("Logon failed!", "Warning");
                        }
                        return;
                    }
                }
                    break;
                                
                case RTC_REGISTRATION_STATE.RTCRS_LOGGED_OFF:
                    // The server has removed the registration for this profile. 
                    // Incoming requests are no longer forwarded.
                    this.DoLogOff();
                    this.presenceUI.OnLoggingOff();
                    break;
                                
                case RTC_REGISTRATION_STATE.RTCRS_LOCAL_PA_LOGGED_OFF:
                    // The server has revoked the status as a presence agent for 
                    // this user. Incoming presence subscriptions are no longer 
                    // forwarded and our presence status is no longer visible to 
                    // others from this client. 
                    break;
                                
                case RTC_REGISTRATION_STATE.RTCRS_REMOTE_PA_LOGGED_OFF:
                    // The client that was the presence agent for this user has 
                    // logged off. It may be possible to register as a presence 
                    //agent from this client. 
                    break;

                default:
                    break;
            }
            
            this.registrationState = registerEvent.State;
        }
    }
}
////////////
//
// End RTC Functionality Code
//
////////////
