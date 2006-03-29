// Setup the icons, about dialog stuff and flags to be nice.
pluginHelper.title = strTitle;
pluginHelper.SetIcons(utils.loadImage("plugin_small.gif"), utils.loadImage("plugin_large.gif"));
pluginHelper.about_text = strAboutText;
pluginHelper.SetFlags(gddPluginFlagNone, gddContentFlagHaveDetails);

pluginHelper.onShowOptionsDlg = ShowOptionsDlg; // handler for options dialog
SetDefaultOptions();

utils.setInterval(OnTimer, 1000 * 3600);  // check once every hour
OnTimer();    // update with first set of items

function SetDefaultOptions() {
  if (options.GetValue("url_0") == "") {
    PutUrls(new Array(
      "http://www.urbandictionary.com/daily.rss",
      "http://www.wordsmith.org/awad/rss1.xml",
      "http://dictionary.reference.com/wordoftheday/wotd.rss"));
  }
}

function GetUrls() {
  var arr = new Array();
  var url = " ";
  for (var i = 0; url != ""; ++i) {
    url = options.GetValue("url_" + i);
    if (url != "")
      arr.push(url);
  }
  return arr;
}

function PutUrls(urls) {
  options.Clear();
  for (var i = 0; i < urls.length; ++i)
    options.PutValue("url_" + i, urls[i]);
}

function OnTimer() {
  // issue requests for all our URLs
  var urls = GetUrls();
  for (var i = 0; i < urls.length; ++i) {
    var item = new WordItem(urls[i]);
    item = null;
  }
}

function TrimString(str) {
  str = str.replace( /^\s+/g, "" );   // strip leading whitespaces
  return str.replace( /\s+$/g, "" );  // strip trailing whitespaces
}

function GetDomainName(url) {
  var i;
  if ((i = url.indexOf("//")) != -1)
    url = url.substring(i + 2);
  if ((i = url.indexOf("/")) != -1)
    url = url.substring(0, i);
  var firstDot = url.indexOf(".");
  var secondDot = url.indexOf(".", firstDot + 1);
  while ((i = url.indexOf(".", secondDot + 1)) != -1) {
    firstDot = secondDot;
    secondDot = i;
  }
  if (firstDot != -1 && secondDot != -1) {
    return url.substring(firstDot + 1);
  }
}

//---- Functions to manage the options dialog
function ShowOptionsDlg(wnd) {
  wnd.AddControl(gddWndCtrlClassLabel, 0, "", strOptionsDlgLabel1Text, 10, 10, 380, 25);
  wnd.AddControl(gddWndCtrlClassEdit, 0, "url_edit", "", 10, 35, 300, 25);
  wnd.AddControl(gddWndCtrlClassList, 0, "url_list", GetUrls(), 10, 70, 300, 100);
  var add_btn = wnd.AddControl(gddWndCtrlClassButton, 0, "",
    strOptionsDlgAddButtonText, 320, 35, 70, 25);
  var remove_btn = wnd.AddControl(gddWndCtrlClassButton, 0, "",
    strOptionsDlgRemoveButtonText, 320, 70, 70, 25);

  // handlers
  wnd.onClose = OptionsDlgClosed;
  add_btn.onClicked = AddButtonClicked;
  remove_btn.onClicked = RemoveButtonClicked;
}

function AddButtonClicked(wnd, ctrl) {
  var edit = wnd.GetControl("url_edit");
  var url = TrimString(edit.value);
  if (url != "") {
    if (url.substring(0, 7) != "http://")
      url = "http://" + url;
    var list = wnd.GetControl("url_list");
    var urls = new VBArray(list.text).toArray();
    urls.push(url);
    list.text = urls;
    edit.value = "";
  }
}

function RemoveButtonClicked(wnd, ctrl) {
  var list = wnd.GetControl("url_list");
  var url_to_remove = list.value;
  var urls = new VBArray(list.text).toArray();
  for (var i = 0; i < urls.length; ++i) {
    if (urls[i] == url_to_remove) {
      urls.splice(i, 1);
      break;
    }
  }
  list.text = urls;
  if (i < urls.length)
    list.value = urls[i];  // select next one in list
}

function OptionsDlgClosed(wnd, code) {
  if (code == gddIdOK) {
    var list = wnd.GetControl("url_list");
    var urls;
    if (list.text == null)
      urls = new Array();
    else
      urls = new VBArray(list.text).toArray();
    PutUrls(urls);
    pluginHelper.RemoveAllContentItems(); // since some may have been deleted
    OnTimer();  // to refresh items and add again
  }
}

//---- A class to manage the requests and callbacks of an item
function WordItem(url) {
  // send request to webserver for data
  var source = GetDomainName(url);
  var http = new XMLHttpRequest();
  http.onreadystatechange = OnData;
  http.open("GET", url, true);
  http.send();

  function OnData() {
    if (http.readyState == 4) { // completed?
      // parse the xml data received
      var doc = new DOMDocument();
      doc.loadXML(http.responseText);

      // read the word title, description and link from the xml
      var title, desc, link;
      var elem = doc.getElementsByTagName("item");
      if (elem != null && elem.length > 0) {
        for (var node = elem[0].firstChild; node != null; node = node.nextSibling) {
          if (node.nodeName == "title")
            title = node.firstChild.nodeValue;
          if (node.nodeName == "description")
            desc = node.firstChild.nodeValue;
          if (node.nodeName == "link")
            link = node.firstChild.nodeValue;
        }
        desc = desc.replace(/<([^>]|\n)*>/g,'');  // remove html tags if present
        desc = desc.replace(/&nbsp;/g, ' ');
        desc = desc.replace(/&quot;/g, '"');
        desc = desc.replace(/&amp;/g, '&');
        
        var i;
        if ((i = title.indexOf(":")) != -1)
          title = title.substring(0, i);
        if ((i = desc.indexOf(":")) != -1) {
          var phrase = desc.substring(0, i);
          if (phrase == title) {
            desc = desc.substring(i + 1);
          }
        }
      }

      if (title != null) {  // successfully parsed?
        // get the currently shown items and check if our word is in there. If so just
        // update it with the new definition, if not add to the beginning.
        var vbarrItems = pluginHelper.content_items;
        if (vbarrItems != null) {
          var items = vbarrItems.toArray();
          for (var i = 0; i < items.length; i++) {
            if (items[i].source == source)
              break;
          }

          var curItem = null;
          if (i == items.length) {
            curItem = new ContentItem();  // not found so add it fresh
            curItem.source = source;
            curItem.layout = gddContentItemLayoutNews;
            curItem.onDetailsView = OnDetailsView;
            pluginHelper.AddContentItem(curItem, gddItemDisplayInSidebar);
          } else {
            curItem = items[i]; // update the existing item
          }
          // update item's data with latest
          str = title + ":\n" + desc;
          curItem.heading = str;
          curItem.snippet = str;     // to show in details view
          curItem.open_command = link;
        }
      }
      http = null;  // free the http object
    }
  }
}

function OnDetailsView(item) {
  var obj = new Object();
  obj.title = item.heading.substring(0, (item.heading.indexOf(":")));
  // other properties we can set in this object are 'cancel', 'details_control' and
  // 'flags'.
  return obj;
}
