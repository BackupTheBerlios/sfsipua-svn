/*
 * file : export.h
 * 
 * this file is used when building the oRTP stack as a dynamic loadable library
 * on win32 OS. Indeed, structures cannot been exported 'as is' using the .def
 * file. Since we want to use the av_profile and telephone_event instances as defined
 * in the original source code, We have to implement those 2 functions to retrieve
 * pointers on them.
 *
 */



#ifndef EXPORT_H
#define EXPORT_H


#if defined __cplusplus
extern "C"
{
#endif


#include "payloadtype.h"
#include "telephonyevents.h"


        RtpProfile * get_av_profile( void );
        PayloadType * get_telephone_event( void );



#if defined __cplusplus
}
#endif


#endif
