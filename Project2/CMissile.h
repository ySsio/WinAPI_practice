#pragma once
#include "CObject.h"
class CMissile :
    public CObject
{
private:
    float     m_fDir; // 미사일 발사 위 아래 방향

public:
    void SetDir(bool _bUp)
    {
        if (_bUp)
            m_fDir = -1.f;
        else
            m_fDir = 1.f;
    }

    

public:
    void update() override;
    void render(HDC _dc) override;

public:
    CMissile();
    ~CMissile();
};

