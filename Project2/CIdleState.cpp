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

	// �÷��̾ ������ ���� �ȿ� ������
	if (fLen < pMonster->GetInfo().m_fSearchRange)
	{
		// ���� ���·� ��ȯ. �̺�Ʈ ó��!!
		ChangeAIState(GetAI(), MON_STATE::TRACE);
	}

	 
}

void CIdleState::Enter()
{
}

void CIdleState::Exit()
{
}