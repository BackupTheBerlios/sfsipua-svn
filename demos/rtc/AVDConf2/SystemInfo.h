// SystemInfo.h: interface for the CSystemInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYSTEMINFO_H__2A945FB9_5C0C_4FA3_9DFA_48B9E00EF45D__INCLUDED_)
#define AFX_SYSTEMINFO_H__2A945FB9_5C0C_4FA3_9DFA_48B9E00EF45D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "pdh.h"

#ifdef CPUINFOHELPER_EXPORTS
#define CPUINFOHELPER_API extern "C" __declspec(dllexport)
#else
#define CPUINFOHELPER_API extern "C" __declspec(dllimport)
#endif

#define HT_BIT             0x10000000     // EDX[28]  Bit 28 is set if HT is supported
#define FAMILY_ID          0x0F00         // EAX[11:8] Bit 8-11 contains family processor ID.
#define PENTIUM4_ID        0x0F00         
#define EXT_FAMILY_ID      0x0F00000      // EAX[23:20] Bit 20-23 contains extended family processor ID
#define NUM_LOGICAL_BITS   0x00FF0000     // EBX[23:16] Bit 16-23 in ebx contains the number of logical
                                          // processors per physical processor when execute cpuid with 
                                          // eax set to 1

#define INITIAL_APIC_ID_BITS  0xFF000000  // EBX[31:24] Bits 24-31 (8 bits) return the 8-bit unique 
                                          // initial APIC ID for the processor this code is running on.
                                          // Default value = 0xff if HT is not supported


// Status Flag
#define HT_NOT_CAPABLE           0
#define HT_ENABLED               1
#define HT_DISABLED              2
#define HT_SUPPORTED_NOT_ENABLED 3
#define HT_CANNOT_DETECT         4


class CSystemInfo  
{
public:
	DWORD GetIPString ( DWORD dwIPAddr, char *strIPAddr);
	CString GetLocalIP();
	void UpdatePerfMeter (int nCPUID, CProgressCtrl cCPUMeter, int IDCPUPercent);
	void UnInitPerfCtr();
	HRESULT InitPerfCounter(DWORD dwCPUCount);
	DWORD GetCPUInfo();
	CSystemInfo();
	DWORD GetCPUCycle(int nCPU);
	virtual ~CSystemInfo();

private:
	DWORD m_dwCPUCount;
	HMODULE m_hMod;
	HCOUNTER m_hCounter1;		// Counter Handle CPU 1
	HCOUNTER m_hCounter2;		// Counter Handle CPU 2
	HQUERY m_hQuery;			// Query Handle

	unsigned char CPUCount(unsigned char *LogicalNum,unsigned char *PhysicalNum);
	unsigned char GetAPIC_ID();
	unsigned char LogicalProcPerPhysicalProc();
	DWORD HTSupported();
};

#endif // !defined(AFX_SYSTEMINFO_H__2A945FB9_5C0C_4FA3_9DFA_48B9E00EF45D__INCLUDED_)
