#include "CScene_Tool.h"
#include "CKeyMgr.h"

#include "CCollisionMgr.h"
#include "CSceneMgr.h"
#include "CTile.h"
#include "CCore.h"
#include "CResMgr.h"
#include "CCamera.h"
#include "CUI.h"
#include "CPanelUI.h"
#include "CBtnUI.h"
#include "CUIMgr.h"


CScene_Tool::CScene_Tool()
	: m_pUI(nullptr)
{
	
}

CScene_Tool::~CScene_Tool()
{
}

void ChangeScene(DWORD_PTR, DWORD_PTR)
{
	ChangeScene(SCENE_TYPE::START);
}


void CScene_Tool::Enter()
{
	// Ÿ�� ����
	CreateTile(5,5);

	Vec2 vResolution = CCore::GetInst()->GetResolution();	// ���������

	CUI* pPanelUI = new CPanelUI;
	pPanelUI->SetName(L"ParentUI111");
	pPanelUI->SetScale(Vec2(500.f,300.f));
	pPanelUI->SetPos(Vec2(vResolution.x - pPanelUI->GetScale().x,0.f));

	CBtnUI* pBtnUI = new CBtnUI;
	pBtnUI-> SetName(L"ChildUI111");
	pBtnUI->SetScale(Vec2(100.f, 50.f));
	pBtnUI->SetPos(Vec2(0.f, 0.f));

	// �������� �ֻ��� �θ� UI�� �˰� ����
	pPanelUI->AddChild(pBtnUI);

	AddObject(pPanelUI, GROUP_TYPE::UI);

	
	CUI* pClonePanel = pPanelUI->Clone();
	pClonePanel->SetPos(pClonePanel->GetPos() + Vec2(-250.f, 150.f));
	((CBtnUI*)(pClonePanel->GetUIChild()[0]))->SetClickedCallBack(ChangeScene);

	AddObject(pClonePanel, GROUP_TYPE::UI);

	m_pUI = pClonePanel;
	
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
	SetTileIdx();

	if (KEY_TAP(KEY::LSHIFT))
	{
		CUIMgr::GetInst()->SetFocusedUI(m_pUI);
	}
	
}

void CScene_Tool::SetTileIdx()
{
	if (KEY_TAP(KEY::LBTN))
	{
		Vec2 vMousePos = MOUSE_POS;
		vMousePos = CCamera::GetInst()->GetRealPos(vMousePos);

		int iTileX = (int)GetTileX();
		int iTileY = (int)GetTileY();

		int iCol = (int)vMousePos.x / TILE_SIZE;
		int iRow = (int)vMousePos.y / TILE_SIZE;

		if (vMousePos.x < 0 || iCol >= iTileX 
			|| vMousePos.y < 0 || iRow >= iTileY)
		{
			return;
		}


		UINT iIdx = iCol + iRow * iTileX;

		const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);
		((CTile*)vecTile[iIdx])->AddImgIdx();
	}
	

}



#include "Resource.h"

// ���� �Լ��� ���ν��� ���� (������� Ÿ�� ���� �Է� �޾Ƽ� ���� ��)
// CALLBACK = __stdcall : �Լ� ȣ�� �Ծ�
INT_PTR CALLBACK TileCountProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			UINT iXCount = GetDlgItemInt(hDlg, IDC_EDIT1, nullptr, false);
			UINT iYCount = GetDlgItemInt(hDlg, IDC_EDIT2, nullptr, false);
			
			// �����Լ���! ����Լ� �ƴ� ����1!!
			// ������ Ÿ���� ����.
			CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
			CScene_Tool* pToolScene = dynamic_cast<CScene_Tool*>(pCurScene);
			assert(pToolScene);

			pCurScene->DeleteGroup(GROUP_TYPE::TILE);
			pCurScene->CreateTile(iXCount, iYCount);

			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
