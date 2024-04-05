#pragma once

class CUI;

class CUIMgr
{
	SINGLETON(CUIMgr);

private:
	CUI*	m_pFocusedUI;	// �̺�Ʈ ���� ��Ŀ�̵� UI(�ϳ�)�� ������.

public:
	void update();

	void SetFocusedUI(CUI* _pUI);

private:
	CUI* GetFocusedUI();
	CUI* GetTargetedUI(CUI* _pParentUI);	// �� �ڽ� UI �� ������ target�� UI�� ��ȯ
};

