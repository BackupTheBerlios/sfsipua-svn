/**
* remove_from_index.js
*
* Demonstrates how to use a record object's RemoveFromIndex() method to
* delete the object from the Google Desktop index.
*
* RemoveFromIndex() takes a single bool parameter. If true, it deletes all
* cached versions of the matching document.  If false, it only removes the
* matching document's current/latest version.
*
* To delete all previous versions of a document and *not* the current version,
* use the record item's 'versions' collection.
*
* The versions collection has one function, Item(index) and one property,
* 'count'. Item(index) returns a record object from the collection given
* a zero based index value.  To only remove a particular version of an
* indexed document, use the Item(index) method to get the version you want to
* remove and then call the RemoveFromIndex() method on the returned record
* object, passing false as the remove_all_versions parameter.
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
* registred. It then displays an error message and terminates the currently
* running script.
*/
function getRegistrationCookie() {
  var cookie = 0;

  try {
    var shell = new ActiveXObject("WScript.Shell");
    cookie = shell.RegRead("HKCU\\Software\\Google\\QueryAPI_Samples\\Cookie");
  } catch(e) {
    message("Please run the register_script_sample.js script to register the samples");
    WScript.Quit(-1);
  }

  return cookie;
}

// Get and keep our registration cookie around for the following functions
var g_securityCookie = getRegistrationCookie();

/**
* Removes a single file from the index by using the RemoveFromIndex() function.
* The 'path' argument is a string containing a file path, such as
* "C:\\gd-temp\\my_temp_file.txt".
*
* In order to use RemoveFromIndex(), the caller must have registered via
* the Query API with read/write access. If the caller does not have write
* access, RemoveFromIndex() will throw an error.
*/
function removeFileFromIndex(path) {
  var query = new String();
  // Lower-case the path so that string comparison is slightly simpler
  var path_lower = new String(path.toLowerCase());

  // locate the index of the last back slash in the path.
  // this is so that we can separate the folder path from the file name.
  var idx = path_lower.lastIndexOf("\\");
  if (idx == -1) {
    message("Invalid path: " + path_lower);
    return false;
  }

  // Now build the query so that we restrict the search to only give us
  // results for files that exist in the folder where our file is
  // and to only include documents that match with the name of the file.
  // In most cases, we will only get a single record back, but
  // in some cases we can get more than that, so we'll check each
  // returned record below.
  query = "in:\"" + path_lower.substr(0, idx) + "\" \"" +
          path_lower.substr(idx + 1) + "\"";

  var q = new ActiveXObject("GoogleDesktop.QueryAPI");
  var set = q.Query(g_securityCookie, query, "file");

  var ret = false;

  var rec = null;
  while ((rec = set.Next()) != null) {
    var uri = new String(rec("uri")).toLowerCase();
    if (uri == path_lower) {
      // If the g_securityCookie was registered with read-only access,
      // this call will generate an error.

      //RemoveFromIndex() takes a single bool parameter. If true, it deletes
      //all cached versions of the matching document.  If false, it only
      //removes the matching document's current/latest version.

      rec.RemoveFromIndex(true);
      ret = true;
      break;
    }
  }

  if (!ret)
    message("Unable to find file '" + path + "' in index");

  return ret;
}

/*
* removeAllInQuery() is a utility function that removes everything matching
* a specified query and returns the number of records affected by the function.
* You can use the category parameter to restrict the search results to a
* specific category such as web, file, im, etc.
*
*/
function removeAllInQuery(query, category) {
  var q = new ActiveXObject("GoogleDesktop.QueryAPI");
  var set = q.Query(g_securityCookie, query, category);

  var rec = null;
  while ((rec = set.Next()) != null)
    //removes all cached versions of the result from the index.
    rec.RemoveFromIndex(true);

  // Since we've gone through all the records in the record set,
  // the 'count' property now holds the exact number of matching records.
  return set.count;
}

/*
* removeFilesInFolderFromIndex finds the collection of files in a specific
* folder and removes it from the index.
*/
function removeFilesInFolderFromIndex(path) {
  // Use the 'in' keyword to pick the files to remove from the index
  // This will not give us any files in subfolders of the specified folder.
  var query = "in:\"" + path + "\"";
  var removed = removeAllInQuery(query, "file");
  message("Removed " + removed + " files in folder " + path);
}

/*
* removeFolderTreeFromIndex finds the collection of files under a specific
* folder tree and removes it from the index.
*/
function removeFolderTreeFromIndex(path) {
  // The 'under' keyword allows us to query for files in a subtree.
  var query = "under:\"" + path + "\"";
  var removed = removeAllInQuery(query, "file");
  message("Removed " + removed + " files under folder tree " + path);
}

/*
* removeItemsFromSite removes a collection of items from a given web site
* from the index.
*/
function removeItemsFromSite(site) {
  // The 'site' keyword allows us to restrict the search to items from
  // a certain web site
  var query = "site:\"" + site + "\"";
  var removed = removeAllInQuery(query, "web");
  message("Removed " + removed + " items from site " + site);
}

////////////////////////////////////////////////////////////////////////////////

function main() {
  // Remove some items.  For demonstration purposes, we're using a 'gd-temp'
  // folder to avoid accidents if somebody accidentally runs this script.
  // You should modify the parameters to meet your deletion needs.
  removeFileFromIndex("C:\\gd-temp\\my_temp_file.txt");
  removeFilesInFolderFromIndex("C:\\gd-temp");
  removeFolderTreeFromIndex("C:\\gd-temp");
  removeItemsFromSite("www.w3.org");
}

main();