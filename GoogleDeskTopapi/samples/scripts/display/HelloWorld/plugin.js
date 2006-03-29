// Setup the icons, about dialog stuff and flags.
pluginHelper.title = strTitle;
pluginHelper.SetIcons(utils.loadImage("plugin_small.gif"), utils.loadImage("plugin_large.gif"));
pluginHelper.about_text = strAboutText;
pluginHelper.SetFlags(gddPluginFlagNone, gddContentFlagHaveDetails);

// Create 1 content item and make it say hello.
var item = new ContentItem();
item.heading = strHello;    // this string is shown in the item
item.snippet = strSnippet;  // this string shown in details view
pluginHelper.AddContentItem(item, gddItemDisplayInSidebar); // add the item to the display
