// Copyright 2005 Google Inc. All Rights Reserved.
//
// utils.cpp : Implementation of our utility functions.
#include "stdafx.h"
#include <winioctl.h>
#include "utils.h"

// Disk performance checking.
HRESULT GetDiskActivityCounters (uint64 *reads, uint64 *writes, 
    uint64 *bytes_read, uint64 *bytes_written) {
  if (reads)
    *reads = 0;

  if (writes)
    *writes = 0;

  if (bytes_read)
    *bytes_read = 0;

  if (bytes_written)
    *bytes_written = 0;

  // for all drives
  for (int drive = 0; ; drive++) {
    struct _DISK_PERFORMANCE perf_data;
    const int max_device_len = 50;

    // check whether we can access this device
    CString device_name;
    device_name.Format (_T("\\\\.\\PhysicalDrive%d"), drive);
    HANDLE device = CreateFile(device_name, 0, 
                               FILE_SHARE_READ | FILE_SHARE_WRITE, 
                               NULL, OPEN_EXISTING, 0, NULL);

    if (device == INVALID_HANDLE_VALUE) {
      break;
    }

    // disk performance counters must be on (diskperf -y on older machines; defaults to on on newer windows)
    DWORD size = 0;
    if (DeviceIoControl(device, IOCTL_DISK_PERFORMANCE, NULL, 0, &perf_data, 
                        sizeof(_DISK_PERFORMANCE), &size, NULL)) {
      // UTIL_LOG ((LEVEL_INF6, _T("drive %d read count %u write count %u read bytes %s write bytes %s\n"),
      // drive, perf_data.ReadCount, perf_data.WriteCount,
      // String_Int64ToString (perf_data.BytesRead.QuadPart, 10), 
      //   String_Int64ToString (perf_data.BytesWritten.QuadPart, 10)));
      if (reads)
        *reads += perf_data.ReadCount; 

      if (writes)
        *writes += perf_data.WriteCount;

      if (bytes_read)
        *bytes_read += perf_data.BytesRead.QuadPart;

      if (bytes_written)
        *bytes_written += perf_data.BytesWritten.QuadPart; 
    } else {
      DWORD err = ::GetLastError();      
      ATLVERIFY(CloseHandle (device));
      return HRESULT_FROM_WIN32(err);
    }

    ATLVERIFY(CloseHandle (device));
  }

  return S_OK;
}

// Implementation of CpuMonitor
CpuMonitor::CpuMonitor() : get_sys_time_func_(NULL), fallback_func_(NULL) {
  // The GetSystemTimes function is a documented function which is available
  // from WinXP SP1 onwards.  It is the preferred function to fetch the
  // CPU information we need.  On earlier systems, we fall back to NtQuerySystemInformation,
  // which is less preferred because it is liable to change in future versions
  // of Windows.
  HMODULE kernel32dll = ::GetModuleHandle(L"kernel32.dll");  // is always loaded
  ATLASSERT(kernel32dll);
  get_sys_time_func_ = reinterpret_cast<GetSystemTimesFunction>(::GetProcAddress(kernel32dll, NOTRANSL("GetSystemTimes")));

  if (!get_sys_time_func_) {
    ntdll_ = ::GetModuleHandle(NOTRANSL(L"ntdll.dll"));
    ATLASSERT(ntdll_);
    if (ntdll_) {
      fallback_func_ = reinterpret_cast<NtQuerySystemInformationFunction>(::GetProcAddress(ntdll_,
        NOTRANSL("NtQuerySystemInformation")));
      ATLASSERT(fallback_func_);
    }
  }

  last_kernel_.QuadPart = 0;
  last_user_.QuadPart = 0;
  last_idle_.QuadPart = 0;

  SYSTEM_INFO system_info = { 0 };
  ::GetSystemInfo(&system_info);
  num_processors_ = system_info.dwNumberOfProcessors;
  processor_info_ = new SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION[num_processors_];

  // Call this to initialize last_total_
  GetLoad();
}

CpuMonitor::~CpuMonitor() {  
  if (processor_info_) {
    delete [] processor_info_;
  }
}

int CpuMonitor::GetLoad() {
  LARGE_INTEGER current_idle, current_user, current_kernel;
  current_idle.QuadPart = 0;
  current_user.QuadPart = 0;
  current_kernel.QuadPart = 0;

  if (get_sys_time_func_) {
    // We're on WinXP SP1 or newer so we can use GetSystemTimes.  It returns
    // the aggregate time for all processors.
    get_sys_time_func_(reinterpret_cast<FILETIME*>(&current_idle),
          reinterpret_cast<FILETIME*>(&current_kernel),
          reinterpret_cast<FILETIME*>(&current_user));
  } else if (fallback_func_) {
    ULONG returned_length = 0;
    fallback_func_(SystemProcessorPerformanceInformation,
      reinterpret_cast<void*>(processor_info_),
      num_processors_ * sizeof(SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION),
      &returned_length);
    ATLASSERT(returned_length == num_processors_ * sizeof(SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION));

    for (int ix = 0; ix < num_processors_; ix++) {
      current_idle.QuadPart += processor_info_[ix].IdleTime.QuadPart;
      current_user.QuadPart += processor_info_[ix].UserTime.QuadPart;
      current_kernel.QuadPart += processor_info_[ix].KernelTime.QuadPart;
      
      ATLASSERT(current_idle.QuadPart > 0);
      ATLASSERT(current_user.QuadPart > 0);
      ATLASSERT(current_kernel.QuadPart > 0);
    }
  }

  LARGE_INTEGER idle_elapsed, user_elapsed, kernel_elapsed;
  idle_elapsed.QuadPart = current_idle.QuadPart - last_idle_.QuadPart;
  user_elapsed.QuadPart = current_user.QuadPart - last_user_.QuadPart;
  kernel_elapsed.QuadPart = current_kernel.QuadPart - last_kernel_.QuadPart;

  last_idle_ = current_idle;
  last_user_ = current_user;
  last_kernel_ = current_kernel;

  // The load should be derived using this:
  //   (kernel + user - idle) / (kernel + user)
  // Becuase idle is just another process and its time included in kernel + user.
  int ret = 0;
  LARGE_INTEGER system_time;
  system_time.QuadPart = user_elapsed.QuadPart + kernel_elapsed.QuadPart;
  if (system_time.QuadPart) {
    ret = static_cast<int>(10000 * 
            (system_time.QuadPart - idle_elapsed.QuadPart) / 
            system_time.QuadPart);
  }

  return ret;
}
