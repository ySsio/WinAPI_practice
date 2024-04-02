#pragma once

class CUI;

class CUIMgr
{
	SINGLETON(CUIMgr);

private:

public:
	void update();

private:
	CUI* GetTargetedUI(CUI* _pParentUI);	// 내 자식 UI 중 실제로 target된 UI를 반환
};

