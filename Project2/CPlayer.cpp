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

CPlayer::CPlayer()
	: m_pTex(0)
{
	// Texture �ε��ϱ�
	m_pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\Player.bmp");

	
}

CPlayer::~CPlayer()
{
	
}


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

void CPlayer::render(HDC _dc)
{
	// width/ height�� �翬�� ����ϱ� UINT���µ� ��ǥ�� ���� �� �� �����ϱ� int�� ��ȯ
	int iWidth = (int)m_pTex->Width();
	int iHeight = (int)m_pTex->Height();

	Vec2 vPos = GetPos();

	//BitBlt(_dc
	//	, (int)(vPos.x - (float)iWidth / 2)
	//	, (int)(vPos.y - (float)iHeight / 2)
	//	, iWidth, iHeight
	//	, m_pTex->GetDC()
	//	, 0, 0, SRCCOPY);

	// Ư�� ������ ����ó���ؼ� ������. RGB(255,0,255) = magenta ����
	// ���� �Ǿ����� (Windows.h �ȿ� wingdi.h��) �����κ� ����.
	// library�� �����ؾ� ��. #pragma comment(lib, "Msimg32.lib")
	TransparentBlt(_dc
		, (int)(vPos.x - (float)iWidth / 2)
		, (int)(vPos.y - (float)iHeight / 2)
		, iWidth, iHeight
		, m_pTex->GetDC()
		, 0, 0, iWidth, iHeight
		, RGB(255,0,255));
}


void CPlayer::CreateMissile()
{
	Vec2 vMissilePos = GetPos();
	vMissilePos.y -= GetScale().y / 2.f;

	CMissile* pMissile = new CMissile;
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(20.f, 20.f));
	pMissile->SetDir(Vec2(0.f, -1.f));

	CSceneMgr::GetInst()->GetCurScene()->AddObject(pMissile,GROUP_TYPE::DEFAULT);
}
