/*++

Copyright © Microsoft Corporation

Module Name:

    RTCPresenceTreeNode.cs

Abstract:

    The module extends TreeNode in order to keep Buddy reference.
	
--*/

using System;

namespace Microsoft.Rtc.Sdk.Samples.RtcPresence
{
	/// <summary>
	/// Summary description for RTCTreeNode.
	/// </summary>
	public class RTCTreeNode :  System.Windows.Forms.TreeNode
	{
        private object entity;

        public object Entity
        {
            get {return this.entity;}
        }

		public RTCTreeNode(string text, object entity) : base (text)
		{
            this.entity = entity;
		}
	}
}
