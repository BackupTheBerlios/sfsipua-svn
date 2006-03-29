To compile the sample EXE, use visual studio with the solution file.

The build creates the sample EXE and a ShellHook.dll, both part of 
the sample. The hook DLL is registered with windows to get all 
window create/destroy events, and these events are sent to Google 
Desktop Search for indexing.

The first time you run the sample, choose "File > Register Component
with GDS" menu option. This registers the plugin with GDS and may prompt
a confirmation dialog box from GDS. Click OK and registration is done.
After this all window open/close events generate events that go into
the GDS history as indexable/searchable events.
