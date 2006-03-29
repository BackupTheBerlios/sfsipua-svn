// Google Desktop Tic Tac Toe game.
// Original game code from http://www.geocities.com/SiliconValley/7116/
var imgSplash = utils.loadImage("splash.gif");
var imgOnline = utils.loadImage("online.gif");
var imgAway = utils.loadImage("away.gif");
var imgBusy = utils.loadImage("busy.gif");
var imgX = utils.loadImage("x_32.gif");
var imgO = utils.loadImage("o_32.gif");
var imgB = utils.loadImage("b_32.gif");
var yourWins = 0, compWins = 0, ties = 0;
var squares = new Array();

// states:
var stateMainMenu = 0;
var stateSinglePlayerPlaying = 1;
var stateMultiPlayerPickFriends = 2;
var stateMultiPlayerWaiting = 3;
var stateMultiPlayerPlaying = 4;

// Talk messages
var messageStartGame = "start";
var messageCancelGame = "cancel";
var messageAcceptGame = "yes";
var messageDeclineGame = "no";

// player
var playerX = "X";
var playerO = "O";

var state = stateMainMenu;
var can_click = true;
var friend_user_id = "";
var step = 0;
var diff = 3;
var blocksize = 38;
var textheight = 18;

// Setup the icons, about dialog and flags.
pluginHelper.title = strTitle;
pluginHelper.SetIcons(utils.loadImage("plugin_small.gif"), utils.loadImage("plugin_large.gif"));
pluginHelper.about_text = strAboutText;
pluginHelper.SetFlags(gddPluginFlagNone, gddContentFlagHaveDetails);
pluginHelper.OnDisplayStateChange = OnDisplayStateChange;
googleTalk.onReceiveTalkData = OnReceiveTalkData;

AddItems();

function AddItem(heading, snippet, flags, onDetailsView) {
  var item = new ContentItem();
  if (heading != null)
    item.heading = heading;

  if (snippet != null)
    item.snippet = snippet;

  if (flags != null)
    item.flags = flags;

  if (onDetailsView != null)
    item.onDetailsView = onDetailsView;

  pluginHelper.AddContentItem(item, gddItemDisplayInSidebar);
}

function DrawMenu() {
  can_click = true;
  pluginHelper.RemoveAllContentItems();

  var splash = new ContentItem();
  splash.image = imgSplash;
  splash.flags = gddContentItemFlagStatic;
  var xpos = Math.max(0, pluginHelper.window_width / 2 - 50);
  splash.SetRect(xpos, 0, 99, 77);
  pluginHelper.AddContentItem(splash, gddItemDisplayInSidebar);

  var single = new ContentItem();
  single.heading = strPlayAgainstComputer;
  single.onDetailsView = OnSingle;
  single.flags = gddContentItemFlagNoRemove;
  single.SetRect(0, 80, pluginHelper.window_width, textheight);
  pluginHelper.AddContentItem(single, gddItemDisplayInSidebar);

  var multi = new ContentItem();
  multi.heading = strPlayAgainstFriend;
  multi.onDetailsView = OnMulti;
  multi.flags = gddContentItemFlagNoRemove;
  multi.SetRect(0, 98, pluginHelper.window_width, textheight);
  pluginHelper.AddContentItem(multi, gddItemDisplayInSidebar);

  // Add an empty item just to get the panel height right
  var temp = new ContentItem();
  temp.flags = gddContentItemFlagStatic;
  temp.SetRect(0, 116, pluginHelper.window_width, textheight);
  pluginHelper.AddContentItem(temp, gddItemDisplayInSidebar);
}

function DrawFriends() {
  var friends = googleTalk.friends.toArray();

  // First check if no friends with this panel are online
  var friends_with_sidebar = 0;
  for (var i = 0; i < friends.length; i++) {
    if (friends[i].has_sidebar)
      friends_with_sidebar++;
  }
  
  if (!friends_with_sidebar) {
    pluginHelper.SetFlags(gddPluginFlagNone, gddContentFlagHaveDetails);
    // no friends online, so tell the user and put a main menu link
    AddItem(strGoToMainMenu, null, gddContentItemFlagNoRemove, OnMainMenu);
    AddItem(strNoFriendsOnline, null, gddContentItemFlagStatic, null);
    return;
  }

  pluginHelper.SetFlags(gddPluginFlagNone, gddContentFlagHaveDetails | gddContentFlagManualLayout);
  pluginHelper.max_content_items = Math.max(25, friends_with_sidebar * 2 + 1);

  // add cancel button
  var cancel = new ContentItem();
  cancel.heading = strCancel;
  cancel.onDetailsView = OnCancelDontNotify;
  cancel.flags = gddContentItemFlagNoRemove;
  cancel.SetRect(0, 0, pluginHelper.window_width, textheight);
  pluginHelper.AddContentItem(cancel, gddItemDisplayInSidebar);

  // add an item for each friend
  var ypos = textheight;
  for (var i = 0; i < friends.length; i++) {
    if (!friends[i].has_sidebar)
      continue;

    var friend = new ContentItem();
    friend.heading = friends[i].name;
    friend.snippet = friends[i].user_id;
    friend.onDetailsView = OnStartMulti;
    friend.flags = gddContentItemFlagNoRemove;
    friend.SetRect(17, ypos, pluginHelper.window_width, textheight);
    pluginHelper.AddContentItem(friend, gddItemDisplayInSidebar);
    
    var icon = new ContentItem();
    if (friends[i].status == gddFriendStatusOnline) {
      icon.image = imgOnline;
    } else if (friends[i].status == gddFriendStatusBusy) {
      icon.image = imgBusy;
    } else {
      icon.image = imgAway;
    }

    icon.flags = gddContentItemFlagStatic;
    icon.SetRect(1, ypos, 16, 16);
    pluginHelper.AddContentItem(icon, gddItemDisplayInSidebar);
    ypos += textheight;
  }
}

// draw the board
function DrawBoard() {
  step = 0;
  pluginHelper.RemoveAllContentItems();

  var items = new Array();
  for (var i = 0; i < 3; ++i) {
    for (var j = 0; j < 3; ++j) {
      squares[items.length] = "";
      var item = new ContentItem();
      item.image = imgB;
      item.flags = gddContentItemFlagNoRemove;
      item.snippet = items.length;
      item.onDetailsView = OnClicked;
      items.push(item);
    }
  }
  
  // add cancel button
  var cancel = new ContentItem();
  cancel.heading = strCancel;
  cancel.onDetailsView = OnCancelNotify;
  cancel.flags = gddContentItemFlagNoRemove;
  cancel.SetRect(0, 3 * blocksize, pluginHelper.window_width, textheight);
  items.push(cancel);

  pluginHelper.content_items = items;
  ResizeBoard();
}

function ResizeBoard() {
  var margin = Math.max(0, (pluginHelper.window_width - 3 * blocksize) / 2);
  var items = pluginHelper.content_items.toArray();
  for (var i = 0; i < items.length; ++i) {
    var index = items[i].snippet;
    if (index != "") {
      // must be a board item, since they have 0...8 as their snippet
      var x = (index % 3);
      var y = Math.floor(index / 3);
      items[i].SetRect(margin + x * blocksize, y * blocksize, blocksize, blocksize);
    }
  }
}

function AddGameStatus(status_string) {
  step = -1;
  var items = pluginHelper.content_items.toArray();
  for (var i = 0; i < items.length; ++i) {
    if (items[i].heading == strCancel) {
      items[i].heading = status_string + "  " + strGoToMainMenu;
      items[i].onDetailsView = OnMainMenu;
    } else if (items[i].snippet != "") {
      // disable clicking on the board pieces
      items[i].flags = gddContentItemFlagStatic;
    }
  }
}

function AddItems() { 
  pluginHelper.RemoveAllContentItems();
  if (state == stateMainMenu) {
    // show the single/multi-player selection items
    pluginHelper.SetFlags(gddPluginFlagNone, gddContentFlagHaveDetails | gddContentFlagManualLayout);
    DrawMenu();
  } else if (state == stateSinglePlayerPlaying) {
    // starting a single player game
    pluginHelper.SetFlags(gddPluginFlagNone, gddContentFlagHaveDetails | gddContentFlagManualLayout);
    DrawBoard();
  } else if (state == stateMultiPlayerPickFriends) {
    // pick a friend for a multi-player game
    DrawFriends();
  } else if (state == stateMultiPlayerWaiting) {
    // Tell the user that we're waiting for a response from their friend,
    // and allow them to cancel the request.
    pluginHelper.SetFlags(gddPluginFlagNone, gddContentFlagHaveDetails);
    AddItem(strCancel, null, gddContentItemFlagNoRemove, OnCancelNotify);
    AddItem(strWaitingForResponse, null, gddContentItemFlagStatic, null);
  } else if (state == stateMultiPlayerPlaying) {
    // Starting a game, so draw the board
    pluginHelper.SetFlags(gddPluginFlagNone, gddContentFlagHaveDetails | gddContentFlagManualLayout);
    DrawBoard()
  }
}

function OnSingle(item) {
  // Start a single player game
  state = stateSinglePlayerPlaying;
  AddItems();
}

function OnMulti(item) {
  // Add list of friends from Talk
  state = stateMultiPlayerPickFriends;
  AddItems();
}

function OnStartMulti(item) {
  // Start a multi-player game
  state = stateMultiPlayerWaiting;
  friend_user_id = item.snippet;

  try {
    googleTalk.SendTalkData(friend_user_id, messageStartGame);
    AddItems();
  } catch (e) {
    utils.alert(strConnectionError);
    OnMainMenu();
  }
}

function OnCancelNotify(item) {
  CancelGame(true);
}

function OnCancelDontNotify(item) {
  CancelGame(false);
}

function CancelGame(send_message) {
  if (friend_user_id != "") {
    if (send_message) {
      try {
        googleTalk.SendTalkData(friend_user_id, messageCancelGame);
      } catch (e) {
      }
    }

    friend_user_id = "";
  }

  OnMainMenu();
}

function OnMainMenu() {
  state = stateMainMenu;
  AddItems();
}

function OnClicked(item) {
  if (!can_click)
    return;

  var position = item.snippet;
  if (step == -1) {
    // game has ended
    return;
  }

  if (squares[position] != "") {
    // item has already been clicked
    return;
  }

  if (state == stateMultiPlayerPlaying) {
    try {
      googleTalk.SendTalkData(friend_user_id, position);
    } catch (e) {
      utils.alert(strConnectionError);
      OnMainMenu();
    }
  }

  HandleBoxClick(position, playerX);
}

function HandleBoxClick(position, player) {
  var items = pluginHelper.content_items.toArray();
  if (squares[position] == "") {
    squares[position] = player;
    items[position].image = (player == playerX ) ? imgX : imgO;
    items[position].flags = gddContentItemFlagStatic;
    if (EvaluatePosition()) {
      if (player == playerX) {
        AddGameStatus(strYouWin);
      } else {
        AddGameStatus(strYouLose);
      }
    } else if(IsGameTied()) {
      AddGameStatus(strGameTied);
    } else {
      if (state == stateSinglePlayerPlaying) {
        // single player, so figure out next move.  sleep a bit first
        utils.setTimeout(ComputerTimeout, 200 + Math.floor(Math.random() * 300)); 
      } else if (state == stateMultiPlayerPlaying) {
        // multi player, so disable any more clicking until friend makes a move
        can_click = false;
      }
    }
  }
}

function ComputerTimeout() {
  var items = pluginHelper.content_items.toArray();
  var next_move = GetNextMove();
  if (next_move == -1) {
    AddGameStatus(strGameTied);
  } else {
    squares[next_move] = playerO;
    items[next_move].image = imgO;
    items[next_move].flags = gddContentItemFlagStatic;

    if (EvaluatePosition())
      AddGameStatus(strYouLose);
  }
}

function OnReceiveTalkData(friend, data) {
  if (data == messageStartGame) {
    if (utils.confirm(friend.name + strWantsToPlay)) {
      friend_user_id = friend.user_id;
      googleTalk.SendTalkData(friend.user_id, messageAcceptGame);
      state = stateMultiPlayerPlaying;
      AddItems();
    } else {
      googleTalk.SendTalkData(friend.user_id, messageDeclineGame);
    }
  } else if (data == messageAcceptGame) {
    // don't start a game if this user cancelled the request, but the friend said yes
    // in the mean time
    if (friend_user_id != "") {
      state = stateMultiPlayerPlaying;
      AddItems();
    }
  } else if (data == messageDeclineGame) {
    utils.alert(friend.name + strDoesntWantToPlay);
    OnMainMenu();
  } else if (data == messageCancelGame) {
    // friend cancelled game
    if (friend_user_id != "") {
      utils.alert(friend.name + strEndedGame);
      OnCancelDontNotify();
    }
  } else {
    // must be a movement
    HandleBoxClick(data, playerO);
    can_click = true;
  }
}

function OnDisplayStateChange(new_display_state) {
  if (new_display_state != gddTileDisplayStateResized)
    return;

  if (state == stateSinglePlayerPlaying || state == stateMultiPlayerPlaying) {
    ResizeBoard();
  } else if (state == stateMainMenu) {
    DrawMenu();
  }
}

// see if there is a winner
function EvaluatePosition() {
  return (
    (squares[0] != "" && squares[0] == squares[3] && squares[0] == squares[6]) ||
    (squares[0] != "" && squares[0] == squares[1] && squares[0] == squares[2]) ||
    (squares[0] != "" && squares[0] == squares[4] && squares[0] == squares[8]) ||
    (squares[1] != "" && squares[1] == squares[4] && squares[1] == squares[7]) ||
    (squares[2] != "" && squares[2] == squares[5] && squares[2] == squares[8]) ||
    (squares[2] != "" && squares[2] == squares[4] && squares[2] == squares[6]) ||
    (squares[3] != "" && squares[3] == squares[4] && squares[3] == squares[5]) ||
    (squares[6] != "" && squares[6] == squares[7] && squares[6] == squares[8]));
}

function IsGameTied() {
  if (EvaluatePosition())
    return false;
    
  for (var i = 0; i < 9; ++i) {
    if (squares[i] == "")
      return false;
  }
  
  return true;
}

function ComputeMove(player, weight, depth) {
  var cost;
  var bestcost = -2;
  var newplayer = (player == playerX) ? playerO : playerX;
  if (depth == diff)
    return 0;

  if (EvaluatePosition())
    return 1;

  for (var i = 0; i < 9; ++i) {
    if (squares[i] == "") {
      squares[i] = player;
      cost = ComputeMove(newplayer, -weight, depth + 1);
      squares[i] = "";
      if (cost > bestcost) {
        bestcost = cost;
        if (cost == 1)
          break;
      }
    }
  }
  return (bestcost == -2) ? 0 : -bestcost;
}

function GetNextMove() {
  var cost;
  var bestcost = -2;
  var bestmove = -1;

  // don't think about first move.
  if (step++ == 0)
    return (squares[4] == "") ? 4 : 0;

  for (var i = 0; i < 9; ++i) {
    if (squares[i] == "") {
      squares[i] = playerO;
      cost = ComputeMove(playerX, -1, 0);
      squares[i] = "";
      if (cost > bestcost) {
        bestmove = i;
        bestcost = cost;
        if (cost == 1)
          break;
      }
    }
  }
  return bestmove;
}
