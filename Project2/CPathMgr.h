#pragma once


class CPathMgr
{
	SINGLETON(CPathMgr);

private:
	wchar_t m_szContentPath[255];	// # wstring���� �ϴ� �Ͱ� �ٸ��� �ϴ� ������?

public:
	void init();
	const wchar_t* GetContentPath() { return m_szContentPath; }

};