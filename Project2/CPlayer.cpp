#include "CPlayer.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CMissile.h"

#include "CSceneMgr.h"
#include "CScene.h"

#include "CPathMgr.h"
#include "CTexture.h"

#include "CResMgr.h"
#include "CCollider.h"

#include "CEventMgr.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CRigidBody.h"

CPlayer::CPlayer()
	: m_iDir(1)
	, m_iPrevDir(1)
	, m_eCurState(PLAYER_STATE::IDLE)
	, m_ePrevState(PLAYER_STATE::IDLE)
{
	// 이름 설정
	SetName(L"Player");


	// 콜라이더 활성화 (오브젝트 생성)
	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, 5.f));
	GetCollider()->SetScale(Vec2(20.f, 40.f));

	// Texture 로딩하기
	CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"Player", L"texture\\jelda.bmp");


	CreateAnimator();

	GetAnimator()->CreateAnimation(L"IDLE_LEFT", pTex, Vec2(0, 65), Vec2(60, 65), Vec2(60, 0), 0.08f, 3);
	GetAnimator()->CreateAnimation(L"IDLE_RIGHT", pTex, Vec2(0, 195), Vec2(60, 65), Vec2(60, 0), 0.08f, 3);

	GetAnimator()->CreateAnimation(L"WALK_LEFT", pTex, Vec2(0, 325), Vec2(60, 65), Vec2(60, 0), 0.08f, 10);
	GetAnimator()->CreateAnimation(L"WALK_RIGHT", pTex, Vec2(0, 455), Vec2(60, 65), Vec2(60, 0), 0.08f, 10);
	GetAnimator()->Play(L"IDLE_RIGHT", true);

	// Rigidbody 활성화
	CreateRigidBody();
	


}

CPlayer::~CPlayer()
{
	
}


void CPlayer::update()
{
	update_move();

	update_state();

	update_animation();

	update_gravity();

	
	if (KEY_TAP(KEY::SPACE))
	{
		CreateMissile();
	}

	
	GetAnimator()->update();

	m_ePrevState = m_eCurState;
	m_iPrevDir = m_iDir;
}

void CPlayer::render(HDC _dc)
{
	// width/ height은 당연히 양수니까 UINT였는데 좌표는 음수 될 수 있으니까 int로 변환
	//int iWidth = (int)GetTexture()->Width();
	//int iHeight = (int)GetTexture()->Height();

	//Vec2 vPos = GetPos();

	//BitBlt(_dc
	//	, (int)(vPos.x - (float)iWidth / 2)
	//	, (int)(vPos.y - (float)iHeight / 2)
	//	, iWidth, iHeight
	//	, m_pTex->GetDC()
	//	, 0, 0, SRCCOPY);

	// 특정 조건은 투명처리해서 복사함. RGB(255,0,255) = magenta 색상
	// 선언만 되어있음 (Windows.h 안에 wingdi.h에) 구현부분 없음.
	// library를 참조해야 함. #pragma comment(lib, "Msimg32.lib")
	//TransparentBlt(_dc
	//	, (int)(vPos.x - (float)iWidth / 2)
	//	, (int)(vPos.y - (float)iHeight / 2)
	//	, iWidth, iHeight
	//	, GetTexture()->GetDC()
	//	, 0, 0, iWidth, iHeight
	//	, RGB(255,0,255));

	// 컴포넌트 렌더
	component_render(_dc);
}


void CPlayer::CreateMissile()
{
	Vec2 vMissilePos = GetPos();
	vMissilePos.y -= GetScale().y / 2.f;

	CMissile* pMissile = new CMissile;
	pMissile->SetPos(vMissilePos);
	pMissile->SetName(L"Missile_Player");
	pMissile->SetScale(Vec2(20.f, 20.f));
	pMissile->SetDir(Vec2(0.f, -1.f));

	CreateObject(pMissile, GROUP_TYPE::PROJ_PLAYER);
}

void CPlayer::update_state()
{
	if (KEY_TAP(KEY::A))
	{
		m_iDir = -1;
		m_eCurState = PLAYER_STATE::WALK;
	}
	if (KEY_TAP(KEY::D))
	{
		m_iDir = 1;
		m_eCurState = PLAYER_STATE::WALK;
	}

	if (GetRigidBody()->GetSpeed() == 0.f && KEY_NONE(KEY::D) && KEY_NONE(KEY::A))
	{
		m_eCurState = PLAYER_STATE::IDLE;
	}

}

void CPlayer::update_move()
{
	CRigidBody* pRigid = GetRigidBody();

	if (KEY_HOLD(KEY::A))
	{
		pRigid->AddForce(Vec2(-200.f, 0.f));
	}
	if (KEY_HOLD(KEY::D))
	{
		pRigid->AddForce(Vec2(200.f, 0.f));
	}

	if (KEY_TAP(KEY::W))
	{
		pRigid->AddVelocity(Vec2(0.f, -100.f));
	}
	if (KEY_TAP(KEY::S))
	{
		pRigid->AddVelocity(Vec2(0.f, 100.f));
	}
	if (KEY_TAP(KEY::A))
	{
		pRigid->AddVelocity(Vec2(-100.f, 0.f));
	}
	if (KEY_TAP(KEY::D))
	{
		pRigid->AddVelocity(Vec2(100.f, 0.f));
	}
	pRigid->finalupdate();
}

void CPlayer::update_animation()
{
	if (m_eCurState == m_ePrevState && m_iPrevDir == m_iDir)
		return;

	switch (m_eCurState)
	{
	case PLAYER_STATE::IDLE:
	{
		if (m_iDir == -1)
			GetAnimator()->Play(L"IDLE_LEFT", true);
		else
			GetAnimator()->Play(L"IDLE_RIGHT", true);
	}
		break;
	case PLAYER_STATE::WALK:
	{
		if (m_iDir == -1)
			GetAnimator()->Play(L"WALK_LEFT", true);
		else
			GetAnimator()->Play(L"WALK_RIGHT", true);
	}
		break;
	case PLAYER_STATE::ATTACK:

		break;
	case PLAYER_STATE::DEAD:

		break;
	}
}

void CPlayer::update_gravity()
{
	GetRigidBody()->AddForce(Vec2(0.f, 500.f));
}
