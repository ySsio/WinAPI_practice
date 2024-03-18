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
    int         m_iDir;     // 1 (����), -1(����)
    float m_time;
    

public:
    float GetSpeed() { return m_fSpeed; }
    void SetSpeed(float _fSpeed) { m_fSpeed = _fSpeed; }

    void SetCenterPos(Vec2 _vPos) { m_vCenterPos = _vPos; }
    void SetMoveDistance(float _fDist) { m_fMaxDistance = _fDist;  }

	void SetTarget(CObject* _target) { m_target = _target; }

public:
    void update() override;
    void render(HDC _dc) override;

public:
    void CreateMissile();

public:
    void OnCollisionEnter(CCollider* _pOther) override;

public:
    CMonster();
    ~CMonster();

};
