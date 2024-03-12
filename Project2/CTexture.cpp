#include "pch.h"
#include "CTexture.h"
#include "CCore.h"


CTexture::CTexture()
	: m_dc(0)
	, m_hBit(0)
	, m_bitInfo{}
{
}

CTexture::~CTexture()
{
	DeleteDC(m_dc);
	DeleteObject(m_hBit);
}

void CTexture::Load(const wstring& _strFilePath)
{
	// _strFilePath는 절대경로. CRes의 멤버는 상대경로이므로 절대경로로 변환해줘야 함.
	// # 인자 뭔데 이거
	const wchar_t* a = _strFilePath.c_str();

	// # 인식이 안되는 파일이 있네..? 그림판에서 24비트 비트맵으로 저장하니까 되더만
	m_hBit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str(), IMAGE_BITMAP , 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	assert(m_hBit);


	// 비트맵과 연결할 dc
	m_dc = CreateCompatibleDC(CCore::GetInst()->GetMainDC());

	// 비트맵과 dc연결
	HBITMAP hPrevBit = (HBITMAP)SelectObject(m_dc, m_hBit);
	DeleteObject(hPrevBit);

	// 비트맵 정보 (BITMAP 구조체)
	GetObject(m_hBit, sizeof(BITMAP), &m_bitInfo);
	
}
