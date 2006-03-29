// Copyright 2005 Google Inc. All Rights Reserved.
//
// utils.h : Declaration of all our utility functions.
#ifndef UTILS_H__
#define UTILS_H__

#include <winternl.h>

// Get disk performance data.
HRESULT GetDiskActivityCounters (uint64 *reads, uint64 *writes, 
    uint64 *bytes_read, uint64 *bytes_written);

/// A class that allows you to fetch the "load" on the CPU since the
/// load was last fetched (or since the object was constructed).
///
/// Requires Windows 2000 or later.
class CpuMonitor {
public:
  CpuMonitor();
  ~CpuMonitor();

  /// Returns the average load on the processor (combined
  /// kernel and user load) since this method was last called on this
  /// object (or since the object was constructed, if this method has never
  /// been called on this object) as a number from 0 to 10000.  Divide
  /// by 100 to get percentage.
  int GetLoad();

private:
  /// CPU idle cycles, time in kernel space, time in user space,
  //  (in terms of time spent in each mode, in 100ns increments)
  /// when we last measured.
  LARGE_INTEGER last_idle_, last_kernel_, last_user_;

  /// Array for CPU performance information.  Length is num_processors_
  SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION * processor_info_;

  /// Number of processors on this system.
  int num_processors_;

  /// Type of the GetSystemTimes function.
  typedef BOOL (WINAPI * GetSystemTimesFunction)(LPFILETIME idle, LPFILETIME kernel, LPFILETIME user);

  /// Type of the NtQuerySystemInformation function.
  typedef NTSTATUS (WINAPI * NtQuerySystemInformationFunction)(SYSTEM_INFORMATION_CLASS cls, PVOID info,
                                                               ULONG len, PULONG return_len);

  /// The preferred function to get CPU information.
  GetSystemTimesFunction get_sys_time_func_;

  /// Function we use to get CPU information if the GetSystemTimes function is not
  /// available.
  NtQuerySystemInformationFunction fallback_func_;

  /// Module handles of the library providing the fallback function we use.
  HMODULE ntdll_;
};


#endif  // UTILS_H__
