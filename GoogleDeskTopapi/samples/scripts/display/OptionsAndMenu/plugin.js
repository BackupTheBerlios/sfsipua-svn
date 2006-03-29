// In this sample the plugin will show 3 items in its menu, one for each item layout.
// When you select each of the menu items the displayed items will change their layout
// to the selected one. This setting will also be saved to the options store so 
// it will persist across sessions when you close and restart the sidebar.

var menuItems = new Array("NoWrap layout", "Email layout", "News layout");
  
// Setup the icons, about dialog stuff and flags.
pluginHelper.title = strTitle;
pluginHelper.SetIcons(utils.loadImage("plugin_small.gif"), utils.loadImage("plugin_large.gif"));
pluginHelper.about_text = strAboutText;
pluginHelper.SetFlags(gddPluginFlagNone, gddContentFlagHaveDetails);
pluginHelper.onAddCustomMenuItems = AddCustomMenuItems;  // handler to add menu items

SetDefaultOptions();
RefreshDisplay();

function SetDefaultOptions() {
  if (options.GetValue("item_layout") == "")
    options.PutValue("item_layout", gddContentItemLayoutNowrapItems);
}

function RefreshDisplay() {
  var itemLayout = options.GetValue("item_layout");
    
  // remove existing and add new items.
  pluginHelper.RemoveAllContentItems();
  for (var i = 3; i >= 1; --i) {
    // get local time and adjust to get UTC time.
    var tm = new Date();
    tm.setMinutes(tm.getMinutes() + tm.getTimezoneOffset());
    
    var item = new ContentItem();
    item.heading = strItemText + i;
    item.snippet = strItemSnippet;
    item.time_created = tm.getVarDate();
    item.layout = itemLayout;
    pluginHelper.AddContentItem(item, gddItemDisplayInSidebar);
  }
}

function AddCustomMenuItems(menu) {
  // Add the various item layouts as menu items and check the currently selected one
  var itemLayout = options.GetValue("item_layout");
  for (var i = 0; i < menuItems.length; ++i) {
    if (i == itemLayout) {
      menu.AddItem(menuItems[i], gddMenuItemFlagChecked, MenuItemClicked);
    } else {
      menu.AddItem(menuItems[i], 0, MenuItemClicked);
    }
  }    
}

function MenuItemClicked(item) {
  // find which one was clicked and switch items to the chosen layout.
  var itemLayout = gddContentItemLayoutNowrapItems;
  for (var i = 0; i < menuItems.length; ++i) {
    if (item == menuItems[i]) {
      itemLayout = i;
    }
  }
  // save the option selected by the user in our options store
  options.PutValue("item_layout", itemLayout);
  RefreshDisplay();
}

