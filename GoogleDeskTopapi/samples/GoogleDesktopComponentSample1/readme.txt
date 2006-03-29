To compile the sample dll, use visual studio with the project file (you may want
to adjust the post-build step to not register the dll). It will also ask you
to save a solution.

To register the DLL, run "regsvr32.exe GoogleDesktopComponentSample1.dll" from a command line.
Note that registration will fail if the DLL is already registered with Google Desktop Search. 
In that case you need to unregister the DLL before registering it again.
To unregister, run "regsvr32.exe /u GoogleDesktopComponentSample1.dll" from a command line.
