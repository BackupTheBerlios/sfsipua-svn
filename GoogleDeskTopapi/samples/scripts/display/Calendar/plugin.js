var maxDaysInWeek = 7;
var maxDaysInMonth = 31;
var curMonth = new Date().getMonth();
var curYear = new Date().getYear();
var curDate = new Date().getDate();
var itemHeight = 17;

pluginHelper.SetFlags(gddPluginFlagToolbarBack + gddPluginFlagToolbarForward,
  gddContentFlagManualLayout + gddContentFlagHaveDetails);
  
pluginHelper.SetIcons(utils.loadImage("plugin_small.gif"), utils.loadImage("plugin_large.gif"));
pluginHelper.about_text = strAboutText;
pluginHelper.max_content_items = 100;   // since we have more items than default
pluginHelper.onCommand = OnCommand;
pluginHelper.onDisplayStateChange = OnDisplayStateChange;
utils.setInterval(OnTimer, 1000);     // timer every second
RefreshCalendar();    // initial UI update

// Timer function which gets called each second.
var prevDate;
function OnTimer() {
  var cal = new Date();
  UpdateTimeMonthYear();
  if (prevDate != cal.getDate()) {  // date changed?
    prevDate = cal.getDate();
    curDate = prevDate;
    curMonth = cal.getMonth();
    curYear = cal.getYear();
    RefreshCalendar();
  }
}

function HaveNotesForDate(year, month, date) {
  var key = "note" + year + month + date;
  var value = options.GetValue(key);
  return (value.length > 0) ? true : false;
}

function GetNotesForDate(year, month, date) {
  var key = "note" + year + month + date;
  var value = options.GetValue(key);
  return (value.length > 0) ? value.split("\n") : new Array();
}

function PutNotesForDate(year, month, date, notes) {
  var key = "note" + year + month + date;
  options.PutValue(key, notes.join('\n'));
}

var monthYearItem;
function UpdateTimeMonthYear() {
  var cal = new Date();
  var hour = cal.getHours() % 12;
  var min = cal.getMinutes();
  // The ':' and ' ' below is to make the ':' character blink in the displayed time
  pluginHelper.title = ((hour == 0) ? 12 : hour) + 
    ((cal.getSeconds() % 2) ? ":" : " ") + ((min < 10) ? "0" : "") + min +
    ((cal.getHours() >= 12) ? " pm" : " am");
  var monthYear = monthName[curMonth] + " " + curYear;
  if (monthYearItem.heading != monthYear)   // optimize redraws
    monthYearItem.heading = monthYear;
}

function OnCommand(cmd) {
  if (cmd == gddCmdToolbarBack || cmd == gddCmdToolbarForward) {
    curMonth += (cmd == gddCmdToolbarForward) ? 1 : -1;
    curYear += (curMonth < 0) ? -1 : (curMonth >= 12 ? 1 : 0);
    curMonth = (curMonth < 0) ? 11 : (curMonth % 12);
    RefreshCalendar();
  }
}

function OnDisplayStateChange(state) {
  RefreshCalendar();  // redraw ourselves during each state change
}

function RefreshCalendar() {
  pluginHelper.RemoveAllContentItems();   // clear current UI elements

  var fullWidth = pluginHelper.window_width;
  var itemWidth = fullWidth / maxDaysInWeek;
  var x = 0, y = 0;

  monthYearItem = AddStaticItem("", x, y, maxDaysInWeek * itemWidth, itemHeight, DrawItem);
  y += itemHeight;

  for (var i = 0; i < maxDaysInWeek; ++i)     // add the weekday header items
    AddStaticItem(dayName[i], x + itemWidth * i, y, itemWidth, itemHeight, DrawItem);
  AddStaticItem("", x, y, maxDaysInWeek * itemWidth, itemHeight, DrawHeaderBkgnd);
  y += itemHeight;

  var cal = new Date();
  var actualDate = cal.getDate();
  var actualMonth = cal.getMonth();
  cal.setDate(1);
  cal.setMonth(curMonth);
  cal.setYear(curYear);
  x += cal.getDay() * itemWidth;

  for (var i = 0; i < maxDaysInMonth; ++i) {  // add each day of the month
    var drawDate = cal.getDate();
    if (drawDate > i) {
      if (i > 0 && cal.getDay() == 0) {
        x = 0;
        y += itemHeight;
      }
      var item = AddItem(drawDate, x, y, itemWidth, itemHeight, DrawItem, SelectDate);
      // show a border around selected date
      if (curDate == drawDate)
        AddStaticItem("", x - 2, y - 2, itemWidth + 5, itemHeight + 5, DrawSelectedDayBkgnd);
      // show a highlight item behind today
      if (actualDate == drawDate && curMonth == actualMonth)
        AddStaticItem("", x - 2, y - 2, itemWidth + 5, itemHeight + 5, DrawTodayBkgnd);
      else if (HaveNotesForDate(curYear, curMonth, drawDate))
        AddStaticItem("", x - 2, y - 2, itemWidth + 5, itemHeight + 5, DrawHeaderBkgnd);
      x += itemWidth;
    }
    cal.setDate(drawDate + 1);
  }
  y += itemHeight + 4;
  x = 0;
  
  AddStaticItem(strNotesForTheDay, x, y + 2, fullWidth / 3 * 2, itemHeight, null);
  AddItem(strAddButtonText, x + fullWidth / 3 * 2, y + 2, fullWidth / 3, itemHeight, null, AddNote);
  y += itemHeight + 4;
  AddStaticItem("", x, y, fullWidth, 1, DrawLineItem);
  y += 4;
  
  var notes = GetNotesForDate(curYear, curMonth, curDate);
  if (notes.length == 0) {
    // since we have no notes to show, add an empty item which is not clickable. This
    // allows us to occupy some empty space at the bottom when we load up initially
    // and if the user adds a note it will be visible immediately.
    AddStaticItem("", x, y, fullWidth, itemHeight * 2, null, null);
  } else {
    for (var i = 0; i < notes.length; ++i) {
      var noteItem = AddItem(notes[i], x, y, fullWidth, itemHeight, null, null);
      noteItem.flags = gddContentItemFlagNone;
      noteItem.onOpenItem = EditNote;
      noteItem.onRemoveItem = DeleteNote; // called when user right clicks and selects 'remove'
      y += itemHeight;
    }
  }
  
  UpdateTimeMonthYear();
}

function SelectDate(item) {
  curDate = item.heading;
  RefreshCalendar();
}

function DeleteNote(item) {
  var notes = GetNotesForDate(curYear, curMonth, curDate);
  for (var i = 0; i < notes.length; ++i) {
    if (notes[i] == item.heading) {
      notes.splice(i, 1);
      break;
    }
  }
  PutNotesForDate(curYear, curMonth, curDate, notes);
  RefreshCalendar();
  // return true to cancel default processing since we removed the item in the UI 
  // also ourselves (by recreating all items above)
  return true;  
}

function AddNote(item) {
  var note = utils.prompt(strAddNotePromptText, "");
  if (note != null && note != "") {
    var notes = GetNotesForDate(curYear, curMonth, curDate);
    notes.splice(notes.length, 0, note);
    PutNotesForDate(curYear, curMonth, curDate, notes);
    RefreshCalendar();
  }
}

function EditNote(item) {
  var note = utils.prompt(strEditNotePromptText, item.heading);
  if (note != null && note != "") {
    var notes = GetNotesForDate(curYear, curMonth, curDate);
    for (var i = 0; i < notes.length; ++i)
      if (notes[i] == item.heading)
        notes[i] = note;
    PutNotesForDate(curYear, curMonth, curDate, notes);
    RefreshCalendar();
  }
}

function AddStaticItem(str, x, y, width, height, drawHandler) {
  var item = new ContentItem();
  item.heading = str;
  item.flags = gddContentItemFlagStatic;  // dont take input
  item.SetRect(x, y, width, height);
  if (drawHandler)
    item.onDrawItem = drawHandler;
  pluginHelper.AddContentItem(item, gddItemDisplayInSidebar);
  return item;
}

function AddItem(str, x, y, width, height, drawHandler, detailsHandler) {
  var item = new ContentItem();
  item.heading = str;
  item.snippet = str;
  item.tooltip = str;
  item.flags = gddContentItemFlagNoRemove;
  item.SetRect(x, y, width, height);
  if (drawHandler)
    item.onDrawItem = drawHandler;
  if (detailsHandler)
    item.onDetailsView = detailsHandler;
  pluginHelper.AddContentItem(item, gddItemDisplayInSidebar);
  return item;
}

function DrawHeaderBkgnd(item, target, graphics, x, y, width, height) {
  var curItemHeight = graphics.GetTextHeight("Z", 1000, 0, gddFontNormal) + 5;
  if (curItemHeight != itemHeight) {
    itemHeight = curItemHeight;
    RefreshCalendar();
  } else {
    graphics.DrawRect(x, y, width, height, "#E0E0E0", "#E0E0E0");
    graphics.DrawText(x, y, width, height, item.heading, gddColorNormalText, 
      gddTextFlagSingleLine + gddTextFlagVCenter, gddFontNormal);
  }
}

function DrawLineItem(item, target, graphics, x, y, width, height) {
  graphics.DrawRect(x, y + height / 2, width, 1, "#808080", "#808080");
}

function DrawTodayBkgnd(item, target, graphics, x, y, width, height) {
  graphics.DrawRect(x, y, width, height, "#C0C0FF", "#C0C0FF");
}

function DrawSelectedDayBkgnd(item, target, graphics, x, y, width, height) {
  var fillcolor;  // not initialized to pass an empty value to the function
  graphics.DrawRect(x, y, width, height, "#808080", fillcolor);
}

function DrawItem(item, target, graphics, x, y, width, height) {
  graphics.DrawText(x, y, width, height, item.heading, gddColorNormalText, 
    gddTextFlagCenter + gddTextFlagSingleLine + gddTextFlagVCenter, gddFontNormal);
}
