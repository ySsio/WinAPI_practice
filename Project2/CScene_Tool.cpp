#include "CScene_Tool.h"
#include "CKeyMgr.h"

#include "CCollisionMgr.h"
#include "CSceneMgr.h"
#include "CTile.h"
#include "CCore.h"
#include "CResMgr.h"

CScene_Tool::CScene_Tool()
{
}

CScene_Tool::~CScene_Tool()
{
}


void CScene_Tool::Enter()
{
	CTexture* pTileTex = CResMgr::GetInst()->LoadTexture(L"Tile", L"texture\\tile.bmp");

	// Ÿ�� ����
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			CTile* pTile = new CTile;
			pTile->SetPos(Vec2((float)j * TILE_SIZE, (float)i * TILE_SIZE));
			pTile->SetTexture(pTileTex);

			AddObject(pTile, GROUP_TYPE::TILE);
		}
	}
	Vec2 vResolution = CCore::GetInst()->GetResolution();	// ���������
	// Camera Look ����
	CCamera::GetInst()->SetLookAt(vResolution / 2.f);	// �ػ� ���� ��ġ�� ī�޶� �߾����� ����
	
}

void CScene_Tool::Exit()
{
	DeleteAll();

	// �̹� ������ �����ص״� �浹 �׷��� ��� ������.
	CCollisionMgr::GetInst()->Reset();
}

void CScene_Tool::update()
{
	CScene::update();
}
