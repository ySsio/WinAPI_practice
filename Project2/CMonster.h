#pragma once
#include "CObject.h"

struct tMonInfo
{
    float       m_fHP;              // ü��
    float       m_fSpeed;           // �ӵ�
    float       m_fSearchRange;     // target ���� ����
    float       m_fAttackRange;     // ���� ����(��Ÿ�)
    float       m_fAttack;          // ���ݷ�
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
