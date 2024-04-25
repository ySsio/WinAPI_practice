#include "CGravity.h"
#include "CObject.h"
#include "CRigidBody.h"

CGravity::CGravity()
	: m_pOwner(nullptr)
	, m_bGround(false)
{
}

CGravity::CGravity(const CGravity& _other)
	: m_pOwner(nullptr)
	, m_bGround(false)
{
}

CGravity::~CGravity()
{
}

void CGravity::SetGround(bool _b)
{
	if (_b)
	{
		Vec2 vVelocity = m_pOwner->GetRigidBody()->GetVelocity();
		vVelocity.y = 0.f;
		m_pOwner->GetRigidBody()->SetVelocity(vVelocity);
	}
	m_bGround = _b;
}

void CGravity::finalupdate()
{
	if (!m_bGround)
		m_pOwner->GetRigidBody()->AddAccel(Vec2(0.f, 1000.f));
}