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

	// 배회 거리 기준량을 넘어섰는지 확인
	if (0.f <= fDiff)
	{
		// 방향 변경
		m_iDir *= -1;
		vChangePos.x += fDiff * m_iDir;
	}
		

	SetPos(vChangePos);
}
