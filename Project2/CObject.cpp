#include "pch.h"
#include "CObject.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CTexture.h"

CObject::CObject()
	: m_vPos{}
	, m_vScale{}
{
}

CObject::~CObject()
{
}

void CObject::render(HDC _dc)
{
	// width/ height은 당연히 양수니까 UINT였는데 좌표는 음수 될 수 있으니까 int로 변환
	int iWidth = (int)GetTexture()->Width();
	int iHeight = (int)GetTexture()->Height();

	Vec2 vPos = GetPos();

	//BitBlt(_dc
	//	, (int)(vPos.x - (float)iWidth / 2)
	//	, (int)(vPos.y - (float)iHeight / 2)
	//	, iWidth, iHeight
	//	, m_pTex->GetDC()
	//	, 0, 0, SRCCOPY);

	// 특정 조건은 투명처리해서 복사함. RGB(255,0,255) = magenta 색상
	// 선언만 되어있음 (Windows.h 안에 wingdi.h에) 구현부분 없음.
	// library를 참조해야 함. #pragma comment(lib, "Msimg32.lib")
	TransparentBlt(_dc
		, (int)(vPos.x - (float)iWidth / 2)
		, (int)(vPos.y - (float)iHeight / 2)
		, iWidth, iHeight
		, GetTexture()->GetDC()
		, 0, 0, iWidth, iHeight
		, RGB(255, 0, 255));
}
