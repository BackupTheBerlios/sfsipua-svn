/*
 * This is a sidebar script plugin sample showing how to display HTML content in an
 * item's details view. 
 */

// This function is called when the user clicks on the item to see the details view.
// We create a details view control here, set the HTML content, indicate that it is
// HTML and return it to the sidebar for displaying within the details view frame.
function onDetailsView(item) {
  var html_for_details_view = "<html><head></head><body><h1>Flash news!</h1>";
  html_for_details_view += "Google doodles with the idea<br><font color=\"#FFFF00\">";
  html_for_details_view += "to sell noodles on froogle</font></body></html>";
  
  var control = new DetailsView();
  var tm = new Date();
  control.SetContent("Google News", tm.getVarDate(), html_for_details_view,
    true, item.layout);
  control.html_content = true;

  var details = new Object();
  details.details_control = control;
  
  return details;
}

// Setup the icons, about dialog stuff and flags.
pluginHelper.title = g_title;
pluginHelper.about_text = g_aboutText;
pluginHelper.SetIcons(utils.loadImage("plugin_small.gif"), utils.loadImage("plugin_large.gif"));
pluginHelper.SetFlags(gddPluginFlagNone, gddContentFlagHaveDetails);

// Create 1 content item
var item = new ContentItem();
item.heading = "Click here.";    // this string is shown in the item
item.onDetailsView = onDetailsView;
pluginHelper.AddContentItem(item, gddItemDisplayInSidebar); // add the item to the display

