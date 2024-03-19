#pragma once
#include "CObject.h"

class CMissile :
    public CObject
{
private:
    float   m_fTheta; // 미사일 발사 방향 (각)
    float   m_fRotateAngle;
    Vec2    m_vDir;
   

public:
    void SetDir(float _fTheta) { m_fTheta = _fTheta; }
    void SetDir(Vec2 _vDir) { m_vDir = _vDir; }
    

public:
    void update() override;
    void render(HDC _dc) override;

public:
    void OnCollisionEnter(CCollider* _pOther) override;

public:
    CMissile();
    ~CMissile();
};

