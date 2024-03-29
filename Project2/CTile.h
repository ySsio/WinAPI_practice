#pragma once
#include "CObject.h"

class CTexture;

class CTile :
    public CObject
{
private:
    CTexture*   m_pTileTex;
    int         m_iImgIdx; // -1인 경우 참조 안한다.

public:
    void SetTexture(CTexture* _pTex) { m_pTileTex = _pTex; }
    void AddImgIdx() { ++m_iImgIdx; }

private:
    void update() override;
    void render(HDC _dc) override;
    CLONE(CTile);

public:
    CTile();
    ~CTile();

};

