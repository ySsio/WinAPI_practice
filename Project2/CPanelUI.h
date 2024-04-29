#pragma once
#include "CUI.h"
class CPanelUI :
    public CUI
{
private:
    Vec2    m_vDragStart;

public:
    void update() override;
    void render(HDC _dc) override;

    void MouseOn() override;
    void MouseLbtnDown() override;
    void MouseLbtnUp() override;

    CLONE(CPanelUI);

public:
    CPanelUI();
    ~CPanelUI();
};

