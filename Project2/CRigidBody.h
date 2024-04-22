#pragma once

class CObject;

class CRigidBody
{
private:
	CObject*	m_pOwner;

	Vec2		m_vForce;	// �� (ũ��, ����) F=m*a
	Vec2		m_vAccel;	// ���ӵ�
	float		m_fMass;	// ����
	
	Vec2		m_vVelocity; // �ӵ� v = v0 + a*t (�� ������ ����ϴϱ� t=DT)

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

