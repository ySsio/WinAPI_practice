#include "global.h"
#include "CUIMgr.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CUI.h"

#include "CKeyMgr.h"


CUIMgr::CUIMgr()
{


}

CUIMgr::~CUIMgr()
{

}

void CUIMgr::update()
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

	const vector<CObject*>& vecUI = pCurScene->GetGroupObject(GROUP_TYPE::UI);

	
	for (auto ui : vecUI)
	{
		// 마우스 체크. 방식이 다름. 카메라 영향 있는 거 vs 없는 거
		CUI* pUI = (CUI*)ui;
		
		pUI = GetTargetedUI(pUI);

		if (pUI == nullptr)
		{
			return;
		}

		pUI->MouseOn();

		if (KEY_TAP(KEY::LBTN))
		{
			pUI->MouseLbtnDown();
			pUI->m_bLbtnDown = true;
		}
		else if (KEY_AWAY(KEY::LBTN))
		{
			pUI->MouseLbtnUp();

			if (pUI->m_bLbtnDown)
			{
				pUI->MouseLbtnClicked();
			}
			pUI->m_bLbtnDown = false;
		}
		
	}
}

CUI* CUIMgr::GetTargetedUI(CUI* _pParentUI)
{
	CUI* pTargetUI = nullptr;

	// level 순회 (BFS)
	// 계속 targetUI를 갱신하다가 가장 마지막으로 나온 targetUI를 리턴
	// 계층 상 가장 하위층의 UI를 리턴해야 하므로..
	
	list<CUI*> queue;
	bool bState = false;	// 반복문 돌면서 좌클릭 떨어졌으면 bLbtnDown을 모두 false로 만들어주는데
							// pTargetUI는 돌아가서 Click 처리를 해줘야 하기 때문에 얘의 상태를 저장해놨다가
							// 나중에 돌려줌.

	queue.push_back(_pParentUI);

	while (!queue.empty())
	{
		CUI* pUI = queue.front();
		queue.pop_front();

		// queue에서 꺼낸 UI가 targetUI인지 확인.
		if (pUI->IsMouseOn())
		{
			pTargetUI = pUI;
			bState = pUI->m_bLbtnDown;
		}

		// Lbtn Up 체크
		if (KEY_AWAY(KEY::LBTN))
		{
			pUI->m_bLbtnDown = false;
		}

		const vector<CUI*>& vecChild = pUI->GetUIChild();

		for (auto child : pUI->GetUIChild())
		{
			queue.push_back(child);
		}

	}

	if (KEY_AWAY(KEY::LBTN) && pTargetUI)
		pTargetUI->m_bLbtnDown = bState;

	return pTargetUI;





	//// 재귀 구현 (내가 함)
	//vector<CUI*> myChild = _pParentUI->GetUIChild();

	//if (myChild.size() == 0)
	//{
	//	_pParentUI->MouseOnCheck();
	//	return _pParentUI->IsMouseOn() ? _pParentUI : nullptr;
	//}
	//	
	//for (auto child : myChild)
	//{
	//	CUI* targetUI = GetTargetedUI(child);
	//	if (targetUI)
	//	{
	//		return targetUI;
	//	}
	//}

	//_pParentUI->MouseOnCheck();
	//return _pParentUI->IsMouseOn() ? _pParentUI : nullptr;
}
