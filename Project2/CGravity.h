#pragma once

class CObject;

class CGravity
{
private:
	CObject*	m_pOwner;
	bool		m_bGround;	// ���� �پ��ִ� �� Ȯ��

public:
	void SetGround(bool _b);
	bool GetGround() { return m_bGround; }

public:
	void finalupdate();

public:
	CGravity();
	CGravity(const CGravity& _other);
	~CGravity();

	friend class CObject;
};

