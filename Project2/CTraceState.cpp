#include "global.h"
#include "CTraceState.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CPlayer.h"
#include "CMonster.h"

#include "CTimeMgr.h"

CTraceState::CTraceState()
	: CState(MON_STATE::TRACE)
{
}

CTraceState::~CTraceState()
{
}


void CTraceState::update()
{
	// Ÿ���� �� player�� �Ѿư���.
	CPlayer* pPlayer = (CPlayer*)CSceneMgr::GetInst()->GetCurScene()->GetPlayer();
	Vec2 vPlayerPos = pPlayer->GetPos();

	Vec2 vMonsterPos = GetMonster()->GetPos();

	Vec2 vMonDir = vPlayerPos - vMonsterPos;
	if (!vMonDir.IsZero())
		vMonDir.Normalize();

	vMonsterPos += vMonDir * GetMonster()->GetInfo().m_fSpeed * fDT;

	GetMonster()->SetPos(vMonsterPos);
}

void CTraceState::Enter()
{
}

void CTraceState::Exit()
{
}

