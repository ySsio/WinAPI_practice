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
	// 실행된 위치가 현재 경로. (exe파일)
	// vs로 실행하는 경우 프로젝트 경로가 반환됨 .. 어떡하지?
	// 작업디렉토리 설정
	GetCurrentDirectory(255, m_szContentPath);	
	//SetWindowText(CCore::GetInst()->GetMainHwnd(), m_szContentPath);

	// 상위폴더\bin\content\
	// # 이거 나중에 배포할 때도 그대로 두냐?
	
	// system 쪽 라이브러리 참조해서 상위폴더 함수 사용할 수 있지만 문자열로 다뤄보겠다
	// 맨 뒤부터 차례대로 보다가 \\가 나오면 걔를 \0 널문자로 변경. 그 뒤를 다 제거할 필요 없음.
	int iLen = (int)wcslen(m_szContentPath);
	for (int i = iLen-1; i >= 0; --i)
	{
		if (m_szContentPath[i] == '\\')
		{
			m_szContentPath[i] = '\0';
			break;
		}
	}

	// \bin\content 붙이기
	wcscat_s(m_szContentPath, 255, L"\\bin\\content\\");

}
