========================================================================
        RTCSample Application (Using RTC Client API)  
========================================================================


Sample Description:
=================

	RTCSample is a fully functional RTC application the uses the RTC
        Client SDK to demonstrate the use of RTC features.


Features in the Sample:
=================

	Features in the sample include:

	- Buddies, Watchers, and Groups Management
	- Instant Messaging and Multiparty Instant Messaging
	- PC-to-PC audio/video call features (including Tuning Wizard)
	- Audio Video and T120 Encryption
	- Extended Presence Device and Properties Information
	- Network Quality Information
	- The DTMF Dialpad
	- Authentication and Auto-Logon features
	- User Search
	- And More...

	
Configurations & Setup:
=======================
      
        - OS       = Windows XP, Windows 2000, 32-bit environments
        - Build    = Build all the files in Platform SDK Environment by
                     running nmake
		 

Building the Sample :
======================

- When building the sample you need to link with uuid.lib and set the include
  path to point the RTC Headers rtccore.h and rtcerr.h OR include in
  RTCSample.cpp rtccore_i.c (generated from running midl on rtccore.idl) for
  this you don't need to link with uuid.lib
		  

How To Run The Sample:
======================

- To execute the RTCSample.exe a file named RTCSample.exe.manifest needs to be in the same
  folder with RTCSample.exe. To get RTCSample.exe.manifest, copy and rename the manifest
  from the VB sample (from RTCSampleVB.exe.manifest to RTCSample.exe.manifest).
 
  This step only needs to be performed once per installation.
 
- Start RTCSample.exe

- At the logon dialog, type a user URI in the form of user@domain and enter
  the address of your SIP proxy/registrar server.

- If you don't have a server you can cancel the logon dialog and still place
  peer-to-peer calls and instant messages.

- The Menu Items in the Main Dialog will lead you to other features.


RTC Sample Table of Contents
======================

This table of contents will help you in find RTC Code for the feature you may be trying to implement.
It is indexed first by source file name, and then method name.

rtcwatcher.cpp
--------------
1) CRTCWatcher::UpdateWatcherList
	This code demonstrates getting watcher name, URI, watcher state 
	and scope and populating the list box
 
2) CRTCWatcher::UpdateWatcherList
	This code demonstrates Addref for the watcher

3) CRTCWatcher::ClearWatcherList
	This code demonstrates releasing IRTCWatcher references

4) CRTCWatcher::PopulateWatcherList
	This code demonstrates enumerating watchers and populating UI

5) CRTCWatcher::DoAddWatcher
	This code demonstrates Adding a watcher

6) CRTCWatcher::DoRemoveWatcher
	This code demonstrates Removing a watcher

7) CRTCWatcher::DoSetWatcherState
	This code demonstrates Setting a watcher's state.


rtcav.cpp
---------
1) CRTCAVSession::DoMute
	This code demonstrates Mute and Unmute operations on audio spk and mic

2) CRTCAVSession::DoVolume
	This code demonstrates setting the speaker/mic volume to a certain value.

3) CRTCAVSession::DoVideo
	This code demonstrates Adding or removing video to/from a call

4) CRTCAVSession::ShowAppSharing
	This code demonstrates Adding T120 stream for appsharing to a call

5) CRTCAVSession::ShowWhiteBoard
	This code demonstrates Adding T120 stream for whiteboarding to a call

6) CRTCAVSession::ShowAudio
	This code demonstrates Reading audio settings from RTC and updating UI

7) CRTCAVSession::ShowVideo
	This code demonstrates Reading Video settings from RTC and updating UI

8) CRTCAVSession::OnTimer
	This code demonstrates obtaining NetworkQuality while in a call.


rtcdialogs.cpp
--------------
1) ShowBuddyPropertiesDialog
	This code demonstrates obtaining presence properties in order to display in UI

2) DialpadDialogProc
	This code demonstrates sending DTMF tones


rtcgroup.cpp
--------------
1) CRTCGroup::UpdateGroupList
	This code demonstrates getting group name and updating the group list UI

2) CRTCGroup::ClearGroupList
	This code demonstrates releasing IRTCBuddyGroup references

3) CRTCGroup::PopulateGroupList
	This code demonstrates enumerating groups and populating UI.

4) CRTCGroup::DoAddGroup
	This code demonstrates Adding a group

5) CRTCGroup::DoRemoveGroup
	This code demonstrates Removing a group


rtcim.cpp
----------
1) CRTCIMSession::UpdateParticipantList
	This code demonstrates getting participant name and updating participant list UI

2) CRTCIMSession::UpdateParticipantList
	This code demonstrates obtaining participant state to update the UI

3) CRTCIMSession::ClearParticipantList
	This code demonstrates releasing IRTCParticipant references

4) CRTCIMSession::DoSendMessage
	This code demonstrates sending an IM

5) CRTCIMSession::DoAddParticipant
	This code demonstrates Adding a participant to a session

6) CRTCIMSession::DoRemoveParticipant
	This code demonstrates releasing IRTCParticipant references

7) CRTCIMSession::DeliverSessionState
	This code demonstrates Calling RTC to see if a participant can be added


rtcsearch.cpp
-------------
1) CRTCSearch::UpdateResultList
	This code demonstrates getting usersearch results and updating UI

2) CRTCSearch::ClearResultList
	This code demonstrates releasing IRTCUserSearchResult references

3) CRTCSearch::DoSearch
	This code demonstrates Creating a query, setting search term, setting search 
	preferences and searching based on first/last name or email for user search 

4) CRTCSearch::OnDestroy
	This code demonstrates releasing usersearch and profile references

5) CRTCSearch::OnNotify
	This code demonstrates obtaining user search results and updating UI.

rtcsession.cpp
--------------
1) CRTCSession::OnDestroy
	This code demonstrates Terminating a session	

rtcwin.cpp
----------
1) CRTCWin::GetUserURI 
	This code demonstrates how to query the profile or client for the local user URI

2) CRTCWin::GetUserName 
	This code demonstrates how to query the profile or client for the local user name

3) CRTCWin::TreeViewHelper_InsertNode 
	This code demonstrates how to enumerate the presence devices on a buddy

4) CRTCWin::UpdateBuddyList 
	This code demonstrates how to read the display name, basic presence, and URI of a buddy

5) CRTCWin::PopulateBuddyList() 
	This code demonstrates how to enumerate the current buddies

6) CRTCWin::DoGetProfile 
	This code demonstrates how to get a profile based on server name, transport, account settings, and uri

7) CRTCWin::DoEnableProfile 
	This code demonstrates how to Enable a Profile (which you can create using GetProfile).

8) CRTCWin::DoRegister 
	This code demonstrates the registration sequence.

9) CRTCWin::DoAuth 
	This code demonstrates how to set the credentials on a profile.

10) CRTCWin::DoEnablePresence 
	This code demonstrates EnablePresenceEx on a Profile (which you can create using GetProfile).
	This code demonstrates how to set a presence property for this particular device.

11) CRTCWin::DoAddBuddy 
	This code demonstrates how to Add a Buddy

12) CRTCWin::DoRefreshBuddy
	This code demonstrates how to refresh a buddy's presence.

13) CRTCWin::DoRemoveBuddy
	This code demonstrates how to remove a buddy

14) CRTCWin::DoCall
	This code demonstrates how to Create a Session with another user

15) CRTCWin::DoTuningWizard
	This code demonstrates how to invoke the tuning wizard

16) CRTCWin::DoSetPresence
	This code demonstrates how to set the presence for your device.

17) CRTCWin::DoOptions
	This code demonstrates how to set the preferred security level, the preferred media types,
	the client name, the client version, the max bitrate, and the preferred security level.

18) CRTCWin::OnCreate
	This code demonstrates how to create an RTC Client object and query its version,
	Initialize the client, set its event filter for the events we are interested in,
	set the listen mode, and attach the event sink.

19) CRTCWin::OnDestroy
	This code demonstrates how to detach the event sink and shutdown the client.

20) CRTCWin::OnClose
	This code demonstrates how to prepare the client for shutdown.

21) CRTCWin::OnRTCEvent
	This code demonstrates how to receive a particular event object from the IDispatch object.

22) CRTCWin::OnRTCRegistrationStateChangeEvent
	This code demonstrates how to handle a Registration State Change event.

23) CRTCWin::OnRTCSessionStateChangeEvent
	This code demonstrates how to handle a Session State Change event.

24) CRTCWin::OnRTCParticipantStateChangeEvent
	This code demonstrates how to handle a Participant State Change event.

25) CRTCWin::OnRTCMessagingEvent
	This code demonstrates how to handle a Messaging Event.

26) CRTCWin::OnRTCMediaEvent
	This code demonstrates how to handle a Media Event.

27) CRTCWin::OnRTCIntensityEvent
	This code demonstrates how to handle an Intensity Event.

28) CRTCWin::OnRTCClientEvent
	This code demonstrates how to handle a Client Event.

29) CRTCWin::OnRTCBuddyEvent
	This code demonstrates how to handle a Buddy Event.

30) CRTCWin::OnRTCWatcherEvent
	This code demonstrates how to handle a Watcher Event.

31) CRTCWin::OnRTCBuddyGroupEvent
	This code demonstrates how to handle a Buddy Group Event.

32) CRTCWin::OnRTCUserSearchResultsEvent
	This code demonstrates how to handle a User Search Results Event.

33) CRTCWin::OnRTCRoamingEvent
	This code demonstrates how to handle a Roaming Event.

34) CRTCWin::OnRTCProfileEvent
	This code demonstrates how to handle a Profile Event.

35) CRTCWin::OnRTCPresencePropertyEvent
	This code demonstrates how to handle a Presence Property Event.

36) CRTCWin::OnRTCPresencePropertyEvent
	This code demonstrates how to handle a Presence Data Event.

37) CRTCWin::OnRTCPresenceStatusEvent
	This code demonstrates how to handle a Presence Status Event.
