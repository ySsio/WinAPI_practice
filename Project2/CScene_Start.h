#pragma once
#include "CScene.h"
class CScene_Start :
    public CScene
{
private:
    Vec2    m_vForcePos;
    float   m_fForceRadius;
    float   m_fCurRadius;
    bool    m_bUseForce;
    float   m_fForce;

public:
    void update() override;
    void render(HDC _dc) override;

public:
    void Enter() override;  // 오버라이딩을 명시하기 위해 virtual 또는 override 키워드 작성.
    void Exit() override;   // 안써도 되긴 함.
    

public:
    void CreateForce();

public:
    CScene_Start();
    ~CScene_Start();
};


