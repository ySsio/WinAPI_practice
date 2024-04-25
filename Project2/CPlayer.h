#pragma once
#include "CObject.h"

enum class PLAYER_STATE
{
    IDLE,
    WALK,
    ATTACK,
    JUMP,
    DEAD,
};

enum class PLAYER_ATTACK_STATE
{
    NORMAL_ATT_1,
    NORMAL_ATT_2,
    NORMAL_ATT_3,
    
    SKILL_ATT_1,

};



class CPlayer :
    public CObject
{
private:
    int             m_iDir; // 좌/우 방향 (-1,1)
    int             m_iPrevDir;
    PLAYER_STATE    m_eCurState;
    PLAYER_STATE    m_ePrevState;

public:
    void CreateMissile();
    void update_state();
    void update_move();
    void update_animation();
    void update_gravity();

    virtual void OnCollisionEnter(CCollider* _pOther);

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

