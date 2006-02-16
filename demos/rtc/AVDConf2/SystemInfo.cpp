// ------------------------------------------------------------------------------------
// Copyright ©2002 Intel Corporation
// All Rights Reserved
// 
// Permission is granted to use, copy, distribute and prepare derivative works of this 
// software for any purpose and without fee, provided, that the above copyright notice
// and this statement appear in all copies.  Intel makes no representations about the
// suitability of this software for any purpose.  This software is provided "AS IS." 
//
// Intel specifically disclaims all warranties, express or implied, and all liability,
// including consequential and other indirect damages, for the use of this software, 
// including liability for infringement of any proprietary rights, and including the 
// warranties of merchantability and fitness for a particular purpose.  Intel does not
// assume any responsibility for any errors which may appear in this software nor any
// responsibility to update it.
// ------------------------------------------------------------------------------------
//
// SystemInfo.cpp : implementation file
//
// Purpose: This class contains all the methods to get the system information
//

#include "stdafx.h"
#include "iphlpapi.h"
#include "pdh.h"
#include "SystemInfo.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSystemInfo::CSystemInfo()
{

}

CSystemInfo::~CSystemInfo()
{

}

//////////////////////////////////////////////////////////////////////////////
// Method: GetCPUInfo()
// Parameter: None
// Return Value: CPU Information
//				 xxxx xxxx xxxx xxxx xxxx xxxx xxxx xxxx
//				 |HT Status         |Log CPU  |Phy CPU  |
// Purpose: Gets the number of logical and phyical CPU and state of HT
//////////////////////////////////////////////////////////////////////////////
DWORD CSystemInfo::GetCPUInfo()
{
   unsigned char LogicalNum   = 0,  // Number of logical CPU per ONE PHYSICAL CPU
        PhysicalNum  = 0,  // Total number of physical processor
		HTStatusFlag = 0;  
   DWORD	lCPUInfo = 0;

   HTStatusFlag = CPUCount(&LogicalNum, &PhysicalNum);

   lCPUInfo |= ((HTStatusFlag << 16) | (LogicalNum << 8) | (PhysicalNum));

   return lCPUInfo;
}

//////////////////////////////////////////////////////////////////////////////
// Method: HTSupported()
// Parameter: None
// Return Value: HT Status
// Purpose: Returns Hyper-Thread support in the system.
// Note: The following Code can be found at http://www.intel.com/ids in the
//		 C++ code central location.
//////////////////////////////////////////////////////////////////////////////
DWORD CSystemInfo::HTSupported()
{
	unsigned int Regedx      = 0,
		         Regeax      = 0,
		         VendorId[3] = {0, 0, 0};

	__try    // Verify cpuid instruction is supported
	{
		__asm
		{
			xor eax, eax          // call cpuid with eax = 0
        	cpuid                 // Get vendor id string
			mov VendorId, ebx
			mov VendorId + 4, edx
			mov VendorId + 8, ecx
			
			mov eax, 1            // call cpuid with eax = 1
			cpuid
			mov Regeax, eax      // eax contains family processor type
			mov Regedx, edx      // edx has info about the availability of hyper-Threading
 
		}
	}

	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		return(0);                   // cpuid is unavailable
	}

    if (((Regeax & FAMILY_ID) ==  PENTIUM4_ID) || 
		(Regeax & EXT_FAMILY_ID))
	  if (VendorId[0] == 'uneG')
		if (VendorId[1] == 'Ieni')
			if (VendorId[2] == 'letn')
				return(Regedx & HT_BIT);    // Genuine Intel with hyper-Threading technology

	return 0;    // Not genuine Intel processor
}

//////////////////////////////////////////////////////////////////////////////
// Method: LogicalProcPerPhysicalProc()
// Parameter: None
// Return Value: Number of logical CPU (typical 1, HT returns 2/CPU)
// Purpose: Returns the number of logical CPU in the system.
//////////////////////////////////////////////////////////////////////////////
unsigned char CSystemInfo::LogicalProcPerPhysicalProc()
{
	unsigned int Regebx = 0;
	if (!HTSupported()) return (unsigned char) 1;  // HT not supported
	                                               // Logical processor = 1
	__asm
	{
		mov eax, 1
		cpuid
		mov Regebx, ebx
	}

	return (unsigned char) ((Regebx & NUM_LOGICAL_BITS) >> 16);
}

unsigned char CSystemInfo::GetAPIC_ID()
{
	unsigned int Regebx = 0;
	if (!HTSupported()) return (unsigned char) -1;  // HT not supported
	                                                // Logical processor = 1
	__asm
	{
		mov eax, 1
		cpuid
		mov Regebx, ebx
	}

	return (unsigned char) ((Regebx & INITIAL_APIC_ID_BITS) >> 24);
}

unsigned char CSystemInfo::CPUCount(unsigned char *LogicalNum, unsigned char *PhysicalNum)
{
	unsigned char StatusFlag  = 0;
    SYSTEM_INFO info;


    *PhysicalNum = 0;
	*LogicalNum  = 0;
    info.dwNumberOfProcessors = 0;
    GetSystemInfo (&info);

	// Number of physical processors in a non-Intel system
	// or in a 32-bit Intel system with Hyper-Threading technology disabled
    *PhysicalNum = (unsigned char) info.dwNumberOfProcessors;  

    if (HTSupported())
	{
		unsigned char HT_Enabled = 0;

        *LogicalNum= LogicalProcPerPhysicalProc();

		if (*LogicalNum >= 1)    // >1 Doesn't mean HT is enabled in the BIOS
			                     // 
		{
            HANDLE hCurrentProcessHandle;
			DWORD  dwProcessAffinity;
			DWORD  dwSystemAffinity;
			DWORD  dwAffinityMask;

			// Calculate the appropriate  shifts and mask based on the 
			// number of logical processors.

			unsigned char i = 1,
				          PHY_ID_MASK  = 0xFF,
			              PHY_ID_SHIFT = 0;

			while (i < *LogicalNum)
			{
				i *= 2;
 	            PHY_ID_MASK  <<= 1;
	            PHY_ID_SHIFT++;

			}
			
			hCurrentProcessHandle = GetCurrentProcess();
			GetProcessAffinityMask(hCurrentProcessHandle, &dwProcessAffinity,
				                                          &dwSystemAffinity);

			// Check if available process affinity mask is equal to the
			// available system affinity mask
            if (dwProcessAffinity != dwSystemAffinity)
			{
                StatusFlag = HT_CANNOT_DETECT;
				*PhysicalNum = (unsigned char)-1;
				return StatusFlag;
			}
			   dwAffinityMask = 1;
			   while (dwAffinityMask != 0 && dwAffinityMask <= dwProcessAffinity)
			   {
			  	  // Check if this CPU is available
				  if (dwAffinityMask & dwProcessAffinity)
				  {
                     if (SetProcessAffinityMask(hCurrentProcessHandle,
						                        dwAffinityMask))
					 {
						 unsigned char APIC_ID,
							           LOG_ID,
									   PHY_ID;

						 Sleep(0); // Give OS time to switch CPU

                         APIC_ID = GetAPIC_ID();
						 LOG_ID  = APIC_ID & ~PHY_ID_MASK;
						 PHY_ID  = APIC_ID >> PHY_ID_SHIFT;
 
     					 if (LOG_ID != 0)  HT_Enabled = 1;

					 }

				  }

				  dwAffinityMask = dwAffinityMask << 1;

			   }
             
			// Reset the processor affinity
			 SetProcessAffinityMask(hCurrentProcessHandle, dwProcessAffinity);

            
			if (*LogicalNum == 1)  // Normal P4 : HT is disabled in hardware
			   	StatusFlag = HT_DISABLED;

			else
				if (HT_Enabled)
				{
                     // Total physical processors in a Hyper-Threading enabled system.
		             *PhysicalNum /= (*LogicalNum);
			   	     StatusFlag = HT_ENABLED;
				}
				else StatusFlag = HT_SUPPORTED_NOT_ENABLED;

		}

	}
	else
	{
		// Processors do not have Hyper-Threading technology
		StatusFlag = HT_NOT_CAPABLE;
        *LogicalNum = 1;
        
	}
	return StatusFlag;
}

//////////////////////////////////////////////////////////////////////////////
// Method: InitPerfCounter()
// Parameter: dwCPUCount		Number of CPU to monitor
// Return Value: S_OK if CPU counter successfully initialized.
// Purpose: Initialize CPU counters for the system
// Note: The counter will only look at the first 2 CPU.  All Intel Pentium 4
//		 Processor with Hyper-Thread Technology based system will only have
//		 2 CPU active.  Intel Xeon Processor with Hyper-Thread Technology can show
//		 2 or more CPU, but only the first 2 CPU will be monitored.
//////////////////////////////////////////////////////////////////////////////
HRESULT CSystemInfo::InitPerfCounter(DWORD dwCPUCount)
{
	m_dwCPUCount = dwCPUCount;
	
	// Creates and initializes a unique query structure that is used 
	// to manage the collection of performance data
	if (PdhOpenQuery ( NULL, 1, &m_hQuery ) != ERROR_SUCCESS)
	{
		// an error occurred.
		return S_FALSE;
	}

	// Add the CPU Utilization counter
	// For this example, we are going to hard code the string to get the average of all
	// processors.  You can get this string from running Perfmon.exe
	if (PdhAddCounter ( m_hQuery, "\\Processor(0)\\% Processor Time", 
		NULL, &m_hCounter1) != ERROR_SUCCESS)
		return S_FALSE;

	if (m_dwCPUCount > 1)
	{
		if (PdhAddCounter ( m_hQuery, "\\Processor(1)\\% Processor Time", 
			NULL, &m_hCounter2) != ERROR_SUCCESS)
			return S_FALSE;
	}

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
// Method: UnInitPerfCtr()
// Parameter: None
// Return Value: S_OK if CPU counter successfully uninitialized.
// Purpose: UnInitialize CPU counters for the system
//////////////////////////////////////////////////////////////////////////////
void CSystemInfo::UnInitPerfCtr()
{
	// Remove any counters.  This is not required.
	PdhRemoveCounter ( m_hCounter1 );
	if (m_dwCPUCount == 2)
		PdhRemoveCounter ( m_hCounter2 );
	
	// close the performance data collector.
	PdhCloseQuery ( m_hQuery );
}

//////////////////////////////////////////////////////////////////////////////
// Method: GetCPUCycle()
// Parameter: nCPU		CPU ID
// Return Value: current CPU utilization (0 - 100)
// Purpose: Gets the CPU Utilization value from NT Perfmon
//////////////////////////////////////////////////////////////////////////////
DWORD CSystemInfo::GetCPUCycle(int nCPU)
{
	PDH_RAW_COUNTER	ppdhRawCounter;
	PDH_FMT_COUNTERVALUE pdhFormattedValue;
	DWORD	dwCPUVal = 0;
	DWORD	pdhErr;

	// Collect the current raw data value for all counters in the 
	// specified query and updates the status code of each counter 
	if (PdhCollectQueryData ( m_hQuery ) != ERROR_SUCCESS)
	{
		// Data collection failed.
		return 0;
	}

	switch (nCPU)
	{
	case 2:
		// Get the CPU raw counter value	
		if (pdhErr = PdhGetRawCounterValue ( m_hCounter2, NULL, &ppdhRawCounter ) == ERROR_SUCCESS)
		{
			// Format the CPU counter
			if (PdhGetFormattedCounterValue ( m_hCounter2, PDH_FMT_LONG, NULL, 
				&pdhFormattedValue) == ERROR_SUCCESS)
			{
				// Got the formatted value.  Show it on the graph
				dwCPUVal = pdhFormattedValue.longValue << 16;
			}
		}
		else
			return pdhErr;

	case 1:
		// Get the CPU raw counter value	
		if (pdhErr = PdhGetRawCounterValue ( m_hCounter1, NULL, &ppdhRawCounter ) == ERROR_SUCCESS)
		{
			// Format the CPU counter
			if (PdhGetFormattedCounterValue ( m_hCounter1, PDH_FMT_LONG, NULL, 
				&pdhFormattedValue) == ERROR_SUCCESS)
			{
				// Save the value in in the lo dword value.
				dwCPUVal |= pdhFormattedValue.longValue;
			}
		}
		else
			return pdhErr;
		break;
	}

	return dwCPUVal;
}


//////////////////////////////////////////////////////////////////////////////
// Method: GetLocalIP()
// Parameter: None
// Return Value: Local IP Address
// Purpose: Get the local IP address from the NIC interface
//////////////////////////////////////////////////////////////////////////////
CString CSystemInfo::GetLocalIP()
{
	DWORD dwErr;
	DWORD InfoLen = sizeof (MIB_IPADDRTABLE);
	PMIB_IPADDRTABLE pIPAddrList;
	
	pIPAddrList = (PMIB_IPADDRTABLE) malloc (InfoLen);

	if (GetIpAddrTable ( pIPAddrList, &InfoLen, TRUE) == ERROR_INSUFFICIENT_BUFFER)
	{
		free (pIPAddrList);
		pIPAddrList = (PMIB_IPADDRTABLE) malloc (InfoLen);
	}

	char strIPAddr[20];
	if (dwErr = GetIpAddrTable ( pIPAddrList, &InfoLen, TRUE))
	{
		return strIPAddr;
	}
	else {
		BOOL bFound = false;
		DWORD i = 0;

		while ((!bFound) && (i < pIPAddrList->dwNumEntries))
		{
			strIPAddr[0] = '\0';
			bFound = GetIPString ( pIPAddrList->table[i++].dwAddr, strIPAddr );
		}
	}

	if (strlen(strIPAddr) == 0)
		strcpy (strIPAddr, "Unable to determine IP address.");

	return strIPAddr;
}

//////////////////////////////////////////////////////////////////////////////
// Method: GetIPString()
// Parameter: dwIPAddr		IP address unformatted form
//			  strIPAddr		IP address in string format
// Return Value: fail or successful
// Purpose: Format the IP dword form into string form.
//////////////////////////////////////////////////////////////////////////////
DWORD CSystemInfo::GetIPString(DWORD dwIPAddr, char *strIPAddr)
{
	for (int i = 0; i < 4; i++)
	{
		char buf[5];

		if (dwIPAddr == 0)
			return false;
		if ((dwIPAddr & 0xff) == 127)
			return false;
		itoa (dwIPAddr & 0xff, buf, 10);
		dwIPAddr = dwIPAddr >> 8;
		strcat (strIPAddr, buf);
		if (i < 3)
			strcat (strIPAddr, ".");
	}

	return true;
}
