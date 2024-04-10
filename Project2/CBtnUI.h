#pragma once
#include "CUI.h"

#include "CScene.h"
#include "CObject.h"



typedef void (*BTN_FUNC) (DWORD_PTR, DWORD_PTR);

// ����Լ� ������ - ���漱������ x, 
typedef void(CScene::* SCENE_MEMFUNC)(void);    // CScene�� ��ӹ��� Ŭ������ ����Լ��� �����ϴ�.
typedef void(CObject::* OBJECT_MEMFUNC)(void);  // ó�� ������ �� ��� Ŭ������ ��ӹ޴� �ֻ��� Ŭ������ �����δ� �� ����.

class CBtnUI :
    public CUI
{
private:
    // ��ư���� �ٸ� ����� ������ �� �ڽ� Ŭ������ �Ļ����� �ʰ� �Լ������͸� ����� ��� ���� ����.
    BTN_FUNC        m_pFunc;
    DWORD_PTR       m_param1;
    DWORD_PTR       m_param2;

    SCENE_MEMFUNC   m_pSceneFunc;
    CScene*         m_pSceneInst;   // ����Լ��� ȣ���� ��ü

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

    void SetClickedCallBack(CScene* _pScene, SCENE_MEMFUNC _pSceneFunc)
    {
        m_pSceneFunc = _pSceneFunc;
        m_pSceneInst = _pScene;
    }

    CLONE(CBtnUI);

public:
    CBtnUI();
    ~CBtnUI();
};

