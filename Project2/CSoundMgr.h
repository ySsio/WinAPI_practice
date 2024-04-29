#pragma once

// 헤더 순서 중요
#include <mmsystem.h>
#include <dsound.h>
#include <dinput.h>

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dsound.lib")

class CSound;

class CSoundMgr
{
	SINGLETON(CSoundMgr)

private:
	LPDIRECTSOUND8	m_pSound;	// 사운드카드 대표 객체
	CSound*			m_pBGM;		// 현재 지정된 BGM

public:
	int init();
	LPDIRECTSOUND8 GetSoundDevice() { return m_pSound; }
	void RegisterToBGM(CSound* _pSound);
};

