#include "global.h"
#include "CUIMgr.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CUI.h"

#include "CKeyMgr.h"


CUIMgr::CUIMgr()
	: m_pFocusedUI(nullptr)
{


}

CUIMgr::~CUIMgr()
{

}

void CUIMgr::update()
{
	// 1. FocusedUI 확인 - 내가 이해하기로는 FocusedUI는 활성화된 부모 UI를 의미하고
	// TargetUI는 FocusedUI 중에서도 실제로 타게팅된 UI를 뜻하는 듯.
	// 예를 들면 내가 롤을 하면 롤 화면이 FocusedUI고 내가 상점을 열려고 하면 상점버튼이 TargetUI
	
	m_pFocusedUI = GetFocusedUI();

	if (!m_pFocusedUI)
		return;
	
	// focusedUI에서 실제 targetUI를 받음.
	CUI* pTargetUI = GetTargetedUI(m_pFocusedUI);

	if (!pTargetUI)
		return;

	// targetUI라는 거는 마우스가 올라와있는 거니까 MouseOn 이벤트를 실행
 	pTargetUI->MouseOn();

	// 좌클릭이 눌린 경우 (down)
	if (KEY_TAP(KEY::LBTN))
	{
		// down 이벤트 실행
		pTargetUI->MouseLbtnDown();
		pTargetUI->m_bLbtnDown = true;
	}
	// 좌클릭이 떨어지는 경우 (up)
	else if (KEY_AWAY(KEY::LBTN))
	{
		// up 이벤트 실행
		pTargetUI->MouseLbtnUp();

		// 만약 이전에 down이었으면 click 이벤트도 실행
		if (pTargetUI->m_bLbtnDown)
		{
			pTargetUI->MouseLbtnClicked();
		}
		pTargetUI->m_bLbtnDown = false;
	}
		
}

void CUIMgr::SetFocusedUI(CUI* _pUI)
{
	m_pFocusedUI = _pUI;

	// 이미 포커싱된 애를 또 요청하거나 nullptr을 요청한 경우 (= 전부 해제요청)
	if (_pUI == m_pFocusedUI || _pUI == nullptr)
	{
		return;
	}

	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	vector<CObject*>& vecUI = pCurScene->GetUIGroup();

	vector<CObject*>::iterator iter = vecUI.begin();
	for (; iter != vecUI.end(); ++iter)
	{
		if (*iter == m_pFocusedUI)
		{
			break;
		}
	}

	vecUI.erase(iter);
	vecUI.push_back(m_pFocusedUI);

}

CUI* CUIMgr::GetFocusedUI()
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	vector<CObject*>& vecUI = pCurScene->GetUIGroup();
	
	CUI* pFocusedUI = m_pFocusedUI;

	if (!(KEY_TAP(KEY::LBTN)))
	{
		return pFocusedUI;
	}

	// 왼쪽버튼 down이 발생함.

	vector<CObject*>::iterator targetiter = vecUI.end();
	vector<CObject*>::iterator iter = vecUI.begin();
	for (; iter != vecUI.end() ; ++iter)
	{
		if (((CUI*)*iter)->IsMouseOn())
		{
			targetiter = iter;
		}
	}

	// 아무 UI도 클릭되지 않았다.
	if (targetiter == vecUI.end())
	{
		return nullptr;
	}

	pFocusedUI = (CUI*)*targetiter;

	// 렌더링 그룹 벡터 순서 교체 (포커싱 된 애가 제일 마지막으로 오게)
	vecUI.erase(targetiter);
	vecUI.push_back(pFocusedUI);

	return pFocusedUI;
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

		for (auto child : vecChild)
		{
			queue.push_back(child);
		}

	}


	if (KEY_AWAY(KEY::LBTN) && pTargetUI)
		pTargetUI->m_bLbtnDown = bState;

	return pTargetUI;



	// 재귀 구현 (내가 함)
	//vector<CUI*> myChild = _pParentUI->GetUIChild();

	//if (myChild.size() == 0)
	//{
	//	if (_pParentUI->IsMouseOn())
	//	{
	//		return _pParentUI;
	//	}

	//	if (KEY_AWAY(KEY::LBTN))
	//	{
	//		_pParentUI->m_bLbtnDown = false;
	//	}
	//	return nullptr;
	//}
	//	
	//for (auto child : myChild)
	//{
	//	CUI* targetUI = GetTargetedUI(child);

	//	if (targetUI)
	//	{
	//		pTargetUI = targetUI;
	//	}

	//	if (KEY_AWAY(KEY::LBTN))
	//	{
	//		_pParentUI->m_bLbtnDown = false;
	//	}
	//}

	//if (pTargetUI) return pTargetUI;

	//return _pParentUI->IsMouseOn() ? _pParentUI : nullptr;
}
