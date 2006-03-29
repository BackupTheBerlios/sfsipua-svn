// Copyright 2004 Google Inc
// All rights reserved
// 
#ifndef __GOOGLE_DESKTOP_COMPONENT_REGISTRATION_H__
#define __GOOGLE_DESKTOP_COMPONENT_REGISTRATION_H__

// Attempts to register the provided CLSID with GDS
// if num_suffixes is zero does not attempt to register for crawl 
// events
// @param clsid class id of this component, must be unique to this component
// @param title name for the component, displayed to the user, cannot be NULL
// @param description info about the component, displayed to the user, cannot be NULL
// @param iocn full path to an icon for this component, cannot be NULL
// @param num_suffixes number of pointers in the suffixes array
// @param suffixes file extensions with which this plugin should be registered
HRESULT RegisterIndexingComponentHelper(REFCLSID clsid,
                                        const wchar_t *title, 
                                        const wchar_t *description,
                                        const wchar_t *icon,
                                        int num_suffixes,
                                        const wchar_t *suffixes[]);


// Attempts to register the provided CLSID with GDS as a display component (eg. a
// sidebar/notification plugin)
// @param clsid class id of this component, must be unique to this component
// @param title name for the component, displayed to the user, cannot be NULL
// @param description info about the component, displayed to the user, cannot be NULL
// @param iocn full path to an icon for this component, cannot be NULL
// @param shows_notifications flag set to true if this plugin displays
//    notifications. This will list the plugin in the options dialog and
//    allow the user to enable/disable notifications for this plugin
HRESULT RegisterDisplayComponentHelper(REFCLSID clsid,
                                       const wchar_t *title, 
                                       const wchar_t *description,
                                       const wchar_t *icon,
                                       bool shows_notifications);

HRESULT UnregisterComponentHelper(REFCLSID clsid);


#endif  // __GOOGLE_DESKTOP_COMPONENT_REGISTRATION_H__
