#pragma once
#include "CObject.h"

 // # ���� �̰�? ����� ��� �����ϴ°� ���� �����Ƽ�
                // �׳� ������ ���漱�� �Ѱǰ�

class CPlayer :
    public CObject
{

public:
    void CreateMissile();

    CLONE(CPlayer)
    //CPlayer* Clone() override { return new CPlayer(*this); }
    // # �ƴ� �ٵ� �̰� CObject* Clone()�� ���������Լ����µ� ����Ÿ���� �ٸ��� �̰͵� �������̵���? ���� �ȵǳ� �̰�
    // # ���� �ϴ� ���� Ÿ���� CObject ��ӹ��� Ŭ������ �����͸� �Ǵµ�..

public :
    void update() override;
    void render(HDC _dc) override;

public:
    CPlayer();
    //CPlayer(const CPlayer& _origin)
    //    : CObject(_origin)
    //{}
    ~CPlayer();
};

