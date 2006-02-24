/*++

Copyright © Microsoft Corporation

Module Name:

    RTCPresenceHelp.cs

Abstract:

    This module provides static methods to handle RTC platform objects.
		
--*/

////////////
//
// Begin RTC Functionality Code
// This code demonstrates Logging on/off and Add/Remove/Poll Buddy
//
////////////

using System;
using System.Text;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Collections;
using RTCCore;

namespace Microsoft.Rtc.Sdk.Samples.RtcPresence
{
    sealed public class RTCHelp
    {
        private RTCHelp()
        {
        }

        public static bool IsFailed(int status)
        {
            return (status < 0);
        }

        public static bool IsSucceeded(int status)
        {
            return (status >= 0);
        }

        public static string BuildDisplayName(string entity, RTC_PRESENCE_STATUS presenceStatus)
        {
            Trace.WriteLine("Entering RTCHelp.BuildDisplayName");
            
            StringBuilder sbDisplay = new StringBuilder(entity);

            switch (presenceStatus)
            {
                case RTC_PRESENCE_STATUS.RTCXS_PRESENCE_OFFLINE:
                    sbDisplay.Append(" (Offline)");
                    break;
                case RTC_PRESENCE_STATUS.RTCXS_PRESENCE_ONLINE:
                    sbDisplay.Append(" (Online)");
                    break;
                case RTC_PRESENCE_STATUS.RTCXS_PRESENCE_AWAY:
                    sbDisplay.Append(" (Away)");
                    break;
                case RTC_PRESENCE_STATUS.RTCXS_PRESENCE_IDLE:
                    sbDisplay.Append(" (Idle)");
                    break;
                case RTC_PRESENCE_STATUS.RTCXS_PRESENCE_BUSY:
                    sbDisplay.Append(" (Busy)");
                    break;
                case RTC_PRESENCE_STATUS.RTCXS_PRESENCE_BE_RIGHT_BACK:
                    sbDisplay.Append(" (Be right back)");
                    break;
                case RTC_PRESENCE_STATUS.RTCXS_PRESENCE_ON_THE_PHONE:
                    sbDisplay.Append(" (On the phone)");
                    break;
                case RTC_PRESENCE_STATUS.RTCXS_PRESENCE_OUT_TO_LUNCH:
                    sbDisplay.Append(" (Out to lunch)");
                    break;
                default:
                    break;
            }

            return sbDisplay.ToString();
        }

        public static string BuildBuddyDisplayName(IRTCBuddy2 buddy2)
        {
            Trace.WriteLine("Entering RTCHelp.BuildBuddyDisplayName");

            RTC_PRESENCE_STATUS presenceStatus = buddy2.Status;
            string name = RTCHelp.GetBuddyName(buddy2);

            if (name == null || name.Length == 0)
            {
                Trace.WriteLine("NULL Buddy Name");
                return null;
            }

            return RTCHelp.BuildDisplayName(name, presenceStatus);
        }

        public static ArrayList BuildDeviceDisplayNameList(IRTCBuddy2 buddy2)
        {
            Trace.WriteLine("Entering RTCHelp.BuildDeviceDisplayNameList");

            ArrayList deviceList = new ArrayList();
            string deviceName;
            RTC_PRESENCE_STATUS deviceStatus;

            try
            {
                IRTCCollection deviceCollection = buddy2.PresenceDevices;

                foreach (IRTCPresenceDevice device in deviceCollection)
                {
                    try
                    {
                        deviceName = device.get_PresenceProperty(RTC_PRESENCE_PROPERTY.RTCPP_DEVICE_NAME);
                    }
                    catch (COMException)
                    {
                        deviceName = "NOT EXIST";
                        Trace.WriteLine("NULL Device Name");
                        continue;
                    }

                    try
                    {
                        deviceStatus = device.Status;
                    }
                    catch (COMException)
                    {
                        deviceStatus = RTC_PRESENCE_STATUS.RTCXS_PRESENCE_OFFLINE;
                    }

                    string deviceDisplayName = RTCHelp.BuildDisplayName(deviceName, deviceStatus);
                    deviceList.Add(deviceDisplayName);
                }
            }
            catch (COMException)
            {
                return null;
            }

            return deviceList;
        }

        public static string GetBuddyName(IRTCBuddy2 buddy2)
        {
            Trace.WriteLine("Entering RTCHelp.GetBuddyName");

            string buddyName;

            try 
            {
                buddyName = buddy2.get_PresenceProperty(RTC_PRESENCE_PROPERTY.RTCPP_DISPLAYNAME);
            }
            catch(COMException)
            {
                buddyName = null;
            }

            if (buddyName == null)
            {
                try
                {
                    buddyName = buddy2.PresentityURI;
                }
                catch (COMException)
                {
                    buddyName = null;
                }
            }
            
            return buddyName;
        }

        public static string GetDeviceProperties(IRTCPresenceDevice device)
        {
            Trace.WriteLine("Entering RTCHelp.GetDeviceProperties");

            StringBuilder properties = new StringBuilder();
            string displayname;
            RTC_PRESENCE_STATUS presenceStatus;
            string notes;
            string space;
            string data;

            try
            {
                displayname = device.get_PresenceProperty(RTC_PRESENCE_PROPERTY.RTCPP_DEVICE_NAME);
            }
            catch  (COMException)
            {
                displayname = "NOT EXIST";
            }

            try
            {
                presenceStatus = device.Status;
            }
            catch  (COMException)
            {
                presenceStatus = RTC_PRESENCE_STATUS.RTCXS_PRESENCE_OFFLINE;
            }

            try
            {
                notes = device.Notes;
            }
            catch  (COMException)
            {
                notes = "NOT EXIST";
            }

            try
            {
                device.GetPresenceData(out space, out data);
            }
            catch  (COMException)
            {
                space = "NOT EXIST";
                data = "NOT EXIST";
            }

            properties.Append(string.Format("Device Name: {0}\n",
                    displayname));
            properties.Append(string.Format("    Status: {0}\n",
                presenceStatus));
            properties.Append(string.Format("    Notes: {0}\n",
                notes));
            properties.Append(string.Format("    NameSpace: {0}\n",
                space));
            properties.Append(string.Format("    Data: {0}\n",
                data));

            //Note: one dummy device object was provided for offline buddies
            if (displayname == "NOT EXIST")
            {
                return null;
            }

            return properties.ToString();
        }

        public static string GetBuddyProperties(IRTCBuddy2 buddy2)
        {
            Trace.WriteLine("Entering RTCHelp.GetBuddyProperties");

            StringBuilder properties = new StringBuilder();
            string displayname, phone, email;
            string uri, notes, data;
            bool fPersistant;
            RTC_PRESENCE_STATUS presenceStatus;

            try
            {
                displayname = buddy2.get_PresenceProperty(RTC_PRESENCE_PROPERTY.RTCPP_DISPLAYNAME);
            }
            catch (COMException )
            {
                displayname = "NOT EXIST";
            }

            try
            {
                phone = buddy2.get_PresenceProperty(RTC_PRESENCE_PROPERTY.RTCPP_PHONENUMBER);
            }
            catch (COMException )
            {
                phone = "NOT EXIST";
            }

            try
            {
                email = buddy2.get_PresenceProperty(RTC_PRESENCE_PROPERTY.RTCPP_EMAIL);
            }
            catch (COMException )
            {
                email = "NOT EXIST";
            }

            try
            {
                uri = buddy2.PresentityURI;
            }
            catch (COMException )
            {
                uri = "NOT EXIST";
            }

            try
            {
                fPersistant = buddy2.Persistent;
            }
            catch (COMException )
            {
                fPersistant = false;
            }

            try
            {
                presenceStatus = buddy2.Status;
            }
            catch (COMException )
            {
                presenceStatus = RTC_PRESENCE_STATUS.RTCXS_PRESENCE_OFFLINE;
            }

            try
            {
                notes = buddy2.Notes;
            }
            catch (COMException )
            {
                notes = "NOT EXIST";
            }

            try
            {
                data = buddy2.Data;
            }
            catch (COMException )
            {
                data = "NOT EXIST";
            }

            properties.Append(string.Format("Buddy Name: {0}\nPhone: {1}\nEmail: {2}\n",
                displayname, 
                phone,
                email));

            properties.Append(string.Format("URI: {0}\nStatus: {1}\nPersistant: {2}\nNotes: {3}\nData: {4}\n",
                uri,
                presenceStatus,
                fPersistant,
                notes,
                data));

            Trace.WriteLine("Get groups");

            properties.Append("Group List: ");

            try 
            {
                IRTCCollection groupCollection = buddy2.Groups;

                foreach (IRTCBuddyGroup pGroup in groupCollection)
                {
                    try
                    {
                        if (pGroup.Name == null || pGroup.Name.Length == 0)
                        {
                            Trace.WriteLine("NULL Group Name");
                            continue;
                        }
                        properties.Append(pGroup.Name + "  ");
                    }
                    catch(COMException ex1COM)
                    {
                        Trace.WriteLine("COMException " + ex1COM.Message); 
                    }
                }
            }
            catch(COMException ex1COM)
            {
                Trace.WriteLine("COMException " + ex1COM.Message); 
            }
    
            properties.Append("\n");

            Trace.WriteLine("Get devices");

            try 
            {
                IRTCCollection deviceCollection = buddy2.PresenceDevices;

                foreach (IRTCPresenceDevice device in deviceCollection)
                {
                    properties.Append(GetDeviceProperties(device));
                }
            }
            catch(COMException ex1COM)
            {
                Trace.WriteLine("COMException " + ex1COM.Message);
            }        
            
            return properties.ToString();
        }
    }
}
////////////
//
// End RTC Functionality Code
//
////////////
