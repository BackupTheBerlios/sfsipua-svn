========================================================================
    Google Desktop Sidebar API : Sample Project Overview
========================================================================

This project implements a very simple plugin for the Google Desktop Sidebar.
Use this as a template for your own plugins.

Google Desktop Sidebar plugins are ActiveX controls that implement the
Sidebar Plugin interface. They show property pages using ISpecifyPropertyPages/
IPropertyPage interfaces and serialize their properties using IPersistStream/
IPersistStreamInit interfaces.

This sample makes use of a COM object exposed by the Sidebar called the 
PluginHelper which implements all the necessary interfaces for a standard
ActiveX control. Your plugins can aggregate this object and use it's methods
to get the standard look and feel provided by the Sidebar.

Getting started:
=================

1. Run guidgen.exe and generate 4 different GUIDs. You can get guidgen.exe
   from the Platform SDK or from Microsoft's website.
2. Open the files Plugin.rgs, PropertyPage.rgs and GoogleDesktopSidebarSample1.idl 
   in a text editor. Select the 4 GUIDs used in these files and replace them
   with the ones that you have generated. 

   DO NOT SKIP THE ABOVE 2 STEPS - THEY ARE REQUIRED TO CREATE A UNIQUE
   ID FOR YOUR PLUGIN AND FOR IT TO WORK PROPERLY.

3. Open the sample project file in Visual studio, open the resources, goto the string
   table and change the "Sample plugin" portion of all the strings to your 
   plugin's name
4. Compile the project and after successfully building it will automatically
   register the plugin using regsvr32.
5. Choose "Add new plugin" from the sidebar menu and your plugin should be shown in
   the list. Select the plugin and press OK to add it to the sidebar.
6. The above 2 steps are required only the first time. Make changes to the files of 
   the project, exit the sidebar (GDS), recompile the project and run the sidebar (GDS)
   again to view your changes.
