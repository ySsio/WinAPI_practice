#include "CPlayer.h"
#include "CCore.h"
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
#include "CGravity.h"

#include "CResMgr.h"
#include "CSound.h"

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
	GetCollider()->SetOffsetPos(Vec2(0.f, 20.f));
	GetCollider()->SetScale(Vec2(25.f, 25.f));

	// Texture 로딩하기
	CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"Player", L"texture\\jelda.bmp");


	CreateAnimator();

	// Animation 로드
	GetAnimator()->LoadAnimation(L"animation\\player_idle_left.anim");
	GetAnimator()->LoadAnimation(L"animation\\player_idle_right.anim");
	GetAnimator()->LoadAnimation(L"animation\\player_walk_left.anim");
	GetAnimator()->LoadAnimation(L"animation\\player_walk_right.anim");
	GetAnimator()->LoadAnimation(L"animation\\player_jump_left.anim");
	GetAnimator()->LoadAnimation(L"animation\\player_jump_right.anim");

	//// Animation 생성
	//GetAnimator()->CreateAnimation(L"IDLE_LEFT", pTex, Vec2(0, 65), Vec2(60, 65), Vec2(60, 0), 0.08f, 3);
	//GetAnimator()->CreateAnimation(L"IDLE_RIGHT", pTex, Vec2(0, 195), Vec2(60, 65), Vec2(60, 0), 0.08f, 3);
	//GetAnimator()->CreateAnimation(L"WALK_LEFT", pTex, Vec2(0, 325), Vec2(60, 65), Vec2(60, 0), 0.08f, 10);
	//GetAnimator()->CreateAnimation(L"WALK_RIGHT", pTex, Vec2(0, 455), Vec2(60, 65), Vec2(60, 0), 0.08f, 10);
	//GetAnimator()->CreateAnimation(L"JUMP_LEFT", pTex, Vec2(120, 325), Vec2(60, 65), Vec2(60, 0), 0.08f, 1);
	//GetAnimator()->CreateAnimation(L"JUMP_RIGHT", pTex, Vec2(120, 455), Vec2(60, 65), Vec2(60, 0), 0.08f, 1);
	//
	//// Animation 저장
	//GetAnimator()->FindAnimation(L"IDLE_LEFT")->Save(L"animation\\player_idle_left.anim");
	//GetAnimator()->FindAnimation(L"IDLE_RIGHT")->Save(L"animation\\player_idle_right.anim");
	//GetAnimator()->FindAnimation(L"WALK_LEFT")->Save(L"animation\\player_walk_left.anim");
	//GetAnimator()->FindAnimation(L"WALK_RIGHT")->Save(L"animation\\player_walk_right.anim");
	//GetAnimator()->FindAnimation(L"JUMP_LEFT")->Save(L"animation\\player_jump_left.anim");
	//GetAnimator()->FindAnimation(L"JUMP_RIGHT")->Save(L"animation\\player_jump_right.anim");

	GetAnimator()->Play(L"IDLE_RIGHT", true);

	// Rigidbody 활성화
	CreateRigidBody();
	
	// Gravity 활성화
	CreateGravity();


}

CPlayer::~CPlayer()
{
	
}


void CPlayer::update()
{
	update_move();

	update_state();

	update_animation();

	//update_gravity();

	
	GetAnimator()->update();

	m_ePrevState = m_eCurState;
	m_iPrevDir = m_iDir;
}

void CPlayer::render(HDC _dc)
{
	static double m_dAcc = 0.f;
	static wchar_t szBuffer[255] = {};
	m_dAcc += DT;

	Vec2 m_vAccel = GetRigidBody() -> GetAccel();
	Vec2 m_vVelocity = GetRigidBody()->GetVelocity();
	
	if (m_dAcc >= 0.1)
	{
		m_dAcc = 0.;

		swprintf_s(szBuffer, L"Accel : %13f, %13f, Velocity : %f, %f", m_vAccel.x, m_vAccel.y, m_vVelocity.x, m_vVelocity.y);

	}
	SetWindowText(CCore::GetInst()->GetMainHwnd(), szBuffer);

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
	// WALK
	if (KEY_HOLD(KEY::A))
	{
		m_iDir = -1;
		if (m_eCurState != PLAYER_STATE::JUMP)
			m_eCurState = PLAYER_STATE::WALK;
	}
	if (KEY_HOLD(KEY::D))
	{
		m_iDir = 1;
		if (m_eCurState != PLAYER_STATE::JUMP)
			m_eCurState = PLAYER_STATE::WALK;
	}

	// IDLE
	if (GetRigidBody()->GetSpeed() == 0.f && m_eCurState != PLAYER_STATE::JUMP)
	{
		m_eCurState = PLAYER_STATE::IDLE;
	}

	// JUMP - 땅에 있을 때
	if (KEY_TAP(KEY::SPACE))
	{
		CResMgr::GetInst()->FindSound(L"JUMP")->Play();
		m_eCurState = PLAYER_STATE::JUMP;
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

	if (KEY_TAP(KEY::A))
	{
		Vec2 vVelocity = pRigid->GetVelocity();
		vVelocity.x = -100.f;
		pRigid->SetVelocity(vVelocity);
	}
	if (KEY_TAP(KEY::D))
	{
		Vec2 vVelocity = pRigid->GetVelocity();
		vVelocity.x = 100.f;
		pRigid->SetVelocity(vVelocity);
	}

	if (KEY_TAP(KEY::SPACE))
	{
		Vec2 vVelocity = pRigid->GetVelocity();
		vVelocity.y = -400.f;
		pRigid->SetVelocity(vVelocity);
	}
	
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
	case PLAYER_STATE::JUMP:
	{
		if (m_iDir == -1)
			GetAnimator()->Play(L"JUMP_LEFT", true);
		else
			GetAnimator()->Play(L"JUMP_RIGHT", true);
	}

		break;
	case PLAYER_STATE::DEAD:

		break;
	}
}

void CPlayer::update_gravity()
{
	GetRigidBody()->AddForce(Vec2(0.f, 500.f));
}

void CPlayer::OnCollisionEnter(CCollider* _pOther)
{
	if (_pOther->GetOwner()->GetName() == L"Ground")
	{
		// 내가 ground보다 위에 있을 때
		if (GetPos().y < _pOther->GetOwner()->GetPos().y)
		{
			m_eCurState = PLAYER_STATE::IDLE;
		}
	}
}
