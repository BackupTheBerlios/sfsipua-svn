/*++

Copyright © Microsoft Corporation

Module Name:

    IRTCPresenceUI.cs

Abstract:

    The UI interface which defines how RTCPresenceCore module will
    send presence information to UI modules.
	
--*/

using System;
using RTCCore;

namespace Microsoft.Rtc.Sdk.Samples.RtcPresence
{
    public interface IRTCPresenceUI
    {
        void ClearBuddyList();
        void RemoveBuddy(IRTCBuddy2 buddy2);
        void UpdateBuddy(IRTCBuddy2 buddy2);

        void OnLoggedOff();
        void OnLoggingOff();
        void OnLoggingOn();
        void OnLoggedOn();

        void CloseUI();

        AuthData ShowAuthDialog();
        void ShowMessage(string message, string caption);
        void ShowStatus(string status);
    }
}
