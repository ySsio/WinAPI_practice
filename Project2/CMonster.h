#pragma once
#include "CObject.h"


class CMonster :
    public CObject
{
private:
    Vec2    m_vCenterPos;
    float   m_fSpeed;
    float   m_fMaxDistance;
    int     m_iDir;     // 1 (우측), -1(좌측)
    float   m_fAttackFrequency;  // 공격 주기 (미사일발사주기)

public:
    float GetSpeed() { return m_fSpeed; }
    void SetSpeed(float _fSpeed) { m_fSpeed = _fSpeed; }

    void SetCenterPos(Vec2 _vPos) { m_vCenterPos = _vPos; }
    void SetMoveDistance(float _fDist) { m_fMaxDistance = _fDist;  }

public:
    void update() override;

public:
    CMonster();
    ~CMonster();

public:
    void CreateMissile();

};

