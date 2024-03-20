#pragma once
#include "CObject.h"

 // # 뭐냐 이거? 헤더에 헤더 참조하는게 별로 안좋아서
                // 그냥 별도로 전방선언 한건가

class CPlayer :
    public CObject
{

public:
    void CreateMissile();

    CLONE(CPlayer)
    //CPlayer* Clone() override { return new CPlayer(*this); }
    // # 아니 근데 이거 CObject* Clone()이 순수가상함수였는데 리턴타입이 다른데 이것도 오버라이딩임? 이해 안되네 이건
    // # 보아 하니 리턴 타입이 CObject 상속받은 클래스의 포인터면 되는듯..

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

