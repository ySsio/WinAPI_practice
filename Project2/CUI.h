#pragma once
#include "CObject.h"

class CUI :
    public CObject
{
private:
    vector<CUI*>        m_vecChildUI;
    CUI*                m_pParentUI;
    Vec2                m_vFinalPos;

    bool                m_bCamAffected;     // �������� ī�޶��� �������� (true�� renderpos�� �����ϴ� ��, false�� ī�޶� ������ ȭ�� �� ������ ��ġ)
    bool                m_bMouseOn;         // UI ���� ���콺�� �ִ� ��(hover)
    bool                m_bLbtnDown;        // UI�� ���� ��ư down �� �� �ִ���

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
    virtual void MouseLbtnClicked();    // ���� ��ư���� down, up�� �Ͼ ��.

public:
    CUI(bool _bCamAff); // �⺻ �����ڸ� �������Ƿ� �ڽ� Ŭ���� �����ڿ��� �Ű����� ��
    virtual ~CUI();

    friend class CUIMgr;
};

