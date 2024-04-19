#include "global.h"
#include "CIdleState.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CPlayer.h"
#include "CMonster.h"

CIdleState::CIdleState()
	: CState(MON_STATE::IDLE)
{
}

CIdleState::~CIdleState()
{
}

void CIdleState::update()
{
	CPlayer* pPlayer = (CPlayer*) CSceneMgr::GetInst()->GetCurScene()->GetPlayer();
	Vec2 vPlayerPos = pPlayer->GetPos();
	CMonster* pMonster = GetMonster();
	Vec2 vMonsterPos = pMonster->GetPos();

	float fLen = (vPlayerPos - vMonsterPos).Length();

	// 플레이어가 몬스터의 범위 안에 있으면
	if (fLen < pMonster->GetInfo().m_fSearchRange)
	{
		// 추적 상태로 전환. 이벤트 처리!!
		ChangeAIState(GetAI(), MON_STATE::TRACE);
	}

	 
}

void CIdleState::Enter()
{
}

void CIdleState::Exit()
{
}