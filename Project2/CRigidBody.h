#pragma once

class CObject;

class CRigidBody
{
private:
	CObject*	m_pOwner;

	Vec2		m_vForce;	// 힘 (크기, 방향) F=m*a
	Vec2		m_vAccel;	// 가속도
	float		m_fMass;	// 질량

	float		m_fFricCoef; // 마찰계수. 실제로는 정지마찰계수 운동마찰계수 나눠져있다고 ..

	
	Vec2		m_vVelocity; // 속도 v = v0 + a*t (매 프레임 계산하니까 t=DT)
	Vec2		m_vMaxVelocity;

public:
	void finalupdate();

public:
	void AddForce(Vec2 _vF) { m_vForce += _vF; }
	void AddAccel(Vec2 _vA) { m_vForce += _vA * m_fMass; }

	void SetMass(float _fMass) { m_fMass = _fMass; }
	float GetMass() { return m_fMass; }
	float GetSpeed() { return m_vVelocity.Length(); }
	Vec2 GetVelocity() { return m_vVelocity; }
	Vec2 GetAccel() { return m_vAccel; }

	void SetVelocity(Vec2 _v) { m_vVelocity = _v; }
	void AddVelocity(Vec2 _v) { m_vVelocity += _v; }
	void SetMaxVelocity(Vec2 _v) { m_vMaxVelocity = _v; }
	
	
private:
	void Move();

public:
	CRigidBody();
	~CRigidBody();

	friend class CObject;
};

