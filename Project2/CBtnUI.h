#pragma once
#include "CUI.h"
class CBtnUI :
    public CUI
{
private:

public:
    void MouseOn() override;
    void MouseLbtnDown() override;
    void MouseLbtnUp() override;

    CLONE(CBtnUI);

public:
    CBtnUI();
    ~CBtnUI();
};

