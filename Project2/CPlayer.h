#pragma once
#include "CObject.h"

class CTexture; // # ���� �̰�? ����� ��� �����ϴ°� ���� �����Ƽ�
                // �׳� ������ ���漱�� �Ѱǰ�

class CPlayer :
    public CObject
{
private:
    CTexture*   m_pTex;

public:
    void CreateMissile();

public :
    void update() override;
    void render(HDC _dc) override;

public:
    CPlayer();
    ~CPlayer();
};

