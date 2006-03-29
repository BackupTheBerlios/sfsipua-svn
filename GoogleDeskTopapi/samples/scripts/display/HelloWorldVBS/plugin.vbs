' Setup the icons, about dialog stuff and flags to be nice.
pluginHelper.title = strTitle
pluginHelper.SetIcons utils.LoadImage("plugin_small.gif"), utils.LoadImage("plugin_large.gif")
pluginHelper.about_text = strAboutText
pluginHelper.SetFlags gddPluginFlagNone, gddContentFlagHaveDetails

' Create 1 content item and make it say hello.
Dim item
Set item = CreateObject("GoogleDesktop.ContentItemHelper")
item.heading = strHello    ' this string is shown in the item
item.snippet = strSnippet  ' this string shown in details view
pluginHelper.AddContentItem item, gddItemDisplayInSidebar ' add the item to the display
