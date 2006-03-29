// This sample monitors the user's browsing behavior, and looks for web pages that 
// are from amazon.com. When it finds such a page, it uses a regular expression that locates the title 
// and author of the book. It then does a query for the book title and author followed by 
// the terms "inurl:book review"
// Thus it tries to show web pages that are book reviews of the book the user is viewing
// on Amazon. The MatcherQueryBuilder class can be extended to form any such query,
// and hence that's why we call this plugin the "I'm Feeling Lucky," because it depends
// on useful Google Search results for its utility.

// Setup the icons, about dialog stuff, and flags to be nice.
// the str* variables are taken from the strings.js file in the appropriate locale directory
pluginHelper.title = strTitle;
pluginHelper.SetIcons(utils.loadImage("plugin_small.gif"), utils.loadImage("plugin_large.gif"));
pluginHelper.about_text = strAboutText;
pluginHelper.SetFlags(gddPluginFlagNone, gddContentFlagHaveDetails);

// initialize the plugin
var plugin = new ImFeelingLuckyPlugin();

// this class does a Google web query using Google's SOAP API.
// see http://api.google.com/ to understand the XML output of the results
function GoogleWebQuery(searchTerms, numResults, callbackFunction) {
  // TODO(developer): change the XX key, and get your own key at http://www.google.com/apis/
  // (start at step 2 "Create a Google Account")
  var searchKey = 'XX';
  if (searchKey == 'XX') {
    utils.log(gddLogLevelError, '', 'No search key provided. Cannot execute Google query.');
    utils.alert('You need to get a Google Search key to use this sample. Visit http://www.google.com/apis/ to get a key.');
    return;
  }
  var xmlhttp = new XMLHttpRequest();  
  // create a SOAP request to get Google results
  xmlhttp.open("POST", "http://api.google.com/search/beta2", true);
  xmlhttp.onreadystatechange= onData;
  xmlhttp.setRequestHeader("Man", "POST http://api.google.com/search/beta2 HTTP/1.1");
  xmlhttp.setRequestHeader("MessageType", "CALL");
  xmlhttp.setRequestHeader("Content-Type", "text/xml");
  xmlhttp.send("<?xml version='1.0' encoding='UTF-8'?>"+"\n\n"+"<SOAP-ENV:Envelope"+
        ' xmlns:SOAP-ENV="http://schemas.xmlsoap.org/soap/envelope/"'+
        ' xmlns:xsi="http://www.w3.org/1999/XMLSchema-instance"'+
        ' xmlns:xsd="http://www.w3.org/1999/XMLSchema">'+
        '<SOAP-ENV:Body><ns1:doGoogleSearch'+
        ' xmlns:ns1="urn:GoogleSearch"'+
        ' SOAP-ENV:encodingStyle="http://schemas.xmlsoap.org/soap/encoding/">'+
        '<key xsi:type="xsd:string">' + escape(searchKey) + '</key> <q'+
        ' xsi:type="xsd:string">' + searchTerms +'</q> <start'+
        ' xsi:type="xsd:int">0</start> <maxResults'+
        ' xsi:type="xsd:int">'+ parseInt(numResults, 10) + '</maxResults> <filter'+
        ' xsi:type="xsd:boolean">true</filter> <restrict'+
        ' xsi:type="xsd:string"></restrict> <safeSearch'+
        ' xsi:type="xsd:boolean">false</safeSearch> <lr'+
        ' xsi:type="xsd:string"></lr> <ie'+
        ' xsi:type="xsd:string">latin1</ie> <oe'+
        ' xsi:type="xsd:string">latin1</oe>'+
        '</ns1:doGoogleSearch>'+
      '</SOAP-ENV:Body></SOAP-ENV:Envelope>');

  // we call the callback with the results returned from Google
  function onData() {
    if (xmlhttp.readyState == 4) { // completed?
      callbackFunction(xmlhttp.responseText);
    }
  } 
}

// this class takes a regular expression for a url. if a web page the user is viewing
// matches this regular express (url_regexp_str), then a second regular expression
// is used to extract strings from the content of the page (page_regexp_str). 
// The matches within this regular expressions are then inserted into the query_template
// (match 1 goes into the label {1} in the query template, match 2 goes in at {2}, etc..)
// and the query is executed on Google and results are returned  
function MatcherQueryBuilder(urlRegexpStr, pageRegexpStr, queryTemplate) {
  this.urlRegexp = new RegExp(urlRegexpStr, 'i');
  this.pageRegexp = new RegExp(pageRegexpStr, 'i');
  
  this.queryTemplate = queryTemplate;
  this.urlRegexpStr = urlRegexpStr;
  this.pageRegexpStr = pageRegexpStr;
  var delimiter = '####';
  
  this.IsUrlMatch = function(url) {
    return this.urlRegexp.test(url);
  }
  
  this.GetQuery = function(content) {
    var matches = this.pageRegexp.exec(content);
    if (matches != null) {
      var query = this.queryTemplate;
      // we start at 1 because matches[0] is the full string, which we don't about
      for (var i = 1; i < matches.length; ++i) {
        query = query.replace("{"+parseInt(i)+"}", matches[i]);
      }
      utils.log(gddLogLevelInfo, "", "executing query: " + query)
      return query;
    }
  }
  
  this.ToString = function() {
    var asString = this.urlRegexpStr + delimiter + this.pageRegexpStr + delimiter + this.queryTemplate;
    return asString;
  }
  
  this.FromString = function(asString) {
    var myArray = asString.split(delimiter);
    this.urlRegexp = new RegExp(myArray[0], 'i');
    this.pageRegexp = new RegExp(myArray[1], 'i');
    this.queryTemplate = myArray[2];
  }
}
  
function ImFeelingLuckyPlugin() {
  var matchers_ = new Array();
  // load up our matchers from options, which is a global variable provided by the sidebar
  if (options.GetValue("matchers_0") == "") {
    utils.log(gddLogLevelInfo, "", "no old matchers found. starting with amazon.com matcher")
    matchers_ = [
      // this default matcher looks at amazon pages, finds the book and author name, and generates a query looking for a book review
      new MatcherQueryBuilder('amazon', '<title>Amazon.com: (.+): Books(: (.+))*</title>', '"{1}" "{3}" inurl:book review') 
      ];
    SaveMatchers();
  } else {
    utils.log(gddLogLevelInfo, "", "loading old matcher data")  
    LoadMatchers();
  }
  
  // initialize our connection to the Google Desktop Event Api
  InitializeEventApi();
  
  function LoadMatchers() {
    var data = " ";
    for (var i = 0; data != ""; ++i) {
      data = options.GetValue("matchers_" + i);
      if (data != "") {
        // construct a Matcher and then load it from its string representation
        var m = new MatcherQueryBuilder("", "", "")
        m.FromString(data);
        matchers_.push(m);
      }
    }
  }

  function SaveMatchers() {
    options.Clear();
    for (var i = 0; i < matchers_.length; ++i)
      options.PutValue("matchers_" + i, matchers_[i].ToString());
  }

  function InitializeEventApi() {
    try {
      var subscription = eventPublisher.Subscribe(OnNewEvent);
      var coll = subscription.AddFilter("GoogleDesktop.FilterCollection");
      coll.filter_operator = 1; // 0 = and, 1 = or
      var schema = coll.AddFilter("GoogleDesktop.SchemaFilter");

      // Configure the schema filter to only show webpages
      // other schemas are listed in the Google Desktop documentation
      schema.Allow("Google.Desktop.WebPage");

      // Turn on the event stream
      subscription.active = true;
    } catch(e) {
      utils.log(gddLogLevelError, "", "could not hook into Event API. error: " + e.description);
      utils.alert("init: " + e.description);
    }
  }

  function OnNewEvent(eventObject) {
    if (eventObject != null) {
      var url = eventObject.GetProperty("uri");
      for (var i = 0; i < matchers_.length; ++i) {      
        if (matchers_[i].IsUrlMatch(url)) {
          var content = eventObject.GetProperty("content");
          var query = matchers_[i].GetQuery(content);
          if (query) 
            ImFeelingLuckyItem(query, url);
        }
      }
    }
  }
}

// this class creates and pushes to the sidebar a content item based on an I'm Feeling Lucky
// type search to Google
function ImFeelingLuckyItem(searchTerms, sourceUrl) {  
  var sourceDomain = getDomainName(sourceUrl);
  var googleQuery = new GoogleWebQuery(searchTerms, 2, onData);
  
  function onData(resultText) {
    var doc = new DOMDocument();
    doc.loadXML(resultText);
    var elem = doc.getElementsByTagName("item");
    for (var i = 0; i < elem.length ; i = i + 1) {
      var url, snippet, title;
      for (var node = elem[0].firstChild; node != null; node = node.nextSibling) {
        if (node.nodeName == "URL")
          url = node.firstChild.nodeValue;
        else if (node.nodeName == "snippet")
          snippet = htmlToPlainText(node.firstChild.nodeValue);
        else if (node.nodeName == "title")
          title = htmlToPlainText(node.firstChild.nodeValue);
      }
      // Since this is an "I'm Feeling Lucky" search, we show only the top
      // result, so break after the first valid result
      if (getDomainName(url) != sourceDomain)
        break;
    }
    // we don't want to show results from the same website that originally 
    // induced the query (seems sort of pointless)
    if (url != null && getDomainName(url) != sourceDomain) {
      var curItem = new ContentItem();
      curItem.source = getDomainName(url);
      curItem.layout = gddContentItemLayoutNews;
      curItem.onDetailsView = onDetailsView;
      pluginHelper.AddContentItem(curItem, gddItemDisplayInSidebar);
      
      var heading = title + ":\n" + snippet;
      curItem.heading = heading;
      curItem.snippet = snippet;     // to show in details view
      curItem.open_command = url;
    }
  }

  function onDetailsView(item) {
    var obj = new Object();
    obj.title = item.heading.substring(0, (item.heading.indexOf(":")));
    // other properties we can set in this object are 'cancel', 'details_control' and
    // 'flags'.
    return obj;
  }
}

// ----------- Utility functions ---------------

// this function is not meant to be comprehensive, but it should do a decent job
// for simple data
function htmlToPlainText (item) {

  item = item.replace(/<([^>]|\n)*>/g, '');  // remove html tags if present
  item = item.replace(/&nbsp;/g, ' ');
  item = item.replace(/&quot;/g, '"');
  item = item.replace(/&amp;/g, '&');
  item = item.replace(/&lt;/g, '<');
  item = item.replace(/&gt;/g, '>');
  return item;
}

function getDomainName(url) {
  // 1) the [^\/]+ sequence is a protocol
  // 2) then we discard the optional username and password section: [^@]*@
  // 3) we also discard a leading www.
  // 4) then we match the domain [\w=]+([\w-]+)*
  // 5) finally we make sure the domain is followed by a port :, anchor #,
  //    path /, or query ? or ;
  var matches = url.match(
    /^[^\/]+:\/\/(?:[^@]*@)?(?:www\.)?([\w-]+(?:\.[\w-]+)*)(?:[#\/:\?;].*)?$/
    );
  return matches && matches[1];
}