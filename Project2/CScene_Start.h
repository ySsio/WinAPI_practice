#pragma once
#include "CScene.h"
class CScene_Start :
    public CScene
{
public:
    void Enter() override;  // �������̵��� ����ϱ� ���� virtual �Ǵ� override Ű���� �ۼ�.
    void Exit() override;   // �Ƚᵵ �Ǳ� ��.
    void update() override;

public:
    CScene_Start();
    ~CScene_Start();
};


