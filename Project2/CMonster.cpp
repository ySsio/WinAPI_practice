#include "pch.h"
#include "CMonster.h"
#include "CTimeMgr.h"
#include "CResMgr.h"
#include "CTexture.h"

CMonster::CMonster()
	: m_vCenterPos(Vec2(0.f,0.f))
	, m_fSpeed(100.f)
	, m_fMaxDistance(50.f)
	, m_iDir(1)
{
	// Texture �ε��ϱ�
	SetTexture(CResMgr::GetInst()->LoadTexture(L"MonsterTex", L"texture\\Monster.bmp"));
}

CMonster::~CMonster()
{
}

void CMonster::update()
{
	Vec2 vChangePos = GetPos();

	vChangePos.x += fDT * m_iDir * m_fSpeed;

	float fDiff = abs(m_vCenterPos.x - vChangePos.x) - m_fMaxDistance;

	// ��ȸ �Ÿ� ���ط��� �Ѿ���� Ȯ��
	if (0.f <= fDiff)
	{
		// ���� ����
		m_iDir *= -1;
		vChangePos.x += fDiff * m_iDir;
	}
		

	SetPos(vChangePos);
}

void CMonster::render(HDC _dc)
{
	// width/ height�� �翬�� ����ϱ� UINT���µ� ��ǥ�� ���� �� �� �����ϱ� int�� ��ȯ
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

}
