#pragma once
#include "CUI.h"

typedef void (*BTN_FUNC) (DWORD_PTR, DWORD_PTR);

class CBtnUI :
    public CUI
{
private:
    // 버튼마다 다른 기능을 구현할 때 자식 클래스로 파생하지 않고 함수포인터를 멤버로 들고 있을 거임.
    BTN_FUNC        m_pFunc;
    DWORD_PTR       m_param1;
    DWORD_PTR       m_param2;

public:
    void MouseOn() override;
    void MouseLbtnDown() override;
    void MouseLbtnUp() override;
    void MouseLbtnClicked() override;

	void SetClickedCallBack(BTN_FUNC _pFunc, DWORD_PTR _param1 = 0, DWORD_PTR _param2 = 0)
    { 
        m_pFunc = _pFunc; 
        m_param1 = _param1;
        m_param2 = _param2;
    }

    CLONE(CBtnUI);

public:
    CBtnUI();
    ~CBtnUI();
};

