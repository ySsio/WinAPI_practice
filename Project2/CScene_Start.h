#pragma once
#include "CScene.h"
class CScene_Start :
    public CScene
{
public:
    void Enter() override;  // 오버라이딩을 명시하기 위해 virtual 또는 override 키워드 작성.
    void Exit() override;   // 안써도 되긴 함.
    void update() override;

public:
    CScene_Start();
    ~CScene_Start();
};


