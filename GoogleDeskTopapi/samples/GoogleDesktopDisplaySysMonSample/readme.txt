========================================================================
    Google Desktop Sidebar API : Sample Project Overview
======================================================================== 

This project implements system monitor plugin for Google Desktop Sidebar.
Use this as a template for your own plugins.

Google Desktop Sidebar plugins are ActiveX controls that implement the
Sidebar Plugin interface. They show property pages using ISpecifyPropertyPages/
IPropertyPage interfaces and serialize their properties using IPersistStream/
IPersistStreamInit interfaces.

This sample demonstrates how to create a plugin based on Sidebar's helper model. 
The Sidebar's helper model is composed of PluginHelper object and ContentItemHelper
object. These two objects exposed by Sidebar are intended to make the plugin 
development easier. Using these two objects are recommended and in the future,
when Sidebar upgrades, your plugin will have the new features with minimal or
no code change.

sysmon.cpp contains the implementation of the system monitor plugin. The plugin
  hosts a set of SysMonContentItem. SysMonContentItem is defined in
  sysmon_content_item.h.
  
sysmon_content_item.cpp implements SysMonContentItem hosted by plugin. In
  this sample, the content item serves as a bridge between the MonitorItem and
  the plugin. MonitorItem is defined in sysmon_monitor_item.h. The derivatives 
  of MonitorItem represent the performance counters. They are responsible for
  data collecting and drawing itself out.
  
sysmon_monitor_item.cpp implements MonitorItem and its derivatives.

Basically, the plugin hosts a timer and triggers data collection at given
refresh_interval. When time is due, each SysMonContentItem hosted will be 
notified. They will in chain call their corresponding MonitorItem to collect
the data and re-paint the space SysMonContentItem occupies.

The one thing needs to note that this sample uses the customized pop-out 
drawing instead of using the details view.  However, when each item of your 
plugin has more details view, it is recommended that you take advantage 
details view. 
 

