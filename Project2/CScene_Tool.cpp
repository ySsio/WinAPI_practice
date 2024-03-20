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
	// �� ������ �츱�� �޾ƿ���
	CSceneMgr::GetInst()->LoadObject();
	//CSceneMgr::GetInst()->ClearObject();
}

void CScene_Tool::Exit()
{
	DeleteAll();

	// �̹� ������ �����ص״� �浹 �׷��� ��� ������.
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
