#pragma once


class CPathMgr
{
	SINGLETON(CPathMgr);

private:
	wchar_t m_szContentPath[255];	// # wstring으로 하는 것과 다르게 하는 이유는?

public:
	void init();
	const wchar_t* GetContentPath() { return m_szContentPath; }

};