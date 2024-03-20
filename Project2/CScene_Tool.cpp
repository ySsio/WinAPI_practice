#include "pch.h"
#include "CScene_Tool.h"
#include "CKeyMgr.h"

#include "CCollisionMgr.h"
#include "CSceneMgr.h"

CScene_Tool::CScene_Tool()
{
}

CScene_Tool::~CScene_Tool()
{
}


void CScene_Tool::Enter()
{
	// 전 씬에서 살릴거 받아오기
	CSceneMgr::GetInst()->LoadObject();
	//CSceneMgr::GetInst()->ClearObject();
}

void CScene_Tool::Exit()
{
	DeleteAll();

	// 이번 씬에서 지정해뒀던 충돌 그룹을 모두 해제함.
	CCollisionMgr::GetInst()->Reset();
}

void CScene_Tool::update()
{
	CScene::update();
	if (KEY_TAP(KEY::ENTER))
	{
		ChangeScene(SCENE_TYPE::START);
	}
}
