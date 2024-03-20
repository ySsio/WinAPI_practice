#pragma once
#include "CObject.h"



class CMonster :
    public CObject
{
private:
    Vec2        m_vSpeed;
    Vec2        m_vCenterPos;
    CObject*    m_target;
    float       m_fSpeed;
    float       m_fMaxDistance;
    int         m_iDir;     // 1 (¿ìÃø), -1(ÁÂÃø)
    float m_time;
    
    int         m_iHP;

public:
    float GetSpeed() { return m_fSpeed; }
    void SetSpeed(float _fSpeed) { m_fSpeed = _fSpeed; }

    void SetCenterPos(Vec2 _vPos) { m_vCenterPos = _vPos; }
    void SetMoveDistance(float _fDist) { m_fMaxDistance = _fDist;  }

	void SetTarget(CObject* _target) { m_target = _target; }

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
