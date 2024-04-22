#pragma once

class CObject;

class CRigidBody
{
private:
	CObject*	m_pOwner;

	Vec2		m_vForce;	// 힘 (크기, 방향) F=m*a
	Vec2		m_vAccel;	// 가속도
	float		m_fMass;	// 질량
	
	Vec2		m_vVelocity; // 속도 v = v0 + a*t (매 프레임 계산하니까 t=DT)

public:
	void finalupdate();

public:
	void AddForce(Vec2 _vF) { m_vForce += _vF; }
	void SetMass(float _fMass) { m_fMass = _fMass; }
	
private:
	void Move();

public:
	CRigidBody();
	~CRigidBody();

	friend class CObject;
};

