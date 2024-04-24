#pragma once
#include "CObject.h"

class CGround :
    public CObject
{
private:

public:
    virtual void start() override;
    virtual void update() override;
    virtual void render(HDC _dc) override;

public:
    virtual void OnCollisionEnter(CCollider* _pOther) override;
    virtual void OnCollision(CCollider* _pOther) override;
    virtual void OnCollisionExit(CCollider* _pOther) override;

    CLONE(CGround)

public:
    CGround();
    virtual ~CGround() override;
};

