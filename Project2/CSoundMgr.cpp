#include "global.h"
#include "CSoundMgr.h"
#include "CResMgr.h"
#include "CSound.h"
#include "CCore.h"

CSoundMgr::CSoundMgr()
	: m_pSound(nullptr)
	, m_pBGM(nullptr)
{
}

CSoundMgr::~CSoundMgr()
{
}


int CSoundMgr::init()
{
	// 사운드 카드 장치 초기화. m_pSound가 사운드 카드로 연결해주는 객체가 됨
	if (FAILED(DirectSoundCreate8(NULL, &m_pSound, NULL)))
	{
		MessageBox(NULL, L"사운드 디바이스 생성 실패", L"SYSTEM ERROR", MB_OK);
		return false;
	}

	// 사운드 디바이스 협조레벨 설정
	HWND hWnd = CCore::GetInst()->GetMainHwnd();
	if (FAILED(m_pSound->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE)))
	{
		MessageBox(NULL, L"사운드 디바이스 협조 레벨 설정", L"SYSTEM ERROR", MB_OK);
		return false;
	}
	return true;
}

void CSoundMgr::RegisterToBGM(CSound* _pSound)
{
	if (m_pBGM != nullptr)
		m_pBGM->Stop();

	m_pBGM = _pSound;
}
