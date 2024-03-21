#include "pch.h"
#include "CResMgr.h"

#include "CPathMgr.h"
#include "CTexture.h"

CResMgr::CResMgr()
{

}

CResMgr::~CResMgr()
{
	Safe_Delete_Map<wstring, CTexture*>(m_mapTex);
}

CTexture* CResMgr::LoadTexture(const wstring& _strKey, const wstring& _strRelativePath)
{
	CTexture* pTex = FindTexture(_strKey);
	if (pTex != nullptr)
		return pTex;

	pTex = new CTexture;

	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	pTex->Load(strFilePath);
	pTex->SetKey(_strKey);
	pTex->SetRelativePath(_strRelativePath);

	m_mapTex.insert(make_pair(_strKey, pTex));

	return pTex;
}

CTexture* CResMgr::FindTexture(const wstring& _strKey)
{
	if (m_mapTex.find(_strKey) != m_mapTex.end())
		return m_mapTex[_strKey];

	return nullptr;
}
