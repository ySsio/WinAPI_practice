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
	CScene::update(); // 부모쪽 기능 그대로 재활용하기 위해 호출.
	if (KEY_TAP(KEY::ENTER))
	{
		ChangeScene(SCENE_TYPE::TOOL);	// func.cpp에 구현된 전역함수
	}

	if (KEY_TAP(KEY::LBTN))
	{
		Vec2 vLookAt = CCamera::GetInst()->GetRealPos(MOUSE_POS);
		CCamera::GetInst()->SetLookAt(vLookAt);
	}
}

void CScene_Start::Enter()
{
	// 전 씬에서 살릴거 받아오기
	CSceneMgr::GetInst()->LoadObject();
	//CSceneMgr::GetInst()->ClearObject();
	
	// CObject 포인터로 CPlayer 객체 생성
	
	CObject* pObj = new CPlayer;
	pObj->SetPos(Vec2(640.f, 384.f));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);
	SaveObject(pObj, GROUP_TYPE::PLAYER);

	//CObject* pOtherPlayer = pObj->Clone();	// CPlayer로 다운캐스팅 해야 CPlayer의 복사생성자 호출 가능
	//pOtherPlayer->SetPos(Vec2(740.f, 384.f));
	//AddObject(pOtherPlayer, GROUP_TYPE::PLAYER);

	//CCamera::GetInst()->SetTarget(pObj);

	// Monster Object 추가
	
	int iMonCount = 10;
	float fMoveDist = 25.f;
	float fObjScale = 50.f;

	Vec2 vResolution = CCore::GetInst()->GetResolution();	// 복사생성자
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

	// 타일 로딩
	//LoadTile(L"tile\\Start.tile");

	// 충돌 지정 (Player과 Monster 그룹간에는 충돌이 발생한다고 지정)
	// Player 그룹과 Monster 그룹 간의 충돌 체크 - Render 직전 finalupdate 이후 가장 마지막에 로직
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::PROJ_MONSTER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PROJ_PLAYER);
	

	// Camera Look 지정
	CCamera::GetInst()->SetLookAt(vResolution / 2.f);	// 해상도 절반 위치를 카메라 중앙으로 설정


	// Camera 효과 지정
	CCamera::GetInst()->FadeOut(1.f);
	CCamera::GetInst()->FadeIn(1.f);
}

void CScene_Start::Exit()
{
	DeleteAll();

	// 이번 씬에서 지정해뒀던 충돌 그룹을 모두 해제함.
	CCollisionMgr::GetInst()->Reset();
}


