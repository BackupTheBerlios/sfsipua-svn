To enable indexing of MSN chats you will need to enable the MSN Messenger 'Message History' checkbox under Tools->Options->Messages.

To compile the MSN Messenger component sample, use visual studio with the solution file.

The build wiill create an executable MSNMessengerComponent.exe and a dll Interop.GoogleDesktopSearchAPILib.dll.
Copy the executable and the dll to a directory and register the component with GDS.

To register run:
MSNMessengerComponent.exe -register

After registration the component will be started automatically on reboot.

To unregister run:
MSNMessengerComponent.exe -unregister



