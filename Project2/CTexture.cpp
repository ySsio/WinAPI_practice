#include "pch.h"
#include "CTexture.h"


CTexture::CTexture()
	: m_dc(0)
	, m_hBit(0)
{
}

CTexture::~CTexture()
{
	DeleteDC(m_dc);
	DeleteObject(m_hBit);
}

void CTexture::Load(const wstring& _strFilePath)
{
	// _strFilePath�� ������. CRes�� ����� ������̹Ƿ� �����η� ��ȯ����� ��.
	// # ���� ���� �̰�
	m_hBit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str(), IMAGE_BITMAP , 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);

	assert(m_hBit);
}
