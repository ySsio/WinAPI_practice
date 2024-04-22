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
{
	// �̸� ����
	SetName(L"Player");


	// �ݶ��̴� Ȱ��ȭ (������Ʈ ����)
	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, 5.f));
	GetCollider()->SetScale(Vec2(20.f, 40.f));

	// Texture �ε��ϱ�
	CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\jelda.bmp");

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"WALK_DOWN", pTex, Vec2(0, 260), Vec2(60, 65), Vec2(60, 0), 0.05f, 10);
	GetAnimator()->Play(L"WALK_DOWN",true);

	// Rigidbody Ȱ��ȭ
	CreateRigidBody();

	CAnimation* pAnim = GetAnimator()->FindAnimation(L"WALK_DOWN");
	
	for (int i = 0; i < pAnim->GetMaxFrame(); ++i)
	{
		pAnim->GetFrame(i).vOffset = Vec2(0.f, -20.f);
	}
	


}

CPlayer::~CPlayer()
{
	
}


void CPlayer::update()
{
	// �� ������� ����. position�� �����ͼ� ���� ���������� �ʰ� 
	// �ӵ��� ������Ʈ ���ִ� ������� ����

	CRigidBody* pRigid = GetRigidBody();

	

	if (KEY_HOLD(KEY::W))
	{
		pRigid->AddForce(Vec2(0.f,-200.f));
	}
	if (KEY_HOLD(KEY::S))
	{
		pRigid->AddForce(Vec2(0.f, 200.f));
	}
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

	if (KEY_TAP(KEY::SPACE))
	{
		CreateMissile();
	}

	pRigid->finalupdate();
	GetAnimator()->update(); 
}

void CPlayer::render(HDC _dc)
{
	// width/ height�� �翬�� ����ϱ� UINT���µ� ��ǥ�� ���� �� �� �����ϱ� int�� ��ȯ
	//int iWidth = (int)GetTexture()->Width();
	//int iHeight = (int)GetTexture()->Height();

	//Vec2 vPos = GetPos();

	//BitBlt(_dc
	//	, (int)(vPos.x - (float)iWidth / 2)
	//	, (int)(vPos.y - (float)iHeight / 2)
	//	, iWidth, iHeight
	//	, m_pTex->GetDC()
	//	, 0, 0, SRCCOPY);

	// Ư�� ������ ����ó���ؼ� ������. RGB(255,0,255) = magenta ����
	// ���� �Ǿ����� (Windows.h �ȿ� wingdi.h��) �����κ� ����.
	// library�� �����ؾ� ��. #pragma comment(lib, "Msimg32.lib")
	//TransparentBlt(_dc
	//	, (int)(vPos.x - (float)iWidth / 2)
	//	, (int)(vPos.y - (float)iHeight / 2)
	//	, iWidth, iHeight
	//	, GetTexture()->GetDC()
	//	, 0, 0, iWidth, iHeight
	//	, RGB(255,0,255));

	// ������Ʈ ����
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
