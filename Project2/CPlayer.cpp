#include "pch.h"
#include "CPlayer.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CMissile.h"

#include "CSceneMgr.h"
#include "CScene.h"


void CPlayer::update()
{
	Vec2 vPos = GetPos();

	if (KEY_HOLD(W))
	{
		vPos.y -= 200.f * fDT;
	}
	if (KEY_HOLD(S))
	{
		vPos.y += 200.f * fDT;
	}
	if (KEY_HOLD(A))
	{
		vPos.x -= 200.f * fDT;
	}
	if (KEY_HOLD(D))
	{
		vPos.x += 200.f * fDT;
	}

	if (KEY_TAP(SPACE))
	{
		CreateMissile();
	}

	SetPos(vPos);
}

void CPlayer::CreateMissile()
{
	Vec2 vMissilePos = GetPos();
	vMissilePos.y -= GetScale().y / 2.f;

	CMissile* pMissile = new CMissile;
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(20.f, 20.f));
	pMissile->SetDir(true);
	pMissile->SetCenter(GetPos());

	CSceneMgr::GetInst()->GetCurScene()->AddObject(pMissile,GROUP_TYPE::DEFAULT);
}
