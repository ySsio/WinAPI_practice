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
			// Lbtn Up 체크
			if (KEY_AWAY(KEY::LBTN))
			{
				pUI->m_bLbtnDown = false;
			}
		}
	}
}
