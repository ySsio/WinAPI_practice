#include "CScene_Tool.h"
#include "CKeyMgr.h"
#include "CPathMgr.h"

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
	// 툴 SCENE에서 사용할 메뉴 붙임. 메뉴 추가한만큼 해상도가 달라짐.
	CCore::GetInst()->DockMenu();

	// 타일 생성
	CreateTile(5,5);

	Vec2 vResolution = CCore::GetInst()->GetResolution();	// 복사생성자

	CUI* pPanelUI = new CPanelUI;
	pPanelUI->SetName(L"ParentUI111");
	pPanelUI->SetScale(Vec2(500.f,300.f));
	pPanelUI->SetPos(Vec2(vResolution.x - pPanelUI->GetScale().x,0.f));

	CBtnUI* pBtnUI = new CBtnUI;
	pBtnUI-> SetName(L"ChildUI111");
	pBtnUI->SetScale(Vec2(100.f, 50.f));
	pBtnUI->SetPos(Vec2(0.f, 0.f));
	pBtnUI->SetClickedCallBack(this, (SCENE_MEMFUNC) & CScene_Tool::SaveTileData);

	// 씬에서는 최상위 부모 UI만 알고 있음
	pPanelUI->AddChild(pBtnUI);

	AddObject(pPanelUI, GROUP_TYPE::UI);

	
	//CUI* pClonePanel = pPanelUI->Clone();
	//pClonePanel->SetPos(pClonePanel->GetPos() + Vec2(-250.f, 150.f));
	//((CBtnUI*)(pClonePanel->GetUIChild()[0]))->SetClickedCallBack(ChangeScene);
	//AddObject(pClonePanel, GROUP_TYPE::UI);

	//m_pUI = pClonePanel;
	
	// Camera Look 지정
	CCamera::GetInst()->SetLookAt(vResolution / 2.f);	// 해상도 절반 위치를 카메라 중앙으로 설정
	
}

void CScene_Tool::Exit()
{
	// 메뉴제거
	CCore::GetInst()->SeparateMenu();

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

void CScene_Tool::SaveTileData()
{
	OPENFILENAME ofn = {};

	wchar_t szName[256] = {};

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = CCore::GetInst()->GetMainHwnd();	// 이 윈도우를 띄울 부모 윈도우
	ofn.lpstrFile = szName;		// 완성된 경로가 채워질 곳
	ofn.nMaxFile = sizeof(szName);	// 2byte 문자열이므로 512byte
	ofn.lpstrFilter = L"ALL\0*.*\0Tile\0*.tile";	// 필터가 목록으로 뜨고, 선택한 필터 확장자 파일만 보임. 필터이름\0필터형식(이름.확장자)
	ofn.nFilterIndex = 0;	// 위에서 설정한 필터의 몇 번쨰를 사용할 건지 인덱스
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;

	wstring strTileFolder = CPathMgr::GetInst()->GetContentPath();
	strTileFolder += L"tile";

	ofn.lpstrInitialDir = strTileFolder.c_str();	// 초기 경로
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	
	// 세이브 윈도우(dialog, 모달 방식) 여는 함수
	// 저장 눌렀으면 true, 취소 눌렀으면 false가 반환됨.
	if (GetSaveFileNameW(&ofn))
	{
		SaveTile(szName);
	}


}

void CScene_Tool::SaveTile(const wstring& _strFilePath)
{
	// C++ file open
	FILE* pFile = nullptr;	// FILE 자료형 : 주소값 하나 들고 있음, 커널 오브젝트

	// 이중 포인터 = 포인터 변수의 포인터. 포인터 변수 값에 접근하는 것?
	// 파일 포인터 주소 , 파일 절대 경로, 모드 (w, r)
	// 읽기모드의 파일이 존재하지 않으면 파일 열기 실패.
	// 쓰기모드의 파일이 이미 존재하면 "덮어씀". 물론 이어쓰는 옵션도 존재.
	// 쓰기 모드로 없는 파일을 열면 파일을 생성함!! 개꿀!
	// binary라는 의미로 b를 붙여서 wb. 
	// 만약 b를 안붙이면 기본적으로 "문자"데이터로 인식함.
	// 예를 들어 3을 저장하면 ASCII 코드 상 3으로 인식하는 것.
	// 사실상 아무런 상관이 없을 것 같지만, 문제는 ASCII 코드표 중, 27 = ESC
	// 27 읽으면 종료라고 생각하고 파일이 닫힘.
	
	_wfopen_s(&pFile, _strFilePath.c_str(), L"wb");  // 2byte open?? input : 이중 포인터 .. 포인터 주소 넘김
	assert(pFile);

	// 데이터 저장
	UINT xCount = GetTileX();
	UINT yCount = GetTileY();

	fwrite(&xCount, sizeof(UINT), 1, pFile);	// void 포인터와 데이터 사이즈를 받아서 범용적으로 데이터 저장하는 함수
	fwrite(&yCount, sizeof(UINT), 1, pFile);

	// 모든 타일들을 개별적으로 저장함. 순서대로 쓰고, 나중에 읽을 때도 그 순서대로 읽으면 되는 듯.
	const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);

	for (size_t i = 0; i < vecTile.size(); ++i)
	{
		((CTile*)vecTile[i])->Save(pFile);
	}


	// 파일 닫기 (file stream 종료?)
	fclose(pFile);

}

void CScene_Tool::LoadTileData()
{
	OPENFILENAME ofn = {};

	wchar_t szName[256] = {};

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = CCore::GetInst()->GetMainHwnd();	// 이 윈도우를 띄울 부모 윈도우
	ofn.lpstrFile = szName;		// 완성된 경로가 채워질 곳
	ofn.nMaxFile = sizeof(szName);	// 2byte 문자열이므로 512byte
	ofn.lpstrFilter = L"ALL\0*.*\0Tile\0*.tile";	// 필터가 목록으로 뜨고, 선택한 필터 확장자 파일만 보임. 필터이름\0필터형식(이름.확장자)
	ofn.nFilterIndex = 0;	// 위에서 설정한 필터의 몇 번쨰를 사용할 건지 인덱스
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;

	wstring strTileFolder = CPathMgr::GetInst()->GetContentPath();
	strTileFolder += L"tile";

	ofn.lpstrInitialDir = strTileFolder.c_str();	// 초기 경로
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	// 세이브 윈도우(dialog, 모달 방식) 여는 함수
	// 저장 눌렀으면 true, 취소 눌렀으면 false가 반환됨.
	if (GetOpenFileNameW(&ofn))
	{
		wstring strRelativePath = CPathMgr::GetInst()->GetRelativePath(szName);
		LoadTile(strRelativePath);
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
