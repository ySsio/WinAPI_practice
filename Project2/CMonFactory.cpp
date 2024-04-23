#include "global.h"
#include "CMonFactory.h" 
#include "CMonster.h"
#include "AI.h"

#include "CIdleState.h"
#include "CTraceState.h"

#include "CRigidBody.h"


CMonster* CMonFactory::CreatMonster(MON_TYPE _eType, Vec2 _vPos)
{
	CMonster* pMon = nullptr;

	switch (_eType)
	{
	case MON_TYPE::NORMAL:
	{
		pMon = new CMonster;
		pMon->SetPos(_vPos);

		// MonInfo Setting
		tMonInfo info = {};
		info.m_fAttack = 10.f;
		info.m_fAttackRange = 50.f;
		info.m_fSearchRange = 300.f;
		info.m_fHP = 100.f;
		info.m_fSpeed = 150.f;

		pMon->SetMonInfo(info);

		pMon->CreateRigidBody();
		pMon->GetRigidBody()->SetMass(1.f);

		// AI Setting
		//AI* pAI = new AI;
		//pAI->AddState(new CIdleState);
		//pAI->AddState(new CTraceState);
		//pAI->SetCurState(MON_STATE::IDLE);

		//pMon->SetAI(pAI);
	}
		

		break;

	case MON_TYPE::RANGER:


		break;

	}

	assert(pMon);

	return pMon;
}
