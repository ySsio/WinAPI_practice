#pragma once
#include "CObject.h"

 // # ���� �̰�? ����� ��� �����ϴ°� ���� �����Ƽ�
                // �׳� ������ ���漱�� �Ѱǰ�

class CPlayer :
    public CObject
{

public:
    void CreateMissile();

public :
    void update() override;
    void render(HDC _dc) override;

public:
    CPlayer();
    ~CPlayer();
};

