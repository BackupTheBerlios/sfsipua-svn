/*
* simple_query.js
*
* This script defines the simple_query() function, which takes a string
* argument and does a Google Desktop search for the string. It also runs
* simple_query() on the argument "hello world". The results are written out
* on the screen.
*
* NOTE: We strongly recommend running this script with cscript.exe rather
* than wscript.exe. wscript.exe causes a series of unnecessary dialogs that
* you'll have to manually dismiss. If you mistakenly use wscript.exe, such
* as by double clicking on the script file, use Task Manager to terminate
* the program if you don't want to have to go through all the dialogs.
*
* CScript runs the script in a console window, with all output printed in
* that window:
*
*  cscript simple_query.js
*
* You can also pipe the output into a file by using the > operator:
*
*  cscript simple_query.js > output.txt
*/

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
* getRegistrationCookie() returns the previously stored registration cookie.
* If no cookie is available, the Query API sample scripts have not been
* registered. It then displays an error message and terminates the currently
* running script.
*/
function getRegistrationCookie() {
  var cookie = 0;

  try {
    var shell = new ActiveXObject("WScript.Shell");
    cookie = shell.RegRead("HKCU\\Software\\Google\\QueryAPI_Samples\\Cookie");
  } catch(e) {
    message("Please run the register_script_sample.js script to register the samples.");
    WScript.Quit(-1);
  }

  return cookie;
}

/*
* simpleQuery() executes a Google Desktop search query on the term(s) by the
* search_string parameter.
*
* For reference, the function prototype for the Query method is:
*
*   recordset Query(cookie, query_string [, category_restrict, [, ranking]])
*
* In other words, the Query method returns a recordset object which you then
* enumerate through to obtain the results.
*
* Query's 1st parameter is the security cookie obtained from running the
*   register_script_sample.js script.
*
* Its 2nd parameter is the string containing the search query term(s).
*
* The 3rd parameter is optional. When used, it restricts the search to
* a specific category such as "email", "web", "im", "file", "contact",
* "calendar", "task", "note", "journal".
*
* Finally, the 4th parameter controls result ordering. You can specify
* ordering either provided by relevance or recency:
*
*     RELEVANCE_RANKING = 0
*     RECENCY_RANKING = 1 [default]
*
* For our example, we skip the the optional parameters and just print out
* the URLs of all the results.
*/
function simpleQuery(search_string) {
  var cookie = getRegistrationCookie();

  // Instantiate the main query api object
  var qapi = new ActiveXObject("GoogleDesktop.QueryAPI");

  // Perform the query and get a recordset object back
  var set = qapi.Query(cookie, search_string);

  // Loop through the items and print out the URLs
  var item = null;
  while ((item = set.Next()) != null)
    message(item("uri"));
}

// You'll never guess what we'll be searching for...
simpleQuery("hello world");