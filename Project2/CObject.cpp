#include "pch.h"
#include "CObject.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CTexture.h"
#include "CCollider.h"

CObject::CObject()
	: m_vPos{}
	, m_vScale{}
	, m_pTex(nullptr)
	, m_pCollider(nullptr)
{
}

CObject::~CObject()
{
	if (m_pCollider != nullptr)
		delete m_pCollider;
}

void CObject::CreateCollider()
{
	m_pCollider = new CCollider;
	m_pCollider->m_pOwner = this;
}

void CObject::finalupdate()
{
	if (m_pCollider)
		m_pCollider->finalupdate();
}

void CObject::render(HDC _dc)
{
	// width/ height은 당연히 양수니까 UINT였는데 좌표는 음수 될 수 있으니까 int로 변환
	int iWidth = (int)GetTexture()->Width();
	int iHeight = (int)GetTexture()->Height();

	Vec2 vPos = GetPos();

	TransparentBlt(_dc
		, (int)(vPos.x - (float)iWidth / 2)
		, (int)(vPos.y - (float)iHeight / 2)
		, iWidth, iHeight
		, GetTexture()->GetDC()
		, 0, 0, iWidth, iHeight
		, RGB(255, 0, 255));

	// 컴포넌트 렌더
	component_render(_dc);
}

void CObject::component_render(HDC _dc)
{
	if (m_pCollider != nullptr)
		m_pCollider->render(_dc);
}
