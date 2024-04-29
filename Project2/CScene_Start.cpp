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
#include "SelectGDI.h"

#include "AI.h"
#include "CIdleState.h"
#include "CTraceState.h"

#include "CTimeMgr.h"

#include "CRigidBody.h"

#include "CGround.h"

#include "CResMgr.h"
#include "CSound.h"


CScene_Start::CScene_Start()
	: m_bUseForce(false)
	, m_fForceRadius(500.f)
	, m_fCurRadius(0.f)
	, m_fForce(500.f)
{
}

CScene_Start::~CScene_Start()
{
}

void CScene_Start::update()
{
	//CScene::update(); // 부모쪽 기능 그대로 재활용하기 위해 호출.
	if (KEY_TAP(KEY::ENTER))
	{
		ChangeScene(SCENE_TYPE::TOOL);	// func.cpp에 구현된 전역함수
	}

	if (KEY_TAP(KEY::LBTN))
	{
		Vec2 vLookAt = CCamera::GetInst()->GetRealPos(MOUSE_POS);
		CCamera::GetInst()->SetLookAt(vLookAt);
	}

	if (KEY_HOLD(KEY::RBTN))
	{
		m_bUseForce = true;
		CreateForce();
	}
	else
	{
		m_bUseForce = false;
	}

	

	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		const vector<CObject*>& vecObj = GetGroupObject((GROUP_TYPE)i);

		for (size_t j = 0; j < vecObj.size(); ++j)
		{
			// 데드 상태인 오브젝트는 update 제외
			if (vecObj[j]->IsDead()) continue;

			if (m_bUseForce && vecObj[j]->GetRigidBody())
			{
				Vec2 vDiff = vecObj[j]->GetPos() - m_vForcePos;
				float fDiff = vDiff.Length();

				if (fDiff < m_fForceRadius)
				{
					float fForce = m_fForce * (1.f - fDiff / m_fForceRadius);

					vDiff.Normalize();
					vecObj[j]->GetRigidBody()->AddForce(vDiff *fForce);
				}

			}

			vecObj[j]->update();
		}
	}

}

void CScene_Start::render(HDC _dc)
{
	CScene::render(_dc);

	if (!m_bUseForce)
		return;

	SelectGDI gdi(_dc, BRUSH_TYPE::HOLLOW);
	SelectGDI gdi2(_dc, PEN_TYPE::GREEN);

	m_fCurRadius += m_fForceRadius * fDT;
	if (m_fCurRadius > m_fForceRadius)
	{
		m_fCurRadius = 0.f;
	}

	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(m_vForcePos);

	Ellipse(_dc
		, (int)(vRenderPos.x - m_fCurRadius)
		, (int)(vRenderPos.y - m_fCurRadius)
		, (int)(vRenderPos.x + m_fCurRadius)
		, (int)(vRenderPos.y + m_fCurRadius));

}

void CScene_Start::CreateForce()
{
	m_vForcePos = CCamera::GetInst()->GetRealPos(MOUSE_POS);
	

}

void CScene_Start::Enter()
{
	CResMgr::GetInst()->LoadSound(L"BGM_01", L"sound\\RoadBgm.wav");
	CResMgr::GetInst()->LoadSound(L"JUMP", L"sound\\Effect1.wav");
	CResMgr::GetInst()->LoadSound(L"GROUND", L"sound\\wood.wav");
	CSound* pNewSound = CResMgr::GetInst()->FindSound(L"BGM_01");

	//pNewSound->Play();

	pNewSound->SetPosition(50.f);
	pNewSound->PlayToBGM(true);
	pNewSound->SetVolume(60.f);






	// 전 씬에서 살릴거 받아오기
	CSceneMgr::GetInst()->LoadObject();
	//CSceneMgr::GetInst()->ClearObject();
	
	// CObject 포인터로 CPlayer 객체 생성
	
	CObject* pObj = new CPlayer;
	pObj->SetName(L"Player");
	pObj->SetPos(Vec2(640.f, 384.f));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);
	SaveObject(pObj, GROUP_TYPE::PLAYER);

	RegisterPlayer(pObj);

	//CObject* pOtherPlayer = pObj->Clone();	// CPlayer로 다운캐스팅 해야 CPlayer의 복사생성자 호출 가능
	//pOtherPlayer->SetPos(Vec2(740.f, 384.f));
	//AddObject(pOtherPlayer, GROUP_TYPE::PLAYER);

	//CCamera::GetInst()->SetTarget(pObj);

	// Monster Object 추가
	
	int iMonCount = 1;
	float fMoveDist = 25.f;
	float fObjScale = 50.f;

	Vec2 vResolution = CCore::GetInst()->GetResolution();	// 복사생성자
	CMonster * pMonsterObj = CMonFactory::CreatMonster(MON_TYPE::NORMAL,vResolution/2.f - Vec2(0.f,300.f));
	AddObject(pMonsterObj,GROUP_TYPE::MONSTER);

	// Ground Object 추가
	CGround* pGround = new CGround;
	pGround->SetName(L"Ground");
	pGround->SetPos(Vec2(640.f, 584.f));
	pGround->SetScale(Vec2(800.f, 100.f));
	AddObject(pGround, GROUP_TYPE::GROUND);

	// 타일 로딩
	//LoadTile(L"tile\\Start.tile");

	// 충돌 지정 (Player과 Monster 그룹간에는 충돌이 발생한다고 지정)
	// Player 그룹과 Monster 그룹 간의 충돌 체크 - Render 직전 finalupdate 이후 가장 마지막에 로직
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::PROJ_MONSTER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PROJ_PLAYER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PLAYER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::GROUND);
	

	// Camera Look 지정
	CCamera::GetInst()->SetLookAt(vResolution / 2.f);	// 해상도 절반 위치를 카메라 중앙으로 설정


	// Camera 효과 지정
	CCamera::GetInst()->FadeOut(1.f);
	CCamera::GetInst()->FadeIn(1.f);

	start();
}

void CScene_Start::Exit()
{
	DeleteAll();

	// 이번 씬에서 지정해뒀던 충돌 그룹을 모두 해제함.
	CCollisionMgr::GetInst()->Reset();
}


