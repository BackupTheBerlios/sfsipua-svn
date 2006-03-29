#pragma once

/**
* Unregisters this application from the Google Desktop event framework.
* @note Must have been successfully registered before.
*/
HRESULT UnregisterFromGDEventFramework();

/**
* Registers this application with the Google Desktop event framework.
*/
HRESULT RegisterWithGDEventFramework();

HRESULT EnsureRegistered(long* cookie);
