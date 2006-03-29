/*
* item_count.js
*
* Executes a query and displays the number of matching records.
*
* Before looking at this example, you should familiarize yourself with the
* simple_query.js script, specifically how the underlying Query method
* works.
*
* The recordset returned by the Query method, in addition to containing the
* query results, also has 'readyState' and 'count' properties.
*
* The readyState property has one of these values:
*
*  0 = GD_QRS_UNINITIALIZED
*  1 = GD_QRS_LOADING
*  2 = GD_QRS_COMPLETE
*
* By default, a recordset is populated asynchronously. Its readyState
* will start out as GD_QRS_UNINITIALIZED, then, as items are fetched from disk
* and made available to the current process, it changes to GD_QRS_LOADING and,
* when all matching items have been found, moves to its final GD_QRS_COMPLETE
* value.
*
* During all this, you can start iterating through and processing any already
* fetched records while matches continue to be fetched in the background.
*
* However, this has the side effect that the count property value will be an
* estimate until the readyState property value is GD_QRS_COMPLETE.
*
* In this example, we're only interested in knowing the exact number of
* matching records. So instead of using the Query method, we use QueryEx,
* which doesn't immediately execute the query but instead returns a
* query object that allows us to change the default options before
* executing the query.
*
* In this case, we turn off the aforementioned asynchronous result item
* loading.  This has the effect that the call to Execute() blocks until
* the recordset object contains all the returned records from the search query.
*/

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

// Keep our registration cookie around for the below function
var g_securityCookie = getRegistrationCookie();

/*
* showItemCount() uses the QueryEx method to get a query object which is
* modified prior to its execution. The more commonly used Query method
* executes a query with all the default attributes applied and returns a
* recordset object. By using QueryEx, we can turn off asynchronous result
* item fetching so that by the time the Execute() call completes, all results
* will have been fetched. Thus, at that time, the recordset's count property
* will contain the correct value for the total number of results.
*
* prototype for QueryEx:
*   QueryObject QueryEx(query_string [, category_restrict, [, ranking]])
*/
function showItemCount(query) {
  var q = new ActiveXObject("GoogleDesktop.QueryAPI");

  // Call the QueryEx method so that we can turn off the asynchronous
  // loading of record items.  It's not needed since all we're interested
  // in is the total item count.
  var qx = q.QueryEx(g_securityCookie, query);

  // Turn off the default asynchronous behavior.
  qx.SetOption("async", false);

  // Execute the query synchronously and get back a recordset object
  var set = qx.Execute();
  // Get the number of results from the recordset's count property.
  message("Total matches for '" + query + "': " + set.count);
}

// See how many items match a query
showItemCount("\"google desktop\"");