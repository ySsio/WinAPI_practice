#pragma once

class CObject;

class CRigidBody
{
private:
	CObject*	m_pOwner;

	Vec2		m_vForce;	// �� (ũ��, ����) F=m*a
	Vec2		m_vAccel;	// ���ӵ�
	float		m_fMass;	// ����

	float		m_fFricCoef; // �������. �����δ� ����������� �������� �������ִٰ� ..

	
	Vec2		m_vVelocity; // �ӵ� v = v0 + a*t (�� ������ ����ϴϱ� t=DT)
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

