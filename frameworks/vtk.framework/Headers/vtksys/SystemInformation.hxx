/*============================================================================
  KWSys - Kitware System Library
  Copyright 2000-2009 Kitware, Inc., Insight Software Consortium

  Distributed under the OSI-approved BSD License (the "License");
  see accompanying file Copyright.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the License for more information.
============================================================================*/
#ifndef vtksys_SystemInformation_h
#define vtksys_SystemInformation_h


/* Define these macros temporarily to keep the code readable.  */
#if !defined (KWSYS_NAMESPACE) && !vtksys_NAME_IS_KWSYS
# define kwsys_stl vtksys_stl
# define kwsys_ios vtksys_ios
#endif
#include "stl/string"
#include <stddef.h> /* size_t */

namespace vtksys
{


// forward declare the implementation class
class SystemInformationImplementation;

class vtksys_EXPORT SystemInformation
{

public:
  SystemInformation ();
  ~SystemInformation ();

  const char * GetVendorString();
  const char * GetVendorID();
  kwsys_stl::string GetTypeID();
  kwsys_stl::string GetFamilyID();
  kwsys_stl::string GetModelID();
  kwsys_stl::string GetModelName();
  kwsys_stl::string GetSteppingCode();
  const char * GetExtendedProcessorName();
  const char * GetProcessorSerialNumber();
  int GetProcessorCacheSize();
  unsigned int GetLogicalProcessorsPerPhysical();
  float GetProcessorClockFrequency();
  int GetProcessorAPICID();
  int GetProcessorCacheXSize(long int);
  bool DoesCPUSupportFeature(long int);

  // returns an informative general description of the cpu
  // on this system.
  kwsys_stl::string GetCPUDescription();

  const char * GetHostname();
  kwsys_stl::string GetFullyQualifiedDomainName();

  const char * GetOSName();
  const char * GetOSRelease();
  const char * GetOSVersion();
  const char * GetOSPlatform();

  int GetOSIsWindows();
  int GetOSIsLinux();
  int GetOSIsApple();

  // returns an informative general description of the os
  // on this system.
  kwsys_stl::string GetOSDescription();

  bool Is64Bits();

  unsigned int GetNumberOfLogicalCPU(); // per physical cpu
  unsigned int GetNumberOfPhysicalCPU();

  bool DoesCPUSupportCPUID();

  // Retrieve id of the current running process
  long long GetProcessId();

  // Retrieve memory information in megabyte.
  size_t GetTotalVirtualMemory();
  size_t GetAvailableVirtualMemory();
  size_t GetTotalPhysicalMemory();
  size_t GetAvailablePhysicalMemory();

  // returns an informative general description if the ram
  // on this system
  kwsys_stl::string GetMemoryDescription();

  // Retrieve physical memory information in kib
  long long GetMemoryTotal();
  long long GetMemoryUsed();

  // enable/disable stack trace signal handler.
  static
  void SetStackTraceOnError(int enable);

  /** Run the different checks */
  void RunCPUCheck();
  void RunOSCheck();
  void RunMemoryCheck();
private:
  SystemInformationImplementation* Implementation;

};
} // namespace vtksys

/* Undefine temporary macros.  */
#if !defined (KWSYS_NAMESPACE) && !vtksys_NAME_IS_KWSYS
# undef kwsys_stl
# undef kwsys_ios
#endif

#endif
