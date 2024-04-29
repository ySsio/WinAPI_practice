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
    void Enter() override;  // �������̵��� ����ϱ� ���� virtual �Ǵ� override Ű���� �ۼ�.
    void Exit() override;   // �Ƚᵵ �Ǳ� ��.
    

public:
    void CreateForce();

public:
    CScene_Start();
    ~CScene_Start();
};


