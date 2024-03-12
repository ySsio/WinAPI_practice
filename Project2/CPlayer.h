#pragma once
#include "CObject.h"

class CTexture; // # 뭐냐 이거? 헤더에 헤더 참조하는게 별로 안좋아서
                // 그냥 별도로 전방선언 한건가

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

