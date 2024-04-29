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
	// 1. FocusedUI Ȯ�� - ���� �����ϱ�δ� FocusedUI�� Ȱ��ȭ�� �θ� UI�� �ǹ��ϰ�
	// TargetUI�� FocusedUI �߿����� ������ Ÿ���õ� UI�� ���ϴ� ��.
	// ���� ��� ���� ���� �ϸ� �� ȭ���� FocusedUI�� ���� ������ ������ �ϸ� ������ư�� TargetUI
	
	m_pFocusedUI = GetFocusedUI();

	if (!m_pFocusedUI)
		return;
	
	// focusedUI���� ���� targetUI�� ����.
	CUI* pTargetUI = GetTargetedUI(m_pFocusedUI);

	if (!pTargetUI)
		return;

	// targetUI��� �Ŵ� ���콺�� �ö���ִ� �Ŵϱ� MouseOn �̺�Ʈ�� ����
 	pTargetUI->MouseOn();

	// ��Ŭ���� ���� ��� (down)
	if (KEY_TAP(KEY::LBTN))
	{
		// down �̺�Ʈ ����
		pTargetUI->MouseLbtnDown();
		pTargetUI->m_bLbtnDown = true;
	}
	// ��Ŭ���� �������� ��� (up)
	else if (KEY_AWAY(KEY::LBTN))
	{
		// up �̺�Ʈ ����
		pTargetUI->MouseLbtnUp();

		// ���� ������ down�̾����� click �̺�Ʈ�� ����
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

	// �̹� ��Ŀ�̵� �ָ� �� ��û�ϰų� nullptr�� ��û�� ��� (= ���� ������û)
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

	// ���ʹ�ư down�� �߻���.

	vector<CObject*>::iterator targetiter = vecUI.end();
	vector<CObject*>::iterator iter = vecUI.begin();
	for (; iter != vecUI.end() ; ++iter)
	{
		if (((CUI*)*iter)->IsMouseOn())
		{
			targetiter = iter;
		}
	}

	// �ƹ� UI�� Ŭ������ �ʾҴ�.
	if (targetiter == vecUI.end())
	{
		return nullptr;
	}

	pFocusedUI = (CUI*)*targetiter;

	// ������ �׷� ���� ���� ��ü (��Ŀ�� �� �ְ� ���� ���������� ����)
	vecUI.erase(targetiter);
	vecUI.push_back(pFocusedUI);

	return pFocusedUI;
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

		for (auto child : vecChild)
		{
			queue.push_back(child);
		}

	}


	if (KEY_AWAY(KEY::LBTN) && pTargetUI)
		pTargetUI->m_bLbtnDown = bState;

	return pTargetUI;



	// ��� ���� (���� ��)
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
