-----------------------------------------------------------------------------------------------
Microsoft Real-Time Communications Client API SDK - RTCPresence.exe
© 2004 Microsoft Corporation. All rights reserved.
-----------------------------------------------------------------------------------------------


RTC Client API v1.3
RTCPresence.exe SDK sample


Description
=======
RTCPresence is a fully functional "C#" RTC application the uses the RTC Client API to 
sign in, sign out, set local presence, add a contact, remove a contact, view contact
properties, and poll a contact.


Configuration and Setup
===============
Operating System: Microsoft® Windows® XP and 
		Microsoft Windows Server™ 2003
Build: Build all the files by running Compile.bat. 


Files in This Sample
============
* RTCPresenceCore.cs		(RTC functionality code)
* RTCPresenceHelp.cs		(RTC functionality code)
* RTCPresenceConst.cs		(RTC functionality code)
* IRTCPresenceUI.cs		(UI)
* RTCPresence.cs			(UI) (have the "main" entry function)
* RTCPresenceAddressDialog.cs	(UI)
* RTCPresenceAuthDialog.cs		(UI)
* RTCPresenceLogonDialog.cs	(UI)
* RTCPresencePollDialog.cs		(UI)
* RTCPresenceTreeNode.cs		(UI)

The two files: RTCPresenceCore.cs and RTCPresenceHelp.cs contain most of the 
RTC client API functionality code. They initialize the RTC client, register for the events, 
and provide other RTC API related functionality. 

The other files mainly provide user interface functionality. The clear separation between 
the RTC functionality code and the user interface code is to make the program easy to understand and easy to change or reuse.


Building the Sample
============
* Verify that Microsoft .Net Framework version 1.1.4322 is installed.

* Add ".Net Framework" to the system PATH variable (typically, this is 
   %windir%\Microsoft.Net\Framework\v1.1.4322).

* Produce the Interop assembly. The Interop assembly (also known as Runtime Callable
   Wrappers) allows COM objects to be referenced by .Net clients. One manner to 
   produce the assembly is to use the type library importer tool (Tlbimp.exe), which is 
   part of the .Net framework. The following is an example method to generate the 
   type library and then the assembly.

   midl /I "your path\Microsoft SDK\Include" 
       /I "your Visual Studio path\PlatformSDK\Include\DShowIDL" rtccore.idl

       tlbimp rtccore.tlb /out:Interop.RTCCore.dll /namespace:RTCCore /sysarray

* Copy the Interop.RTCCore.dll file to the RTCPresence sample directory. Compile the 
   Compile.bat file and follow the instructions.

How to Run the Sample
===============
* Verify that Interop.RTCCore.dll, RTCPresence.exe.manifest, and RTCPresence.exe 
   are in the same directory.

* Start RTCPresence.exe.

* In the logon dialog box, type a user URI in the form of user@domain and enter
   the address of your SIP proxy/registrar server.

* If the authentication dialog box appears, type your SIP user name and password.
   The user name can be in the format of "domain\user name."

* Log on to the SIP server. A list of your contacts and their status appears. You can 
   use menus to add, remove, or poll a contact.


Troubleshooting
==========
* If the application presents a COMException, you can verify the COMException
   error code against the RTC reference. Or, you can use "Error Lookup" tool in 
   Microsoft Visual Studio® .Net.

* If the application presents a FileNotFoundException, verify that the Interop assembly 
   is in the same directory as the application.