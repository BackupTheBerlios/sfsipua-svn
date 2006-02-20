; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
ClassCount=3
ResourceCount=0
NewFileInclude1=#include "stdafx.h"
Class1=CListenSocket
LastClass=CSendClient
LastTemplate=CSocket
Class2=CClientSocket
Class3=CSendClient

[CLS:CListenSocket]
Type=0
HeaderFile=ListenSocket.h
ImplementationFile=ListenSocket.cpp
BaseClass=CSocket
Filter=N
LastObject=CListenSocket
VirtualFilter=uq

[CLS:CClientSocket]
Type=0
HeaderFile=ClientSocket.h
ImplementationFile=ClientSocket.cpp
BaseClass=CSocket
Filter=N
VirtualFilter=uq
LastObject=CClientSocket

[CLS:CSendClient]
Type=0
HeaderFile=SendClient.h
ImplementationFile=SendClient.cpp
BaseClass=CAsyncSocket
Filter=N
VirtualFilter=uq
LastObject=CSendClient

