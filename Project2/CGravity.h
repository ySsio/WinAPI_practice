#pragma once

class CObject;

class CGravity
{
private:
	CObject*	m_pOwner;
	bool		m_bGround;	// 땅에 붙어있는 지 확인

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

