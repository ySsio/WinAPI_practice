#pragma once
#include "CRes.h"

class CTexture :
    public CRes
{
private:
    HDC         m_dc;
    HBITMAP     m_hBit;
    BITMAP      m_bitInfo ;

public:
    void Load(const wstring& _strFilePath);
    void Create(UINT _iWidth, UINT _iHeight);

    UINT Width() { return m_bitInfo.bmWidth; }
    UINT Height() { return m_bitInfo.bmHeight; }

    HDC GetDC() { return m_dc; }

// 리소스 매니저에서만 생성할 수 있도록 막음.
private:
    CTexture();
    virtual ~CTexture();

    friend class CResMgr;   // 전방 선언 안해도 되네

};