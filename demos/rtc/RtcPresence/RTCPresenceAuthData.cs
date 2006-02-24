/*++

Copyright © Microsoft Corporation

Module Name:

   RTCPresenceAuthData.cs
 
Abstract:
	
--*/

using System;

namespace Microsoft.Rtc.Sdk.Samples.RtcPresence
{
    /// <summary>
    /// Summary description for AuthData.
    /// </summary>
    public class AuthData
    {
        string uri;
        string server;
        string transport;
        string account;
        string password;

        public AuthData()
        {
            uri = server = transport = account = password = String.Empty;
        }

        public string Uri
        {
            get { return this.uri; }
            set { this.uri = value; }
        }

        public string Server
        {
            get { return this.server;}
            set { this.server = value; }
        }

        public string Transport
        {
            get { return this.transport;}
            set { this.transport = value; }
        }

        public string Account
        {
            get { return this.account;}
            set { this.account = value; }
        }

        public string Password
        {
            get { return this.password;}
            set { this.password = value; }
        }

        public bool IsValid()
        {
            return (this.Uri.Length != 0);
        }

        public override string ToString()
        {
            return String.Format("URI: {0} Server: {1} Transport: {2} Account: {3}", 
                this.Uri, this.Server, this.Transport, this.Account);
        }
    }
}
