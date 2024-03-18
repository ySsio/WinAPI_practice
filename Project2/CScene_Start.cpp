#include "pch.h"
#include "CScene_Start.h"
#include "CObject.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CCore.h"
#include "CTexture.h"
#include "CPathMgr.h"
#include "CCollisionMgr.h"

CScene_Start::CScene_Start()
{
}

CScene_Start::~CScene_Start()
{
}

void CScene_Start::Enter()
{
	// CObject 포인터로 CPlayer 객체 생성
	CObject* pObj = new CPlayer;
	pObj->SetPos(Vec2(640.f,384.f));
	pObj->SetScale(Vec2(100.f,100.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);

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
		pMonsterObj->SetPos(Vec2(xvalue, 50.f));
		pMonsterObj->SetScale(Vec2(fObjScale, fObjScale));
		pMonsterObj->SetMoveDistance(fMoveDist);
		pMonsterObj->SetCenterPos(Vec2(xvalue, 384.f));
		pMonsterObj->SetTarget(pObj);
		AddObject(pMonsterObj, GROUP_TYPE::MONSTER);
	}

	// 충돌 지정 (Player과 Monster 그룹간에는 충돌이 발생한다고 지정)
	// Player 그룹과 Monster 그룹 간의 충돌 체크 - Render 직전 finalupdate 이후 가장 마지막에 로직
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::DEFAULT, GROUP_TYPE::MONSTER);
	
}

void CScene_Start::Exit()
{
	// 이번 씬에서 지정해뒀던 충돌 그룹을 모두 해제함.
	CCollisionMgr::GetInst()->Reset();
}
