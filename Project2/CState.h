#pragma once
#include "global.h"

class AI; 
class CMonster;

// ��� �� �߻�Ŭ���� (�������̽�)
class CState
{
private:
	AI*			m_pAI;
	MON_STATE	m_eState;

public:
	AI* GetAI() { return m_pAI; }
	MON_STATE GetType() { return m_eState; }
	CMonster* GetMonster();

public:
	virtual void update() = 0;
	// ���� ��ȯ�� ��. ���� / Ż�� �Լ�
	virtual void Enter() = 0;
	virtual void Exit() = 0;


public:
	CState(MON_STATE _eState);
	virtual ~CState();

	friend class AI;
};

