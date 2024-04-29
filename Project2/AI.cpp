#include "AI.h"
#include "CState.h"

AI::AI()
	: m_pCurState(nullptr)
	, m_pOwner(nullptr)
{
}

AI::~AI()
{
	Safe_Delete_Map(m_mapState);
}

void AI::update()
{
	m_pCurState->update();
}


void AI::AddState(CState* _pState)
{
	assert(GetState(_pState->GetType()) == nullptr);

	m_mapState.insert(make_pair(_pState->GetType(), _pState));
	_pState->m_pAI = this;
}

CState* AI::GetState(MON_STATE _eState)
{
	map<MON_STATE, CState*>::iterator iter = m_mapState.find(_eState);

	if (iter != m_mapState.end())
		return iter->second;

	return nullptr;
}

void AI::SetCurState(MON_STATE _eState)
{
	m_pCurState = GetState(_eState);
	assert(m_pCurState);
}

void AI::ChangeState(MON_STATE _eState)
{
	CState* pNextState = GetState(_eState);

	// 원래 curstate 상태로 변경 요청 되었으면 오류
	assert(pNextState != m_pCurState);

	m_pCurState->Exit();

	m_pCurState = pNextState;

	m_pCurState->Enter();
}
