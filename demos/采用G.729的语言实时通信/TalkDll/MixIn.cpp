// MixIn.cpp: implementation of the CMixIn class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MixIn.h"

#define	WND_CLASS_NAME	"Input Volume Msg Wnd Class"
#define	WND_NAME		"Input Volume Msg Wnd"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
static CMixIn *g_pThis = NULL;
LRESULT CALLBACK CMixIn::MixerWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	if ( uMsg == MM_MIXM_CONTROL_CHANGE )
	{
		if ( g_pThis )
		{
			g_pThis->OnControlChanged( (DWORD)lParam );
		}	
	}
	return ::DefWindowProc( hwnd, uMsg, wParam, lParam);
}

CMixIn::CMixIn() :
	m_iDevNum(0),
	m_uiMixerId(0),
	m_hMixer(0),
	m_hWnd(NULL),
	m_bIni(FALSE),
	m_dwMinimalVolume(0),
	m_dwMaximalVolume(100)
{
	g_pThis = this;
}

CMixIn::~CMixIn()
{

}
MMRESULT CMixIn::GetLastMMError()
{
	return m_mmr;
}
CString CMixIn::GetLastErrorString()
{
	char buffer[256];
	memset(buffer,0,256);
	switch(m_mmr)
	{
	case MMSYSERR_NOERROR:
		sprintf(buffer,"No error.");
		break;
	case MIXERR_INVALCONTROL:
		sprintf(buffer,"Specified device handle is invalid.");
		break;
	case MMSYSERR_BADDEVICEID:
		sprintf(buffer,"The hmxobj parameter specifies an invalid device identifier.");
		break;
	case MMSYSERR_INVALFLAG:
		sprintf(buffer,"One or more flags are invalid.");
		break;
	case MMSYSERR_INVALHANDLE:
		sprintf(buffer,"The hmxobj parameter specifies an invalid handle.");
		break;
	case MMSYSERR_INVALPARAM:
		sprintf(buffer,"One or more parameters are invalid.");
		break;
	case MMSYSERR_NODRIVER:
		sprintf(buffer,"No mixer device is available for the object specified by hmxobj.");
		break;
	case MIXERR_INVALLINE:
		sprintf(buffer,"The audio line reference is invalid..");
		break;
	case MMSYSERR_NOTSUPPORTED:
		sprintf(buffer,"The mixer device did not process the message.");
		break;
	case MMSYSERR_ALLOCATED:
		sprintf(buffer,"The specified resource is already allocated by the maximum number of clients possible.");
		break;
	case MMSYSERR_NOMEM:
		sprintf(buffer,"Unable to allocate resources.");
		break;
	default:
		sprintf(buffer,"Unknow error,Error code %d",m_mmr);
		break;
	}
	return buffer;
}

BOOL CMixIn::OpenMixer()
{
	m_iDevNum = mixerGetNumDevs();
	if (m_iDevNum == 0)
	{
		TRACE("There (is) are no device mixer.\n");
		return FALSE;
	}
	WAVEFORMATEX wfx;
	memset( &wfx, 0, sizeof(WAVEFORMATEX) );
	wfx.wFormatTag = WAVE_FORMAT_PCM;
	wfx.nChannels = 1;
	wfx.nSamplesPerSec = 8000;
	wfx.nAvgBytesPerSec = 1 * 8000 * 16 / 8;
	wfx.nBlockAlign = 16 * 1 / 8;
	wfx.wBitsPerSample = 16;
	wfx.cbSize = 0;

	HWAVEIN hwaveIn;
	m_mmr = waveInOpen( &hwaveIn, WAVE_MAPPER, &wfx, 0L, 0L, CALLBACK_NULL );

	if ( m_mmr != MMSYSERR_NOERROR )
	{
		return false;
	}
	m_mmr = mixerGetID((HMIXEROBJ)hwaveIn, &m_uiMixerId, MIXER_OBJECTF_HWAVEIN );
	waveInClose( hwaveIn );
	if ( m_mmr != MMSYSERR_NOERROR )
	{
		return false;
	}

	// Exposing Window to Mixer
	WNDCLASSEX wcx;
	memset( &wcx, 0, sizeof(WNDCLASSEX) );	
	wcx.cbSize = sizeof(WNDCLASSEX);
	wcx.lpszClassName = WND_CLASS_NAME;
	wcx.lpfnWndProc = (WNDPROC)MixerWndProc;
	::RegisterClassEx(&wcx);
	m_hWnd = CreateWindow(	WND_CLASS_NAME,
							WND_NAME,
							WS_POPUP | WS_DISABLED,
							0, 0, 0, 0,
							NULL, NULL, NULL, NULL );
	if ( !m_hWnd )
	{
	
		return false;
	}
	::ShowWindow(m_hWnd, SW_HIDE);

	m_mmr = mixerOpen(&m_hMixer, m_uiMixerId, (DWORD)m_hWnd, 0L, CALLBACK_WINDOW );
	if (m_mmr != MMSYSERR_NOERROR )
	{
		return false;
	}
	return TRUE;
}

BOOL CMixIn::Initialize(UINT uLineIndex)
{
	if (m_hMixer)
	{
		TRACE("You haven't open the mixer.\n");
		return FALSE;
	}

	MIXERLINE MixerLine;
	memset( &MixerLine, 0, sizeof(MIXERLINE) );
	MixerLine.cbStruct = sizeof(MIXERLINE);
	MixerLine.dwComponentType = MIXERLINE_COMPONENTTYPE_DST_WAVEIN;
	MixerLine.dwSource = 1;

	m_mmr = mixerGetLineInfo( (HMIXEROBJ)m_hMixer, &MixerLine, MIXER_GETLINEINFOF_COMPONENTTYPE );
	if ( m_mmr != MMSYSERR_NOERROR )
	{
		return false;
	}
	MIXERCONTROL Control;
	memset( &Control, 0, sizeof(MIXERCONTROL));
	Control.cbStruct = sizeof(MIXERCONTROL);

	MIXERLINECONTROLS LineControls;
	memset( &LineControls, 0, sizeof(MIXERLINECONTROLS));
	LineControls.cbStruct = sizeof(MIXERLINECONTROLS);

	MIXERLINE Line;
	memset( &Line, 0, sizeof(MIXERLINE) );
	Line.cbStruct = sizeof(MIXERLINE);

	if ((uLineIndex < MixerLine.cConnections))
	{
		Line.dwDestination = MixerLine.dwDestination;
		Line.dwSource = uLineIndex;
		m_mmr = mixerGetLineInfo((HMIXEROBJ)m_hMixer, &Line, MIXER_GETLINEINFOF_SOURCE );
		if ( m_mmr != MMSYSERR_NOERROR )
		{
			return false;
		}

		LineControls.dwControlType = MIXERCONTROL_CONTROLTYPE_VOLUME;
		LineControls.dwLineID = Line.dwLineID;
		LineControls.cControls = 1;
		LineControls.cbmxctrl = sizeof(MIXERCONTROL);
		LineControls.pamxctrl = &Control;
		m_mmr = mixerGetLineControls( (HMIXEROBJ)m_hMixer, &LineControls, MIXER_GETLINECONTROLSF_ONEBYTYPE );
		if ( m_mmr == MMSYSERR_NOERROR )
		{
			if ((Control.fdwControl & MIXERCONTROL_CONTROLF_DISABLED) )
			{
				return FALSE;
			}
		}
		else
		{
			return FALSE;
		}		
	} 
	else
	{
		return false;
	}
	m_dwMinimalVolume = Control.Bounds.dwMinimum;
	m_dwMaximalVolume = Control.Bounds.dwMaximum;

	return TRUE;
}

BOOL CMixIn::EnumerateInputLines(int &dwUserValue)
{
	if (!m_hMixer)
	{
		TRACE("Handle of mix hasn't been get.\n");
		return FALSE;
	}
	MIXERLINE MixerLine;
	memset( &MixerLine, 0, sizeof(MIXERLINE) );
	MixerLine.cbStruct = sizeof(MIXERLINE);
	MixerLine.dwComponentType = MIXERLINE_COMPONENTTYPE_SRC_WAVEOUT ;
								 
	m_mmr = mixerGetLineInfo( (HMIXEROBJ)m_hMixer, &MixerLine, MIXER_GETLINEINFOF_COMPONENTTYPE );
	if (m_mmr != MMSYSERR_NOERROR )
	{
		return false;
	}

	MIXERLINE Line;
	for (UINT uLineIndex = 0; uLineIndex < MixerLine.cConnections; uLineIndex++ )
	{
		memset( &Line, 0, sizeof(MIXERLINE));
		Line.cbStruct = sizeof(MIXERLINE);
		Line.dwDestination = MixerLine.dwDestination;
		Line.dwSource = uLineIndex;
		m_mmr = mixerGetLineInfo((HMIXEROBJ)m_hMixer, &Line, MIXER_GETLINEINFOF_SOURCE );
		if (m_mmr != MMSYSERR_NOERROR )
		{
			return false;
		}

		if ( Line.dwComponentType == MIXERLINE_COMPONENTTYPE_SRC_MICROPHONE )
		{
			dwUserValue = uLineIndex;
			break;
		}
	}
	return true;
}

BOOL CMixIn::CloseMixer()
{
	if (m_hMixer)
	{
		m_mmr = mixerClose((HMIXER)m_hMixer);
		if (m_mmr != MMSYSERR_NOERROR )
		{
			return false;
		}
	}
	return TRUE;
}

BOOL CMixIn::Ini()
{
	if (m_bIni)
	{
		TRACE("Mix in has alreadly ini.\n");		
		return FALSE;
	}
	if (!OpenMixer())
	{
		TRACE("%s.\n",GetLastErrorString());
		return FALSE;
	};

	int i=-1;
	EnumerateInputLines(i);
	if(i != -1)
	{
		if (!Initialize(i))
		{
			TRACE("%s.\n",GetLastErrorString());
		};
	}
	m_bIni = TRUE;
	return TRUE;
}

BOOL CMixIn::UnIni()
{
	if (!m_bIni)
	{
		TRACE("Mix in hasn't ini.\n");
		return FALSE;
	}
	::DestroyWindow( m_hWnd );
	CloseMixer();

	m_iDevNum = 0;
	m_uiMixerId = 0;
	m_hMixer = 0;
	m_hWnd = NULL;
	m_bIni = FALSE;
	m_dwMinimalVolume = 0;
	m_dwMaximalVolume = 100;
	return TRUE;
}

void CMixIn::OnControlChanged(int iValue)
{

}

DWORD CMixIn::GetMinimalVolume()
{
	if (!m_bIni)
	{
		TRACE("Mix in hasn't ini.\n");
		return 0;
	}
	return this->m_dwMinimalVolume ;
}

DWORD CMixIn::GetMaximalVolume()
{
	if (!m_bIni)
	{
		TRACE("Mix in hasn't ini.\n");
		return 100;
	}
	return this->m_dwMaximalVolume ;
}

DWORD CMixIn::GetCurrentVolume()
{
	if (!m_bIni)
	{
		TRACE("Mix in hasn't ini.\n");
		return 0;
	}
	return 0;
}

void CMixIn::SetCurrentVolume(DWORD dwValue)
{
}

