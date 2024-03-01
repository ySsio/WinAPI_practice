#include "pch.h"
#include "CCore.h"

// 구현 1.
// 클래스에서 선언한 정적 멤버는 밖에서 반드시 초기화 해줘야 한다. 안하면 링크에러 남
// CCore* CCore::g_pInst = nullptr;



// 구현 2.
CCore::CCore()
{

}

CCore::~CCore()
{

}

int CCore::init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;

	// 해상도에 맞게 윈도우 크기 조정



	HRESULT hr = E_FAIL; // E_FAIL / S_OK

	// FAILED 매크로는 음수 받으면 true인 함수 저장함. S_OK == 0, S_FALSE == 1, E_FAIL < 0
	if (FAILED(hr))
	{
		return E_FAIL;
	}
	
	return S_OK;
}

void CCore::progress()
{
}
