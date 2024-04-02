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
		// ���콺 üũ. ����� �ٸ�. ī�޶� ���� �ִ� �� vs ���� ��
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

	// level ��ȸ (BFS)
	// ��� targetUI�� �����ϴٰ� ���� ���������� ���� targetUI�� ����
	// ���� �� ���� �������� UI�� �����ؾ� �ϹǷ�..
	
	list<CUI*> queue;
	bool bState = false;	// �ݺ��� ���鼭 ��Ŭ�� ���������� bLbtnDown�� ��� false�� ������ִµ�
							// pTargetUI�� ���ư��� Click ó���� ����� �ϱ� ������ ���� ���¸� �����س��ٰ�
							// ���߿� ������.

	queue.push_back(_pParentUI);

	while (!queue.empty())
	{
		CUI* pUI = queue.front();
		queue.pop_front();

		// queue���� ���� UI�� targetUI���� Ȯ��.
		if (pUI->IsMouseOn())
		{
			pTargetUI = pUI;
			bState = pUI->m_bLbtnDown;
		}

		// Lbtn Up üũ
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





	//// ��� ���� (���� ��)
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
