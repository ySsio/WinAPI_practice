#include "pch.h"
#include "CCore.h"

// ���� 1.
// Ŭ�������� ������ ���� ����� �ۿ��� �ݵ�� �ʱ�ȭ ����� �Ѵ�. ���ϸ� ��ũ���� ��
// CCore* CCore::g_pInst = nullptr;



// ���� 2.
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

	// �ػ󵵿� �°� ������ ũ�� ����



	HRESULT hr = E_FAIL; // E_FAIL / S_OK

	// FAILED ��ũ�δ� ���� ������ true�� �Լ� ������. S_OK == 0, S_FALSE == 1, E_FAIL < 0
	if (FAILED(hr))
	{
		return E_FAIL;
	}
	
	return S_OK;
}

void CCore::progress()
{
}
