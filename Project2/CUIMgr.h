#pragma once

class CUI;

class CUIMgr
{
	SINGLETON(CUIMgr);

private:
	CUI*	m_pFocusedUI;	// 이벤트 받을 포커싱된 UI(하나)를 관리함.

public:
	void update();

	void SetFocusedUI(CUI* _pUI);

private:
	CUI* GetFocusedUI();
	CUI* GetTargetedUI(CUI* _pParentUI);	// 내 자식 UI 중 실제로 target된 UI를 반환
};

