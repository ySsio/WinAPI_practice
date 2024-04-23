#include "global.h"
#include "CRigidBody.h"
#include "CObject.h"
#include "CTimeMgr.h"



CRigidBody::CRigidBody()
	: m_pOwner(nullptr)
	, m_fMass(1.f)
	, m_fFricCoef(100.f)
	, m_fMaxSpeed(300.f)
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

	
	if (!m_vVelocity.IsZero())
	{
		// 마찰력 적용
		Vec2 vFriction = -m_vVelocity;
		vFriction.Normalize();
		vFriction *= m_fFricCoef * fDT;

		if (vFriction.Length() >= m_vVelocity.Length())
		{
			m_vVelocity = Vec2(0.f, 0.f);
		}
		else
		{
			m_vVelocity += vFriction;
		}
	}
	

	// 속도 제한 검사
	if (m_vVelocity.Length() > m_fMaxSpeed)
	{
		m_vVelocity.Normalize();
		m_vVelocity *= m_fMaxSpeed;
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
