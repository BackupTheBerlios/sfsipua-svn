/*
* lucky.js
*
* A slight modification of the simple_query.js example to create a
* "I'm feeling lucky" style query script.
*
* Before looking at this example, you should familiarize yourself with the
* simple_query.js script, specifically how the underlying Query method
* works.
*
* This example runs a query, uses the relevance algorithm to select the first
* matching result record, and then writes out that result's indexed contents.
*/

// The two different types of search result ranking
var RELEVANCE_RANKING = 0;
var RECENCY_RANKING = 1;  // the default

// message() borrowed from simple_query.js
function message(text) {
  WScript.Echo(text);
}

// getRegistrationCookie() borrowed from simple_query.js
function getRegistrationCookie() {
  var cookie = 0;

  try {
    var shell = new ActiveXObject("WScript.Shell");
    cookie = shell.RegRead("HKCU\\Software\\Google\\QueryAPI_Samples\\Cookie");
  } catch(e) {
    message("please run the register_script_sample.js script to register the samples");
    WScript.Quit(-1);
  }

  return cookie;
}

/*
* lucky() executes a query and then displays the contents of its most relevant
* Desktop search result. The key difference between this and simpleQuery() is
* that the call to Query() includes a value for its optional fourth parameter,
* which determines which ranking order to use on the query results. It then
* only displays the first result, which is what the relevance algorithm
* considered the most relevant.
*
* Also distinct from simpleQuery(), lucky() displays the item's URL and its
* content, while simpleQuery() just displays result URLs.
*/
function lucky(query) {
  var cookie = getRegistrationCookie();
  var qapi = new ActiveXObject("GoogleDesktop.QueryAPI");

  // Use relevance ranking of query results instead of the default date ranking
  var ignore;
  var set = qapi.Query(cookie, query, ignore, RELEVANCE_RANKING);

  var item = set.Next()
  if (item != null) {
    // First output the URI of the item we found
    message(item("uri"));
    // Now output the text representation of the content
    message(item("text_content"));
    // Alternatively, we could output the content in its native form
    // message(item("content"));
  } else {
    message("no item found!");
  }
}

lucky("hello world");
