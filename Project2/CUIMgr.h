#pragma once

class CUI;

class CUIMgr
{
	SINGLETON(CUIMgr);

private:

public:
	void update();

private:
	CUI* GetTargetedUI(CUI* _pParentUI);	// �� �ڽ� UI �� ������ target�� UI�� ��ȯ
};

