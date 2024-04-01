#pragma once
#include "CObject.h"

class CUI :
    public CObject
{
private:
    vector<CUI*>        m_vecChildUI;
    CUI*                m_pParentUI;
    Vec2                m_vFinalPos;

    bool                m_bCamAffected;     // 렌더링과 카메라의 관계유무 (true면 renderpos로 존재하는 것, false면 카메라 렌더링 화면 상에 고정된 위치)
    bool                m_bMouseOn;         // UI 위에 마우스가 있는 지(hover)
    bool                m_bLbtnDown;        // UI에 왼쪽 버튼 down 된 적 있는지

public :
    Vec2 GetFinalPos() { return m_vFinalPos; }
    CUI* GetParent() { return m_pParentUI; }
    bool IsMouseOn() { return m_bMouseOn; }

    void AddChild(CUI* _pUI) { m_vecChildUI.push_back(_pUI); _pUI->m_pParentUI = this; }

public:
    void update() override;
    void finalupdate() override;
    void render(HDC _dc) override;

private:
    void update_child();
    void finalupdate_child();
    void render_child(HDC _dc);

    void MouseOnCheck();

    CLONE(CUI);

public:
    virtual void MouseOn();

    virtual void MouseLbtnDown();
    virtual void MouseLbtnUp();
    virtual void MouseLbtnClicked();    // 같은 버튼에서 down, up이 일어날 때.

public:
    CUI(bool _bCamAff); // 기본 생성자를 없앴으므로 자식 클래스 생성자에서 신경써줘야 함
    virtual ~CUI();

    friend class CUIMgr;
};

