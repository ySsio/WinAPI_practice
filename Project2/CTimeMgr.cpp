#include "pch.h"
#include "CTimeMgr.h"


CTimeMgr::CTimeMgr()
	: m_llCurCount{}
	, m_llFrequency{}
{

}

CTimeMgr::~CTimeMgr()
{

}

void CTimeMgr::init()
{
	QueryPerformanceCounter(&m_llCurCount);		// ī��Ʈ ��
	QueryPerformanceFrequency(&m_llFrequency);	// 1�ʿ� �� �� ī��Ʈ �ϴ� �� -> 10000000��
}
