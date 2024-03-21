#include "pch.h"
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

CPlayer::CPlayer()
{
	// 이름 설정
	SetName(L"Player");


	// 콜라이더 활성화 (오브젝트 생성)
	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, 5.f));
	GetCollider()->SetScale(Vec2(20.f, 40.f));

	// Texture 로딩하기
	SetTexture(CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\jelda.bmp"));

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"PlayerWalk",GetTexture(), Vec2(0, 260), Vec2(60, 65), Vec2(60, 0), 10);
}

CPlayer::~CPlayer()
{
	
}


void CPlayer::update()
{
	Vec2 vPos = GetPos();

	if (KEY_HOLD(KEY::W))
	{
		vPos.y -= 200.f * fDT;
	}
	if (KEY_HOLD(KEY::S))
	{
		vPos.y += 200.f * fDT;
	}
	if (KEY_HOLD(KEY::A))
	{
		vPos.x -= 200.f * fDT;
	}
	if (KEY_HOLD(KEY::D))
	{
		vPos.x += 200.f * fDT;
	}

	if (KEY_TAP(KEY::SPACE))
	{
		CreateMissile();
	}

	SetPos(vPos);

}

void CPlayer::render(HDC _dc)
{
	// width/ height은 당연히 양수니까 UINT였는데 좌표는 음수 될 수 있으니까 int로 변환
	int iWidth = (int)GetTexture()->Width();
	int iHeight = (int)GetTexture()->Height();

	Vec2 vPos = GetPos();

	//BitBlt(_dc
	//	, (int)(vPos.x - (float)iWidth / 2)
	//	, (int)(vPos.y - (float)iHeight / 2)
	//	, iWidth, iHeight
	//	, m_pTex->GetDC()
	//	, 0, 0, SRCCOPY);

	// 특정 조건은 투명처리해서 복사함. RGB(255,0,255) = magenta 색상
	// 선언만 되어있음 (Windows.h 안에 wingdi.h에) 구현부분 없음.
	// library를 참조해야 함. #pragma comment(lib, "Msimg32.lib")
	TransparentBlt(_dc
		, (int)(vPos.x - (float)iWidth / 2)
		, (int)(vPos.y - (float)iHeight / 2)
		, iWidth, iHeight
		, GetTexture()->GetDC()
		, 0, 0, iWidth, iHeight
		, RGB(255,0,255));

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
