#include "pch.h"
#include "CMonster.h"
#include "CTimeMgr.h"

CMonster::CMonster()
	: m_vCenterPos(Vec2(0.f,0.f))
	, m_fSpeed(100.f)
	, m_fMaxDistance(50.f)
	, m_iDir(1)
{
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
