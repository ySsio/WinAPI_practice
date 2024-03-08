#include "pch.h"
#include "CMonster.h"
#include "CTimeMgr.h"
#include "CMissile.h"

#include "CSceneMgr.h"
#include "CScene.h"

CMonster::CMonster()
	: m_vCenterPos(Vec2(0.f, 0.f))
	, m_fSpeed(100.f)
	, m_fMaxDistance(50.f)
	, m_iDir(1)
	, m_fAttackFrequency(2.f)
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

	m_fAttackFrequency -= fDT;

	if (m_fAttackFrequency <= 0.f)
	{
		CreateMissile();
		m_fAttackFrequency = 2.f;
	}


	SetPos(vChangePos);
}

void CMonster::CreateMissile()
{
	Vec2 vMissilePos = GetPos();
	vMissilePos.y += GetScale().y / 2.f;

	CMissile* pMissile = new CMissile;
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(20.f, 20.f));
	pMissile->SetDir(false);
	pMissile->SetCenter(GetPos());

	CSceneMgr::GetInst()->GetCurScene()->AddObject(pMissile, GROUP_TYPE::DEFAULT);

}