#include "pch.h"
#include "CEventMgr.h"

#include "CObject.h"
#include "CSceneMgr.h"
#include "CScene.h"

CEventMgr::CEventMgr()
	: m_vecEvent{}
	, m_vecDead{}
{

}

CEventMgr::~CEventMgr() {

}

void CEventMgr::update()
{
	// ########### Dead object 삭제 #############
	
	// Dead 이벤트를 처리한 다음 프레임에서
	// Dead 벡터에 들어있는 오브젝트를 모두 삭제함.
	for (size_t i = 0; i < m_vecDead.size(); i++)
	{
		delete m_vecDead[i];
	}

	m_vecDead.clear();
	// ##########################################

	

	// ############## Event 처리 ################
	
	// 쌓여있는 이벤트를 프레임 가장 마지막에 처리함.
	for (size_t i = 0; i < m_vecEvent.size(); i++)
	{
		Execute(m_vecEvent[i]);
	}

	m_vecEvent.clear();
	// ##########################################

}

void CEventMgr::Execute(const tEvent& _eve)
{
	switch (_eve.eEven)
	{
	case EVENT_TYPE::CREATE_OBJECT:
	{
		// lParam : Object Address
		// rParam : GROUP_TYPE
		CObject* pNewObj = (CObject*)_eve.lParam;	// upcasting
		GROUP_TYPE eType = (GROUP_TYPE)_eve.wParam;

		CSceneMgr::GetInst()->GetCurScene()->AddObject(pNewObj, eType);
	}
		break;

	case EVENT_TYPE::DELETE_OBJECT:
	{
		// 삭제 이벤트는 삭제될 객체를 참조하고 있던 부분들 때문에
		// 다음 한 프레임 동안 삭제 예정할 것이라고 미리 알려주고
		// 그 다음 프레임에서 실제로 제거한다.
		// 삭제할 오브젝트를 모아둘 배열 필요. m_vecDead

		// lParam : Object Address

		// Object를 Dead 상태로 변경
		// 삭제예정 오브젝트들을 모아둔다.
		CObject* pDeadObj = (CObject*)_eve.lParam;
		pDeadObj->SetDead();
		m_vecDead.push_back(pDeadObj);
	}
		break;

	case EVENT_TYPE::SCENE_CHANGE:

		break;
	}

	
}

void CEventMgr::AddEvent(const tEvent& _eve)
{
	m_vecEvent.push_back(_eve);
}
