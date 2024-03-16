#include "pch.h"
#include "CPathMgr.h"
#include "CCore.h"


CPathMgr::CPathMgr()
	: m_szContentPath{}
{
}

CPathMgr::~CPathMgr()
{
}


void CPathMgr::init()
{
	// ����� ��ġ�� ���� ���. (exe����)
	// vs�� �����ϴ� ��� ������Ʈ ��ΰ� ��ȯ�� .. �����?
	// �۾����丮 ����
	GetCurrentDirectory(255, m_szContentPath);	
	//SetWindowText(CCore::GetInst()->GetMainHwnd(), m_szContentPath);

	// ��������\bin\content\
	// # �̰� ���߿� ������ ���� �״�� �γ�?
	
	// system �� ���̺귯�� �����ؼ� �������� �Լ� ����� �� ������ ���ڿ��� �ٷﺸ�ڴ�
	// �� �ں��� ���ʴ�� ���ٰ� \\�� ������ �¸� \0 �ι��ڷ� ����. �� �ڸ� �� ������ �ʿ� ����.
	int iLen = (int)wcslen(m_szContentPath);
	for (int i = iLen-1; i >= 0; --i)
	{
		if (m_szContentPath[i] == '\\')
		{
			m_szContentPath[i] = '\0';
			break;
		}
	}

	// \bin\content ���̱�
	wcscat_s(m_szContentPath, 255, L"\\bin\\content\\");

}
