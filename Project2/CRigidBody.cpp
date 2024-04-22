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
	// ���� ũ�� �Ի�
	float fForce = m_vForce.Length();

	if (fForce != 0.f)
	{
		// ���ӵ� = �� / ����
		m_vAccel = m_vForce / m_fMass;

		// �ӵ� v = v0 + at
		m_vVelocity += m_vAccel * fDT;
	}
	
	Move();

	// ���� �����ӿ��� ���� ����ϱ� ���� �ʱ�ȭ
	m_vForce = Vec2(0.f, 0.f);
}

void CRigidBody::Move()
{
	Vec2 vPos = m_pOwner->GetPos();
	vPos += m_vVelocity * fDT;
	m_pOwner->SetPos(vPos);
}
