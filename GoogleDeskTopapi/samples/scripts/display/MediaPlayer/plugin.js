// Google Desktop Media Player plugin
// © 2005 Google. All rights reserved.

// Global Objects
var playerObject;   // the windows media player

// UI controls
var imgPlay = utils.LoadImage("play.gif");
var imgPause = utils.LoadImage("pause.gif");
var ctrlPlayPause, ctrlStop, ctrlPrev, ctrlNext, ctrlFileOpen;
var isPlaying = false;
var isOpenFileCalled = false;
var ourPlaylist;

// Album info
var albumInfoObject;
var timerToUpdateTitle;

// options
var doLoop, doShuffle;

pluginHelper.title = strTitle;
pluginHelper.SetFlags(gddPluginFlagNone, gddContentFlagManualLayout);
pluginHelper.SetIcons(utils.loadImage("plugin_small.gif"), utils.loadImage("plugin_large.gif"));
pluginHelper.about_text = strAboutText;
pluginHelper.onAddCustomMenuItems = AddCustomMenuItems;
pluginHelper.onDisplayStateChange = UpdateItemPositions;
LoadOptions();
CreateControlPanel();

playerObject = new ActiveXObject("WMPlayer.OCX");
playerObject.uiMode = "none";
playerObject.settings.setMode("autoRewind", true);
ourPlaylist = playerObject.newPlaylist("", "");
playerObject.currentPlaylist = ourPlaylist;

function SaveOptions() {
  options.PutValue("loop", doLoop);
  options.PutValue("shuffle", doShuffle);
}

function LoadOptions() {
  if (options.GetValue("loop") == "") { // first time will be empty.
    doLoop = 0;
    doShuffle = 0;
    SaveOptions();
  } else {
    doLoop = options.GetValue("loop");
    doShuffle = options.GetValue("shuffle");
  }
}

// Adds our plugin specific items to the menu
function AddCustomMenuItems(menu) {
  menu.AddItem(strMenuItemLoop, 
    (doLoop == 1) ? gddMenuItemFlagChecked : 0, OnMenuClicked);
  menu.AddItem(strMenuItemShuffle, 
    (doShuffle == 1) ? gddMenuItemFlagChecked : 0, OnMenuClicked);
}

function OnMenuClicked(itemText) {
  if (itemText == strMenuItemLoop) {
    doLoop = 1 - doLoop;
    playerObject.settings.setMode("loop", doLoop);
  } else if (itemText == strMenuItemShuffle) {
    doShuffle = 1 - doShuffle;
    playerObject.settings.setMode("shuffle", doShuffle);
    if (isPlaying) {
      // stop and start playing again in the new mode
      PlayPauseButtonClicked(null, null);
      PlayPauseButtonClicked(null, null);
    }
  }
  SaveOptions();
}

// Function that creates content items which are controls for the playback
function CreateControlPanel() {
  // Create the Album info Content Item
  albumInfoObject = new ContentItem();
  albumInfoObject.heading = strInstructions;
  albumInfoObject.layout = gddContentItemLayoutNews;
  albumInfoObject.flags = gddContentItemFlagStatic; // dont take clicks
  pluginHelper.AddContentItem(albumInfoObject, gddItemDisplayInSidebar);
  
  // Create Controls
  ctrlFileOpen = new ContentItem();
  ctrlPlayPause = new ContentItem();
  ctrlStop = new ContentItem();
  ctrlPrev = new ContentItem();
  ctrlNext = new ContentItem();
  
  // Set the images
  ctrlFileOpen.image = utils.LoadImage("open.gif");
  ctrlStop.image = utils.LoadImage("stop.gif");
  ctrlPrev.image = utils.LoadImage("prev.gif");
  ctrlNext.image = utils.LoadImage("next.gif");
  ctrlPlayPause.image = imgPlay;
  
  // Tooltips
  ctrlFileOpen.tooltip = strTooltipOpen;
  ctrlStop.tooltip = strTooltipStop;
  ctrlPrev.tooltip = strTooltipPrev;
  ctrlNext.tooltip = strTooltipNext;
  ctrlPlayPause.tooltip = strTooltipPlay;

  // OnDetailsview is called on single clicks, so use that to do various tasks
  ctrlFileOpen.onDetailsView = OpenFileButtonClicked;
  ctrlPlayPause.onDetailsView = PlayPauseButtonClicked;
  ctrlStop.onDetailsView = StopButtonClicked;
  ctrlPrev.onDetailsView = PrevButtonClicked;
  ctrlNext.onDetailsView = NextButtonClicked;

  // Now add the items
  pluginHelper.SetFlags(gddPluginFlagNone, gddContentFlagManualLayout + gddContentFlagHaveDetails);
  pluginHelper.AddContentItem(ctrlFileOpen, gddItemDisplayInSidebar);
  pluginHelper.AddContentItem(ctrlPlayPause, gddItemDisplayInSidebar);
  pluginHelper.AddContentItem(ctrlStop, gddItemDisplayInSidebar);
  pluginHelper.AddContentItem(ctrlPrev, gddItemDisplayInSidebar);
  pluginHelper.AddContentItem(ctrlNext, gddItemDisplayInSidebar);
}

function UpdateItemPositions() {
  // Get the current window width and layout all items accordingly
  var infoItemHeight = 40;
  var imageHeight = 22;
  var imageWidth = 22;
  var horizontalGap = 4;
  var posX = (pluginHelper.window_width - imageWidth * 5 - horizontalGap * 4) / 2;

  albumInfoObject.SetRect(horizontalGap, horizontalGap, 
    pluginHelper.window_width - horizontalGap * 2, infoItemHeight);
  ctrlFileOpen.SetRect(posX, horizontalGap + infoItemHeight, 
    imageWidth, imageHeight);
  ctrlPlayPause.SetRect(posX + (horizontalGap + imageWidth), 
    horizontalGap + infoItemHeight, imageWidth, imageHeight);
  ctrlStop.SetRect(posX + (horizontalGap + imageWidth) * 2, 
    horizontalGap + infoItemHeight, imageWidth, imageHeight);  
  ctrlPrev.SetRect(posX + (horizontalGap + imageWidth) * 3,
    horizontalGap + infoItemHeight, imageWidth, imageHeight);
  ctrlNext.SetRect(posX + (horizontalGap + imageWidth) * 4, 
    horizontalGap + infoItemHeight, imageWidth, imageHeight);
}

// refreshes the metadata in album info as the player switches to next song
function refreshMediaInfo() {
  if (playerObject.currentMedia != null) { // have we selected any file at all?
    albumInfoObject.heading = playerObject.currentMedia.name;
    if (playerObject.controls.currentPositionString != "") {
      albumInfoObject.heading += " [" + playerObject.controls.currentPositionString +
        " / " + playerObject.currentMedia.durationString + "]";
    }
  }
}

// opens the file selection dialog and queues the selected file for playback
function OpenFileButtonClicked() {
  var fileDialog = new ActiveXObject("UserAccounts.CommonDialog");
  fileDialog.Filter = "Media Files/Playlists|*.wav;*.mp3;*.avi;*.wma;*.mid;*.asx;*.wax;*.m3u;*.wpl;*.wvx;*.wmx|All Files|*.*";
  fileDialog.FilterIndex = 1;
  
  if (fileDialog.ShowOpen() != 0) {
    var playlist = null;
    var mediaItem = null;
    
    try {
      playlist = playerObject.newPlaylist("", fileDialog.FileName);
    } catch (er) {
    }

    if (playlist) {
      ourPlaylist = playlist;
      playerObject.currentPlaylist = ourPlaylist;
    } else {
      try {
        mediaItem = playerObject.newMedia(fileDialog.FileName);
      } catch (er) {
      }      
      if (mediaItem) {
        ourPlaylist.appendItem(mediaItem);
      }
    }
    if (!isOpenFileCalled || !isPlaying) {
      // start playing
      isOpenFileCalled = true;
      PlayPauseButtonClicked(null, mediaItem);
    }
  }
}

// Handle play/pause button clicks
function PlayPauseButtonClicked(contentItem, media) {
  if (isPlaying == false) {
    if (isOpenFileCalled) { // has the user selected any file at all?
      isPlaying = true;
      ctrlPlayPause.image = imgPause;
      ctrlPlayPause.tooltip = strTooltipPause;
      if (media) {
        playerObject.controls.playItem(media);
      } else {
        playerObject.controls.play();
      }
      OnAlbumInfoTimer(); // update album info and set timer
    } else {
      OpenFileButtonClicked();  // since no file has been selected bring up the dialog
    }
  } else {
    isPlaying = false;
    playerObject.controls.pause();
    ctrlPlayPause.image = imgPlay;
    ctrlPlayPause.tooltip = strTooltipPlay;
    ClearAlbumInfoTimer();
  }
}

// Update Album info through a timer
function OnAlbumInfoTimer() {
  refreshMediaInfo(); // Update Album info

  // stopped, or media ended states mean a single state to us.
  if (playerObject.playState == 1 || playerObject.playState == 8) {
    StopButtonClicked();
    ClearAlbumInfoTimer();
  } else if (timerToUpdateTitle == null) {
    timerToUpdateTitle = utils.setInterval(OnAlbumInfoTimer, 1000);
  }
}

// Switch off the periodic event that updates album info 
function ClearAlbumInfoTimer() {
  if (timerToUpdateTitle != null)
    utils.clearInterval(timerToUpdateTitle);
  timerToUpdateTitle = null;
}

// Handler for Stop button
function StopButtonClicked() {
  ClearAlbumInfoTimer();
  playerObject.controls.stop();
  isPlaying = false;
  ctrlPlayPause.image = imgPlay;
}

// Handler for Rewind button
function PrevButtonClicked() {
  playerObject.controls.previous();
}

// Handler for Forward button
function NextButtonClicked() {
  playerObject.controls.next();
}
