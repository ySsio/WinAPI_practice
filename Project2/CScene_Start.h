#pragma once
#include "CScene.h"
class CScene_Start :
    public CScene
{
public:
    virtual void Enter() override;  // �������̵��� ����ϱ� ���� virtual �Ǵ� override Ű���� �ۼ�.
    virtual void Exit() override;   // �Ƚᵵ �Ǳ� ��.


public:
    CScene_Start();
    ~CScene_Start();
};


