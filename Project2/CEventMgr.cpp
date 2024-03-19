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
	// ########### Dead object ���� #############
	
	// Dead �̺�Ʈ�� ó���� ���� �����ӿ���
	// Dead ���Ϳ� ����ִ� ������Ʈ�� ��� ������.
	for (size_t i = 0; i < m_vecDead.size(); i++)
	{
		delete m_vecDead[i];
	}

	m_vecDead.clear();
	// ##########################################

	

	// ############## Event ó�� ################
	
	// �׿��ִ� �̺�Ʈ�� ������ ���� �������� ó����.
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
		// ���� �̺�Ʈ�� ������ ��ü�� �����ϰ� �ִ� �κе� ������
		// ���� �� ������ ���� ���� ������ ���̶�� �̸� �˷��ְ�
		// �� ���� �����ӿ��� ������ �����Ѵ�.
		// ������ ������Ʈ�� ��Ƶ� �迭 �ʿ�. m_vecDead

		// lParam : Object Address

		// Object�� Dead ���·� ����
		// �������� ������Ʈ���� ��Ƶд�.
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
