/*
 * file : export.c
 * 
 * this file is used when building the oRTP stack as a dynamic loadable library
 * on win32 OS. Indeed, structures cannot been exported 'as is' using the .def
 * file. Since we want to use the av_profile and telephone_event instances as defined
 * in the original source code, We have to implement those 2 functions to retrieve
 * pointers on them.
 *
 */


#include "export.h"


RtpProfile * get_av_profile( void )
{
        return &av_profile;
}

PayloadType * get_telephone_event( void )
{
        return &telephone_event;
}

