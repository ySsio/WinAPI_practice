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
		if (pUI->IsMouseOn())
		{
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
		else
		{
			// Lbtn Up üũ
			if (KEY_AWAY(KEY::LBTN))
			{
				pUI->m_bLbtnDown = false;
			}
		}
	}
}
