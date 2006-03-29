#region Copyright 2005 Google Inc.
//
// All Rights Reserved.
// 
// Sample Google Desktop Search plug-in for MSN Messenger
//
#endregion

using System;
using System.IO;
using System.Collections;
using System.Diagnostics;
using System.Threading;
using System.Xml;
using System.Runtime.InteropServices;
using Microsoft.Win32;
using System.Windows.Forms;

using GoogleDesktopAPILib;

namespace Google.Desktop.MSNMessengerComponent
{
  /// <summary>
  /// Captures and sends MSN conversations to the Google Desktop Search system
  /// </summary>
  public class MSNCapture
  {
    #region Internal classes

    /// <summary>
    /// Holds per IM message information 
    /// </summary>
    internal struct MSNMessageData
    {
      public DateTime date;
      public string fromFriendlyName;
      public string toFriendlyName;
      public string message;
      public int sessionId;
    }

    /// <summary>
    /// Holds data about an MSN passport identity
    /// </summary>
    internal class Passport
    {
      string passportId;
      string logFilePath;
      DateTime logLastIndexed;

      public Passport(string id, string filePath) 
      {
        passportId = id;
        logFilePath = filePath;
        logLastIndexed = DateTime.MinValue;
      }

      public string PassportId 
      {
        get {return passportId;}
      }

      public string LogFilePath 
      {
        get {return logFilePath;}
      }
        
      public DateTime LogLastIndexed 
      {
        get {return logLastIndexed;}
        set {logLastIndexed = value;}
      }
    }

    #endregion Internal classes

    #region Private Data
    
    const string kLogginEnableMessage = "In order to allow chat indexing\nplease enable the MSN Message History\ncheckbox under Tools->Options->Messages";
    const string kComponentGuid = "{7c6a240f-824e-4f90-84c3-ee3901f1c1d7}";
    const string kPerPassportSettings = "Software\\Microsoft\\MSNMessenger\\PerPassportSettings";
    const string kWindowsRunRegKey = "Software\\Microsoft\\Windows\\CurrentVersion\\Run";

    const string kMessengerSetupMessage = "GDS Messenger Component Setup";
    const string kMessageLogPath = "MessageLogPath";
    const string kMessageLogLastIndexed = "MessageLogLastIndexed";

    static string userName = null;
    static string buddyName = null;
    static Passport [] passportList = null;

    #endregion Private Data  

    #region Public Methods

    /// <summary>
    /// Captures MSN conversations
    /// </summary>
    private void CaptureMessages()
    {
      // first get the location of the log files
			RegistryKey key = Registry.CurrentUser.OpenSubKey(kPerPassportSettings, true);
      if (null != key && key.SubKeyCount > 0)  
      {
        // enumerate through all passports and save settings
        string [] subKeys = key.GetSubKeyNames();
        passportList = new Passport[subKeys.Length];

        for (int i=0; i < subKeys.Length; i++) 
        {
          RegistryKey subKey = key.OpenSubKey(subKeys[i]);
          passportList[i] = new Passport(subKeys[i], (string)subKey.GetValue(kMessageLogPath));

          // check if we have a value for last indexed
          string lastIndexed = (string)subKey.GetValue(kMessageLogLastIndexed);   
          subKey.Close();
          if (lastIndexed != null)
          {
            passportList[i].LogLastIndexed = DateTime.Parse(lastIndexed);
          }
        }
        key.Close();
      }

      // periodically check which log files timestamps have changed
      // for each log file that has changed - parse it and send the new messages to GDS
      while (true)
      {
        foreach (Passport passport in passportList)
        {
          DateTime now = DateTime.Now;
          bool needTimeUpdate = false;

          // check if a chat log exists for this user
          if (passport.LogFilePath == null || !Directory.Exists(passport.LogFilePath))
            continue;

          string [] fileEntries = Directory.GetFiles(passport.LogFilePath);
          foreach (string file in fileEntries)
          {
            if (file.EndsWith(".xml")) 
            {
              if (File.GetLastWriteTime(file).CompareTo(passport.LogLastIndexed) > 0) 
              {
                needTimeUpdate = true;
                ParseAndSendMessages(file, passport.LogLastIndexed);
              }
            }
          }
          // update time stamp of last index check
          if (needTimeUpdate)
          {
            passport.LogLastIndexed = now;
            RegistryKey subKey = Registry.CurrentUser.OpenSubKey(kPerPassportSettings + "\\" + passport.PassportId, true);
            subKey.SetValue(kMessageLogLastIndexed, passport.LogLastIndexed.ToString());
            subKey.Close();
          }
        }

        // sleep for some time
        Thread.Sleep(5000);
      }
    }

    /// <summary>
    /// Registers and unregisters the component with GDS
    /// </summary>
    /// <param name="install">set to true to register, false otherwise</param>
    /// <returns>true on success</returns>
    private bool DoRegistration(bool install) 
    {
      try 
      {
        // register/unregister the component
        GoogleDesktopIndexingComponentRegisterClass gdsReg = new GoogleDesktopIndexingComponentRegisterClass();

        if (install) 
        {
          bool result = SimpleMessageBox(kMessengerSetupMessage, kLogginEnableMessage, true);

          if (!result) 
            return false;
          
          try 
          {
            // register with GDS
            object [] componentDesc = new object[6] {"Title", "MSN Chats", "Description", "Captures and indexes MSN Messenger conversations", "Icon", "no icon"};
            gdsReg.RegisterIndexingComponent(kComponentGuid, componentDesc);

            // add the program to Run
            RegistryKey key = Registry.CurrentUser.OpenSubKey(kWindowsRunRegKey, true);
            key.SetValue(kMessengerSetupMessage, Directory.GetCurrentDirectory()+ "\\" + Process.GetCurrentProcess().ProcessName + ".exe");

            SimpleMessageBox(kMessengerSetupMessage, "Registration completed successfully!", false);
          }
          catch(COMException e)
          {
            // check if not already registered
            if ((UInt32)e.ErrorCode != 0x80040006)       // E_COMPONENT_ALREADY_REGISTERED
            {
              SimpleMessageBox("COM Exception", e.ToString(), false);
              return false;
            }
            else
              SimpleMessageBox(kMessengerSetupMessage, "Component already registered!", false);
          }
        }
        else
        {
          try 
          {
            gdsReg.UnregisterIndexingComponent(kComponentGuid);
          }
          catch(COMException e)
          {
            // check if not already unregistered
            if ((UInt32)e.ErrorCode != 0x80040002)        // E_COMPONENT_NOT_REGISTERED
              SimpleMessageBox("COM Exception", e.ToString(), false);
          }

          // remove the program from Run
          RegistryKey key = Registry.CurrentUser.OpenSubKey(kWindowsRunRegKey, true);
          key.DeleteValue(kMessengerSetupMessage, false);

          SimpleMessageBox(kMessengerSetupMessage, "Component unregistered successfully!", false);
        }
      }
      catch (Exception e) 
      {
        SimpleMessageBox("Exception", e.ToString(), false);
        return false;
      }

      return true;
    }

    #endregion Public Methods

    #region Private Methods

    /// <summary>
    /// Captures MSN conversations
    /// </summary>
    /// <param name="xmlMessage">xml string containing an IM message data</param>
    /// <returns>an MSNMessageData struct containing the parsed data</returns>
    private MSNMessageData ParseMessageData(string xmlMessage) 
    {
      XmlDocument doc = new XmlDocument();
      doc.LoadXml(xmlMessage);
      XmlNodeReader reader = new XmlNodeReader(doc);
      MSNMessageData messageData = new MSNMessageData();

      // Moves the reader to the root element.
      reader.MoveToContent();

      // get the date
      reader.MoveToAttribute("DateTime");
      messageData.date = DateTime.Parse(reader.Value);

      // get the session id
      reader.MoveToAttribute("SessionID");
      messageData.sessionId = Convert.ToInt32(reader.Value);

      // get the rest of the attributes
      while (reader.Read())
      {
        // advance to the inner node we're interested in
        if (reader.NodeType == XmlNodeType.Element)
        {
          string parentNodeName = reader.LocalName;
          reader.Read();

          switch(parentNodeName)
          {
            case "From":
              // get the from user 
              reader.MoveToAttribute("FriendlyName");
              messageData.fromFriendlyName = reader.Value;
              break;
            case "To":
              // get the to user 
              reader.MoveToAttribute("FriendlyName");
              messageData.toFriendlyName = reader.Value;
              break;
              // get the actual IM message
            case "Text":
              messageData.message = reader.Value;
              break;  
            default:
              break;
          }
        }
      }

      // set user and buddy names if not already set
      if (userName == null)
        userName = messageData.fromFriendlyName;

      if (buddyName == null)
        buddyName = messageData.toFriendlyName;

      return messageData;
    }

    /// <summary>
    /// Sends the conversation data to GDS using COM Interop
    /// </summary>
    /// <param name="messageData">MSNMessageData struct containing the IM message data</param>
    private void SendMessageData(MSNMessageData messageData)
    {  
      try 
      {
        GoogleDesktopClass gdsClass = new GoogleDesktopClass();

        // create the event
        object gdsEventDisp = gdsClass.CreateEvent(kComponentGuid, "Google.Desktop.IM");
        IGoogleDesktopEvent gdsEvent = (IGoogleDesktopEvent)gdsEventDisp;

        // add IM event properties

        // "message_time" property
        gdsEvent.AddProperty("message_time", messageData.date.ToUniversalTime().ToOADate());

        // "format" property
        gdsEvent.AddProperty("format", "text/html");

        // "content" property
        gdsEvent.AddProperty("content", messageData.fromFriendlyName + ": " + messageData.message);

        // "user_name" property
        gdsEvent.AddProperty("user_name", userName);

        // "buddy_name" property
        gdsEvent.AddProperty("buddy_name", buddyName);
        
        // "conversation_id" property
        gdsEvent.AddProperty("conversation_id", messageData.sessionId);
        
        // "title" property - use the buddy name
        gdsEvent.AddProperty("title", buddyName);

        // send the event real-time
        gdsEvent.Send(0x01);
      }
      catch (COMException e)
      {
        // protect some valid error results
        UInt32 error = (UInt32)e.ErrorCode;
        if (error != 0x80040005 &&    // E_COMPONENT_DISABLED
            error != 0x80040008 &&    // E_EVENT_TOO_LARGE
            error != 0x80040009       // E_SERVICE_NOT_RUNNING
          )
        {
          SimpleMessageBox("COM Exception", e.ToString(), false);
        }
      }
    }

    /// <summary>
    /// Parses an IM log file and sends the information to GDS
    /// </summary>
    /// <param name="logFile">The IM conversations log file</param>
    /// <param name="lastIndexed">messages older than this will not be sent to GDS</param>
    private void ParseAndSendMessages(string logFile, DateTime lastIndexed)
    {
      XmlDocument doc = new XmlDocument();
      doc.Load(logFile);
      XmlNodeReader reader = new XmlNodeReader(doc);

      // reset user and buddy name
      userName = null;
      buddyName = null;

      // Moves the reader to the root element.
      reader.MoveToContent();

      // move to the first message
      reader.Read();

      while(reader.LocalName == "Message") 
      {
        // check the date of the message - if older skip
        reader.MoveToAttribute("DateTime");
        DateTime messageDateTime = DateTime.Parse(reader.Value);
        reader.MoveToElement();

        // if older than the last indexing time, skip the message
        if (messageDateTime.CompareTo(lastIndexed) <= 0) 
        {
          reader.Skip();
          continue;
        }

        // get message data
        MSNMessageData messageData = ParseMessageData(reader.ReadOuterXml());
        
        // send this message to GDS for indexing
        SendMessageData(messageData);
      }
    }

    /// <summary>
    /// Helper function to display a message box
    /// </summary>
    /// <param name="caption">Caption of the message box</param>
    /// <param name="text">Text of the message box</param>
    /// <param name="okCancel">Choice of buttons</param>
    /// <returns>true/false based on button selection</returns>
    private bool SimpleMessageBox(string caption, string text, bool okCancel) 
    {
      DialogResult result = MessageBox.Show(text, caption, okCancel ? MessageBoxButtons.OKCancel : MessageBoxButtons.OK);
      return (result == DialogResult.OK) ? true : false;
    }
    #endregion Private Methods    

    # region Main

    /// <summary>
    /// Main entry point
    /// </summary>
    public static void Main(string [] args) 
    {
      MSNCapture msnCapture = new MSNCapture();

      // check command line args
      for (int i = 0; i < args.Length; i++)
      {
        switch (args[i])
        {
          case "-register":
            // register and if successful launch the component
            if (msnCapture.DoRegistration(true) == false)
              return;
            break;

          case "-unregister":
            msnCapture.DoRegistration(false);
            return;

          default:
            return;
        }
      }

      // index existing IM messages and monitor and index new conversations
      msnCapture.CaptureMessages();
    }
    # endregion Main  
  }
}
