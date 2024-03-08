#pragma once
#include "CObject.h"
class CMissile :
    public CObject
{
private:
    float   m_fDir; // 미사일 발사 위 아래 방향
    Vec2    m_vCenterPos;
    float   m_fDist;
    float   m_fSpeed;
    int     i_Dir;

public:
    void SetDir(bool _bUp)
    {
        if (_bUp)
            m_fDir = -1.f;
        else
            m_fDir = 1.f;
    }

    void SetCenter(Vec2 _pos) { m_vCenterPos = _pos; }
    

public:
    void update() override;
    void render(HDC _dc) override;

public:
    CMissile();
    ~CMissile();
};

