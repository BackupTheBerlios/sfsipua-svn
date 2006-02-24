// rtcdebug.h
//

#ifndef _RTCDEBUG_H_
#define _RTCDEBUG_H_

#if defined(_DEBUG) || defined(DEBUG) || defined(DBG)

#define DEBUG_PRINT(arg) DebugPrint arg
#define MAX_DEBUG_STRING 1024
void DebugPrint(const char * szFormat, ...);

#else

#define DEBUG_PRINT(arg)

#endif

#endif //_RTCDEBUG_H_
