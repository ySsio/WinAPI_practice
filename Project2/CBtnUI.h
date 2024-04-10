#pragma once
#include "CUI.h"

#include "CScene.h"
#include "CObject.h"



typedef void (*BTN_FUNC) (DWORD_PTR, DWORD_PTR);

// 멤버함수 포인터 - 전방선언으로 x, 
typedef void(CScene::* SCENE_MEMFUNC)(void);    // CScene을 상속받은 클래스의 멤버함수도 가능하다.
typedef void(CObject::* OBJECT_MEMFUNC)(void);  // 처음 설계할 때 모든 클래스가 상속받는 최상위 클래스를 만들어두는 게 좋다.

class CBtnUI :
    public CUI
{
private:
    // 버튼마다 다른 기능을 구현할 때 자식 클래스로 파생하지 않고 함수포인터를 멤버로 들고 있을 거임.
    BTN_FUNC        m_pFunc;
    DWORD_PTR       m_param1;
    DWORD_PTR       m_param2;

    SCENE_MEMFUNC   m_pSceneFunc;
    CScene*         m_pSceneInst;   // 멤버함수를 호출할 객체

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

