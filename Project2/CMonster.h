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
    CObject* target;

public:
    float GetSpeed() { return m_fSpeed; }
    void SetSpeed(float _fSpeed) { m_fSpeed = _fSpeed; }

    void SetCenterPos(Vec2 _vPos) { m_vCenterPos = _vPos; }
    void SetMoveDistance(float _fDist) { m_fMaxDistance = _fDist;  }

    void SetTarget(CObject* _obj) { target = _obj; }

public:
    void update() override;

public:
    CMonster();
    ~CMonster();

public:
    void CreateMissile();

};

