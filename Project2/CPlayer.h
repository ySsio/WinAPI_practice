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
    int             m_iDir; // ��/�� ���� (-1,1)
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

