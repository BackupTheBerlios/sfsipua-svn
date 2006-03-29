/*
* register_script_sample.js
*
* Run before any other example scripts in order to register the script sample
* GUID with Google Desktop. It also stores its registration cookie result
* so that other scripts can use the cookie.
*
* You can only use the Query API if you have access to a registration cookie.
* There are two types of Query API registration cookies; read-only and
* read-write. If you are only running queries, you should get and use
* a read-only cookie. A read-write cookie lets you remove an item or item
* collection from the Google Desktop index via the RemoveFromIndex() method.
* Calls to RemoveFromIndex() when you just have a read-only cookie yield
* an "Access Denied" error.
*
* As with your house keys, registered cookies should not be left lying
* around unguarded.  They are the keys to your users' data so please
* guard them as if they were your own. :-)
*/

/*
* NOTE: We strongly recommend running this script with cscript.exe rather
* than wscript.exe. wscript.exe causes a series of unnecessary dialogs that
* you'll have to manually dismiss. If you mistakenly use wscript.exe, such
* as by double clicking on the script file, use Task Manager to terminate
* the program if you don't want to have to go through all the dialogs.
*
* CScript runs the script in a console window, with all output printed in
* that window:
*
*  cscript register_script_sample.js
*
* You can also pipe the output into a file by using the > operator:
*
*  cscript register_script_sample.js > output.txt
*
* To run the script with WScript.exe, either double click on the script in
* Explorer (assuming wscript.exe is your default handler for js files; it's
* Windows default handler), or execute the following command when in the
* script's folder:
*
*  wscript register_script_sample.js
*/

// This is the global identifier we've generated for our example scripts.
// For your code, use a tool such as guidgen.exe to generate your own GUID.
var g_scriptSampleId = "{8534E036-3D7C-4753-AC8D-35B289601165}";

// Our examples show how to do both queries and removals from the Desktop
// index, so we'll need read-write access.
var g_readOnlyAccess = false;

/*
* message() is a utility function that prints out messages.
* If you run this script with wscript.exe, the message appears in a message
* box with an OK button.
* If you use cscript.exe, the message prints out in the console window and
* no user interaction is needed.
*/
function message(text) {
  WScript.Echo(text);
}

/*
* storeRegistrationCookie() stores the cookie in the user's registry so
* it can be used later and let us not have to register every time we want
* to use the Query API. Other scripts in this examples directory rely on this
* having been run and the cookie being available.
*
* Note: This function stores an unencrypted cookie in the user's registry.
* You should not store unencrypted cookies, but we do so here for simplicity
* in our examples. Your applications should both encrypt their registration
* cookies and have the necessary code to unencrypt them when used.
*/
function storeRegistrationCookie(cookie) {
  var shell = new ActiveXObject("WScript.Shell");
  shell.RegWrite("HKCU\\Software\\Google\\QueryAPI_Samples\\Cookie", cookie, "REG_DWORD");
}

/*
* getRegistrationCookie() returns the previously stored registration cookie,
* or 0 if you haven't stored a cookie.
*/
function getRegistrationCookie() {
  var cookie = 0;

  try {
    var shell = new ActiveXObject("WScript.Shell");
    cookie = shell.RegRead("HKCU\\Software\\Google\\QueryAPI_Samples\\Cookie");
  } catch(e) {
    return 0;
  }

  return cookie;
}

/**
* install() fills in some registration fields and hands the information
* to Google Desktop.  This registration data will be stored along with the
* access rights and registration cookie so that Desktop can keep
* track of which component had the registration cookie assigned to it.
*
* The read_only argument should be set to true for read-only Query API access
* and false for read-write access.
*
* It returns the registration cookie value when successful, or 0 if the
* registration fails.
*/
function install(read_only) {
  var componentDescription = new Array();

  componentDescription[0] = "Title";
  componentDescription[1] = "Google Desktop Query API examples";

  componentDescription[2] = "Description";
  componentDescription[3] = "This is purely for demonstration purposes";

  // We don't really have an icon, but if we did, here's where we would
  // put the path to it.
  componentDescription[4] = "Icon";
  componentDescription[5] = "My Icon@1";

  componentDescription[6] = "Homepage";
  componentDescription[7] = "http://desktop.google.com";

  var cookie = 0;

  try {
    // Instantiate the Google Desktop registrar component
    var registrar = new ActiveXObject("GoogleDesktop.Registrar");

    // Give it our ID and description
    registrar.StartComponentRegistration(g_scriptSampleId, componentDescription);

    // Ask for the specific registration object that gives us Query API access.
    var regObj = registrar.GetRegistrationInterface("GoogleDesktop.QueryRegistration");

    // Now ask that registration object to give us a cookie representing
    // our Query API access.  Note the read_only flag here; if false, then
    // we're asking for read-write access instead of just read-only.
    cookie = regObj.RegisterPlugin(g_scriptSampleId, read_only);

    // Now submit and hope the user will accept this component
    // if not, then an error will be thrown
    registrar.FinishComponentRegistration();
  } catch (e) {
    // We hit an error
    message("Couldn't register the script samples.\n" + new String(e.number) +
            "\n" + e.description);
    return 0;
  }

  return cookie;
}

////////////////////////////////////////////////////////////////////////////////
// main() runs the various previously defined routines and registers our
// example GUID and stores the resulting registration cookie for later use.

function main() {
  // First check if we're already installed
  var existingCookie = getRegistrationCookie();

  if (existingCookie == 0) {
    // Register the script samples
    var registrationCookie = install(g_readOnlyAccess);

    if (registrationCookie != 0) {
      // Save the cookie for later use
      storeRegistrationCookie(registrationCookie);
    }
  } else {
    message("A registration cookie has already been stored.\n" +
            "Please unregister before registering again.");
  }
}

main();