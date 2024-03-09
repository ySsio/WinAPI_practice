#pragma once
#include "CObject.h"
class CMissile :
    public CObject
{
private:
    float   m_fTheta; // �̻��� �߻� ���� (��)
    Vec2    m_vDir;
public:
    void SetDir(float _fTheta) { m_fTheta = _fTheta; }
    void SetDir(Vec2 _vDir) { m_vDir = _vDir; }
    

public:
    void update() override;
    void render(HDC _dc) override;

public:
    CMissile();
    ~CMissile();
};

