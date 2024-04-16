#pragma once
#include "global.h"

class AI;

// 상속 용 추상클래스 (인터페이스)
class CState
{
private:
	AI*			m_pAI;
	MON_STATE	m_eState;

public:
	AI* GetAI() { return m_pAI; }
	MON_STATE GetType() { return m_eState; }

public:
	virtual void update() = 0;
	// 상태 전환할 때. 진입 / 탈출 함수
	virtual void Enter() = 0;
	virtual void Exit() = 0;


public:
	CState(MON_STATE _eState);
	virtual ~CState();

	friend class AI;
};

