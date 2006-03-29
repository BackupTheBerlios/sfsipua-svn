Open the solution in Visual Studio.NET and compile to create the plugin DLL. This DLL must be registered ( regasm yourplugin.dll /codebase (this will require that all the .DLLs referenced by your plugin have strong names)) to automatically add itself to the Sidebar.

If you run into any build errors mentioning that component "GoogleDesktopDisplayLib" cannot be found, you have to register the Display API type library file that would have been created in "api\samples\common". Open command prompt and run "c:\windows\system32\URTTemp\regtlib.exe api\samples\common\GoogleDesktopDisplayAPI.tlb" to register the type library. Build the solution after this.

This sample plugin will create and display content at regular intervals, showcasing the various features of the Google Desktop Display API.

The plugin uses GUIDs for various classes visible to COM. These GUIDs are marked with the text "Change this in your plugin". You have to create new GUIDs for these when you start developing a plugin based on this sample code.

It is recommended that you create an installer to distribute the plugin.