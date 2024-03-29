#include "CScene_Tool.h"
#include "CKeyMgr.h"

#include "CCollisionMgr.h"
#include "CSceneMgr.h"
#include "CTile.h"
#include "CCore.h"
#include "CResMgr.h"
#include "CCamera.h"

CScene_Tool::CScene_Tool()
{
}

CScene_Tool::~CScene_Tool()
{
}


void CScene_Tool::Enter()
{
	// 타일 생성
	CreateTile(5,5);

	Vec2 vResolution = CCore::GetInst()->GetResolution();	// 복사생성자
	// Camera Look 지정
	CCamera::GetInst()->SetLookAt(vResolution / 2.f);	// 해상도 절반 위치를 카메라 중앙으로 설정
	
}

void CScene_Tool::Exit()
{
	DeleteAll();

	// 이번 씬에서 지정해뒀던 충돌 그룹을 모두 해제함.
	CCollisionMgr::GetInst()->Reset();
}

void CScene_Tool::update()
{
	CScene::update();
	SetTileIdx();
	
	
}

void CScene_Tool::SetTileIdx()
{
	if (KEY_TAP(KEY::LBTN))
	{
		Vec2 vMousePos = MOUSE_POS;
		vMousePos = CCamera::GetInst()->GetRealPos(vMousePos);

		UINT iTileX = GetTileX();
		UINT iTileY = GetTileY();

		UINT iCol = (UINT)vMousePos.x / TILE_SIZE;
		UINT iRow = (UINT)vMousePos.y / TILE_SIZE;

		UINT iIdx = iCol + iRow * iTileX;

		const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);
		((CTile*)vecTile[iIdx])->AddImgIdx();
	}
	

}

#include "Resource.h"

// 전역 함수로 프로시저 구현 (윈도우로 타일 개수 입력 받아서 적용 함)
// CALLBACK = __stdcall : 함수 호출 규약
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
			
			// 전역함수야! 멤버함수 아님 주의1!!
			// 기존의 타일을 제거.
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
