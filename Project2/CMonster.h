#pragma once
#include "CObject.h"

class AI;

class CMonster :
    public CObject
{
private:
    float       m_fSpeed;    
    int         m_iHP;
    AI*         m_pAI;

public:
    float GetSpeed() { return m_fSpeed; }
    void SetSpeed(float _fSpeed) { m_fSpeed = _fSpeed; }
    void SetAI(AI* _AI) { m_pAI = _AI; }

public:
    void update() override;
    void render(HDC _dc) override;

    CLONE(CMonster)

public:
    void CreateMissile();

public:
    void OnCollisionEnter(CCollider* _pOther) override;

public:
    CMonster();
    ~CMonster();

};
