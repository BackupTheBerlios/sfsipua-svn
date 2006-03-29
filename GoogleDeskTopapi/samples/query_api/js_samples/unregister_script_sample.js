/*
* unregister_script_sample.js
*
* Run this script to uninstall the Javascript Query API samples.
*/

/*
* How to run this sample:
*
* This sample can be run with either CScript.exe [recommended] or WScript.exe.
* CScript runs the script in a console window where it prints messages while
* WScript creates a message box for every message.
*
* To run the script with CScript.exe, run:
*
*  cscript unregister_script_sample.js
*
* To run with WScript.exe, you can either double click on the script in
* explorer (assuming you have wscript.exe as the default handler for js files,
* which is the Windows default), or execute the following command in the folder
* where the script file resides:
*
*  wscript unregister_script_sample.js
*/

// The global identifier of the samples.
var g_scriptSampleId = "{8534E036-3D7C-4753-AC8D-35B289601165}";

/*
* A little utility function that prints out messages.
* If wscript.exe is used to run this script, then this
* will show a message box with an OK button.
* If cscript.exe is used, then this function just prints out
* the message and no user interaction is needed.
*/
function message(text) {
  WScript.Echo(text);
}

/*
* Deletes the registry settings of the Query API script samples.
*/
function deleteSettings() {
  try {
    var shell = new ActiveXObject("WScript.Shell");
    // Delete the QueryAPI_Samples sub key
    shell.RegDelete("HKCU\\Software\\Google\\QueryAPI_Samples\\");
  } catch (e) {
    return false;
  }

  return true;
}

/*
* Unregisters the javascript sample ID from the Google Desktop
* component registry.
* Returns true if the component was successfully unregistered, false otherwise.
*/
function uninstall() {
  try {
    var registrar = new ActiveXObject("GoogleDesktop.Registrar");
    registrar.UnregisterComponent(g_scriptSampleId);
  } catch (e) {
    return false;
  }
  
  return true;
}

////////////////////////////////////////////////////////////////////////////////
// Main routine

function main() {
  uninstall();
  deleteSettings();
  message("Unregistration complete and settings have been deleted.");
}

main();
