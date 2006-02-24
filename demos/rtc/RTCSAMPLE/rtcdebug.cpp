// rtcdebug.h
//

#include "stdafx.h"

#if defined(_DEBUG) || defined(DEBUG) || defined(DBG)

/////////////////////////////////////////////
//
// DebugPrint
// 

void DebugPrint(const char * szFormat, ...)
{
    int cch;
    char szBuf[MAX_DEBUG_STRING+2];
    va_list arglist;

    va_start(arglist, szFormat);
    cch = _vsnprintf(szBuf, MAX_DEBUG_STRING, szFormat, arglist);
    va_end(arglist);

    if ((cch == -1) || (cch == MAX_DEBUG_STRING))
    {
        // overflow
        szBuf[MAX_DEBUG_STRING] = '\0';
        cch = MAX_DEBUG_STRING;
    }

    if (cch > 0)
    {
        // add an end of line
        strcat(szBuf, "\n");

        // send to debugger
        OutputDebugStringA("RTCSAMPLE: ");
        OutputDebugStringA(szBuf);
    }
}

#endif
