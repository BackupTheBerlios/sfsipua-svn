// Setup the icons, about dialog stuff and flags.
pluginHelper.title = strTitle;
pluginHelper.SetIcons(utils.loadImage("plugin_small.gif"), utils.loadImage("plugin_large.gif"));
pluginHelper.about_text = strAboutText;
pluginHelper.SetFlags(gddPluginFlagNone, gddContentFlagHaveDetails);

var itemImage = utils.loadImage("sky.jpg");
var itemImageHeight = 37;  // the image's height in pixels

RefreshDisplay();

function RefreshDisplay() {
  // clear display and add new items with latest information
  pluginHelper.RemoveAllContentItems();
  for (i = 0; i < 3; ++i) {
    var item = new ContentItem();
    item.heading = strItemText;
    item.snippet = strItemSnippet;
    item.image = itemImage;
    item.onDrawItem = DrawItem;         // set handler for drawing the item
    item.onGetHeight = GetItemHeight;   // set handler for calculating the item's height
    pluginHelper.AddContentItem(item, gddItemDisplayInSidebar);
  }
}

// Called to find out the height of each content item
function GetItemHeight(item, target, graphics, width) {
  return itemImageHeight + 2 + 
    graphics.GetTextHeight(strItemText, width, 0, gddFontNormal);
}

// Called to draw each content item
function DrawItem(item, target, graphics, x, y, width, height) {
  graphics.DrawImage(x, y, width, itemImageHeight, itemImage, 100);
  y += itemImageHeight + 2;
  height -= itemImageHeight + 2;
  graphics.DrawText(x, y, width, height, item.heading, gddColorNormalText, 
    gddTextFlagCenter, gddFontNormal);
}
