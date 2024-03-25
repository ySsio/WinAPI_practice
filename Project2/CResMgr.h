#pragma once

class CTexture;
class CSound;
class CRes;

class CResMgr
{
	SINGLETON(CResMgr);

private:
	map<wstring, CRes*> m_mapTex;

public:
	CTexture* LoadTexture(const wstring& _strKey, const wstring& _strRelativePath);
	CTexture* FindTexture(const wstring& _strKey);
};

