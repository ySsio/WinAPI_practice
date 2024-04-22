#include "global.h"
#include "CRigidBody.h"
#include "CObject.h"
#include "CTimeMgr.h"



CRigidBody::CRigidBody()
	: m_pOwner(nullptr)
	, m_fMass(1.f)
{
}

CRigidBody::~CRigidBody()
{
}

void CRigidBody::finalupdate()
{
	// 힘의 크기 게산
	float fForce = m_vForce.Length();

	if (fForce != 0.f)
	{
		// 가속도 = 힘 / 질량
		m_vAccel = m_vForce / m_fMass;

		// 속도 v = v0 + at
		m_vVelocity += m_vAccel * fDT;
	}
	
	Move();

	// 다음 프레임에서 힘을 계산하기 전에 초기화
	m_vForce = Vec2(0.f, 0.f);
}

void CRigidBody::Move()
{
	Vec2 vPos = m_pOwner->GetPos();
	vPos += m_vVelocity * fDT;
	m_pOwner->SetPos(vPos);
}
