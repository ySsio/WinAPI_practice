#pragma once
#include "CObject.h"


class CMonster :
    public CObject
{
private:
    Vec2    m_vCenterPos;
    float   m_fSpeed;
    float   m_fMaxDistance;
    int     m_iDir;     // 1 (����), -1(����)
    float   m_fAttackFrequency;  // ���� �ֱ� (�̻��Ϲ߻��ֱ�)

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

