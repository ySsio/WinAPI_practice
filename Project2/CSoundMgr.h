#pragma once

// ��� ���� �߿�
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
	LPDIRECTSOUND8	m_pSound;	// ����ī�� ��ǥ ��ü
	CSound*			m_pBGM;		// ���� ������ BGM

public:
	int init();
	LPDIRECTSOUND8 GetSoundDevice() { return m_pSound; }
	void RegisterToBGM(CSound* _pSound);
};

