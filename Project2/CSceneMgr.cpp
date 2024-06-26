#include "global.h"
#include "CScene.h"
#include "CSceneMgr.h"
#include "CScene_Start.h"
#include "CScene_Tool.h"
#include "CEventMgr.h"

CSceneMgr::CSceneMgr()
	: m_arrScene{}
	, m_pCurScene(nullptr)
{

}

CSceneMgr::~CSceneMgr()
{
	// 씬 모두 삭제
	// delete를 사용할 경우 지금 부모포인터 (CScene*)으로 관리하고 있기 때문에
	// 부모의 소멸자만 호출해서 부모 부분만 메모리를 지우게 됨.
	// 따라서 자식 객체 (예:CScene_Start)의 소멸자도 호출되도록 부모 소멸자를 virtual로 설정해야 함.

	for (UINT i = 0; i < (UINT)SCENE_TYPE::END; ++i)
	{
		if (m_arrScene[i] != nullptr)
		{
			delete m_arrScene[i];
		}
		
	}
}

void CSceneMgr::init()
{
	// Scene 생성
	m_arrScene[(UINT)SCENE_TYPE::START] = new CScene_Start;
	m_arrScene[(UINT)SCENE_TYPE::START]->SetName(L"Start Scene");

	m_arrScene[(UINT)SCENE_TYPE::TOOL] = new CScene_Tool;
	m_arrScene[(UINT)SCENE_TYPE::START]->SetName(L"Tool Scene");
	//m_arrScene[(UINT)SCENE_TYPE::STAGE_01] = new CScene_Stage01;
	//m_arrScene[(UINT)SCENE_TYPE::STAGE_02] = new CScene_Stage02;

	// 현재 씬 지정
	m_pCurScene = m_arrScene[(UINT)SCENE_TYPE::START];
	m_pCurScene->Enter();
}

void CSceneMgr::update()
{
	m_pCurScene->update();
	m_pCurScene->finalupdate();
}

void CSceneMgr::render(HDC _dc)
{
	m_pCurScene->render(_dc);
}

void CSceneMgr::SaveObject(CObject* _pObj, GROUP_TYPE _etype)
{
	m_arrObjSaved.insert(make_pair(_pObj, _etype));
}

void CSceneMgr::LoadObject()
{
	map<CObject*, GROUP_TYPE>::iterator iter = m_arrObjSaved.begin();
	for (; iter != m_arrObjSaved.end(); ++iter)
	{
		m_pCurScene->AddObject(iter->first, iter->second);
	}
}

void CSceneMgr::ClearObject()
{
	// 실제로 메모리 해제하면 현재 로드한 씬에서도 사용 못하니까
	// 메모리 해제는 안하고 m_arrObjSaved만 비우는 거임.
	m_arrObjSaved.clear();
}

void CSceneMgr::ChangeScene(SCENE_TYPE _eNext)
{
	m_pCurScene->Exit();
	m_pCurScene = m_arrScene[(UINT)_eNext];
	m_pCurScene->Enter();
}

