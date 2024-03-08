#pragma once
#include "CObject.h"
class CMissile :
    public CObject
{
private:
    float     m_fDir; // �̻��� �߻� �� �Ʒ� ����

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

