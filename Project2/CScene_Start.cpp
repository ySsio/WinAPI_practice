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
	//CScene::update(); // �θ��� ��� �״�� ��Ȱ���ϱ� ���� ȣ��.
	if (KEY_TAP(KEY::ENTER))
	{
		ChangeScene(SCENE_TYPE::TOOL);	// func.cpp�� ������ �����Լ�
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
			// ���� ������ ������Ʈ�� update ����
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






	// �� ������ �츱�� �޾ƿ���
	CSceneMgr::GetInst()->LoadObject();
	//CSceneMgr::GetInst()->ClearObject();
	
	// CObject �����ͷ� CPlayer ��ü ����
	
	CObject* pObj = new CPlayer;
	pObj->SetName(L"Player");
	pObj->SetPos(Vec2(640.f, 384.f));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);
	SaveObject(pObj, GROUP_TYPE::PLAYER);

	RegisterPlayer(pObj);

	//CObject* pOtherPlayer = pObj->Clone();	// CPlayer�� �ٿ�ĳ���� �ؾ� CPlayer�� ��������� ȣ�� ����
	//pOtherPlayer->SetPos(Vec2(740.f, 384.f));
	//AddObject(pOtherPlayer, GROUP_TYPE::PLAYER);

	//CCamera::GetInst()->SetTarget(pObj);

	// Monster Object �߰�
	
	int iMonCount = 1;
	float fMoveDist = 25.f;
	float fObjScale = 50.f;

	Vec2 vResolution = CCore::GetInst()->GetResolution();	// ���������
	CMonster * pMonsterObj = CMonFactory::CreatMonster(MON_TYPE::NORMAL,vResolution/2.f - Vec2(0.f,300.f));
	AddObject(pMonsterObj,GROUP_TYPE::MONSTER);

	// Ground Object �߰�
	CGround* pGround = new CGround;
	pGround->SetName(L"Ground");
	pGround->SetPos(Vec2(640.f, 584.f));
	pGround->SetScale(Vec2(800.f, 100.f));
	AddObject(pGround, GROUP_TYPE::GROUND);

	// Ÿ�� �ε�
	//LoadTile(L"tile\\Start.tile");

	// �浹 ���� (Player�� Monster �׷찣���� �浹�� �߻��Ѵٰ� ����)
	// Player �׷�� Monster �׷� ���� �浹 üũ - Render ���� finalupdate ���� ���� �������� ����
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::PROJ_MONSTER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PROJ_PLAYER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PLAYER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::GROUND);
	

	// Camera Look ����
	CCamera::GetInst()->SetLookAt(vResolution / 2.f);	// �ػ� ���� ��ġ�� ī�޶� �߾����� ����


	// Camera ȿ�� ����
	CCamera::GetInst()->FadeOut(1.f);
	CCamera::GetInst()->FadeIn(1.f);

	start();
}

void CScene_Start::Exit()
{
	DeleteAll();

	// �̹� ������ �����ص״� �浹 �׷��� ��� ������.
	CCollisionMgr::GetInst()->Reset();
}


