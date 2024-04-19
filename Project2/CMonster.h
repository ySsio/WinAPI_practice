#pragma once
#include "CObject.h"

struct tMonInfo
{
    float       m_fHP;              // 체력
    float       m_fSpeed;           // 속도
    float       m_fSearchRange;     // target 인지 범위
    float       m_fAttackRange;     // 공격 범위(사거리)
    float       m_fAttack;          // 공격력
};

class AI;

class CMonster :
    public CObject
{
private:
    tMonInfo    m_tInfo;
    AI*         m_pAI;

public:
    float GetSpeed() { return m_tInfo.m_fSpeed; }
    void SetSpeed(float _fSpeed) { m_tInfo.m_fSpeed = _fSpeed; }
    void SetAI(AI* _AI);
    const tMonInfo& GetInfo() { return m_tInfo; }

private:
	void SetMonInfo(const tMonInfo& _info) { m_tInfo = _info; }

public:
    void update() override;
    void render(HDC _dc) override;

    CLONE(CMonster)

public:
    void CreateMissile();

public:
    void OnCollisionEnter(CCollider* _pOther) override;

public:
    CMonster();
    ~CMonster();

    friend class CMonFactory;

};
