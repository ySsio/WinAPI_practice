#include "CScene_Start.h"
#include "CObject.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CCore.h"
#include "CTexture.h"
#include "CPathMgr.h"
#include "CCollisionMgr.h"

#include "CKeyMgr.h"
#include "CSceneMgr.h"

#include "CCamera.h"

CScene_Start::CScene_Start()
{
}

CScene_Start::~CScene_Start()
{
}

void CScene_Start::update()
{
	CScene::update(); // �θ��� ��� �״�� ��Ȱ���ϱ� ���� ȣ��.
	if (KEY_TAP(KEY::ENTER))
	{
		ChangeScene(SCENE_TYPE::TOOL);	// func.cpp�� ������ �����Լ�
	}

	if (KEY_TAP(KEY::LBTN))
	{
		Vec2 vLookAt = CCamera::GetInst()->GetRealPos(MOUSE_POS);
		CCamera::GetInst()->SetLookAt(vLookAt);
	}
}

void CScene_Start::Enter()
{
	// �� ������ �츱�� �޾ƿ���
	CSceneMgr::GetInst()->LoadObject();
	//CSceneMgr::GetInst()->ClearObject();
	
	// CObject �����ͷ� CPlayer ��ü ����
	
	CObject* pObj = new CPlayer;
	pObj->SetPos(Vec2(640.f, 384.f));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);
	SaveObject(pObj, GROUP_TYPE::PLAYER);

	//CObject* pOtherPlayer = pObj->Clone();	// CPlayer�� �ٿ�ĳ���� �ؾ� CPlayer�� ��������� ȣ�� ����
	//pOtherPlayer->SetPos(Vec2(740.f, 384.f));
	//AddObject(pOtherPlayer, GROUP_TYPE::PLAYER);

	//CCamera::GetInst()->SetTarget(pObj);

	// Monster Object �߰�
	
	int iMonCount = 10;
	float fMoveDist = 25.f;
	float fObjScale = 50.f;

	Vec2 vResolution = CCore::GetInst()->GetResolution();	// ���������
	CMonster * pMonsterObj = nullptr;

	for (int i = 0; i < iMonCount; ++i)
	{
		pMonsterObj = new CMonster;
		float xvalue = (fMoveDist + fObjScale / 2) + i * (vResolution.x - 2*(fMoveDist+fObjScale/2)) / (iMonCount-1);
		pMonsterObj->SetPos(Vec2(xvalue, -150.f));
		pMonsterObj->SetScale(Vec2(fObjScale, fObjScale));
		pMonsterObj->SetMoveDistance(fMoveDist);
		pMonsterObj->SetCenterPos(Vec2(xvalue, 100.f));
		AddObject(pMonsterObj, GROUP_TYPE::MONSTER);
	}

	// Ÿ�� �ε�
	//LoadTile(L"tile\\Start.tile");

	// �浹 ���� (Player�� Monster �׷찣���� �浹�� �߻��Ѵٰ� ����)
	// Player �׷�� Monster �׷� ���� �浹 üũ - Render ���� finalupdate ���� ���� �������� ����
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::PROJ_MONSTER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PROJ_PLAYER);
	

	// Camera Look ����
	CCamera::GetInst()->SetLookAt(vResolution / 2.f);	// �ػ� ���� ��ġ�� ī�޶� �߾����� ����


	// Camera ȿ�� ����
	CCamera::GetInst()->FadeOut(1.f);
	CCamera::GetInst()->FadeIn(1.f);
}

void CScene_Start::Exit()
{
	DeleteAll();

	// �̹� ������ �����ص״� �浹 �׷��� ��� ������.
	CCollisionMgr::GetInst()->Reset();
}


