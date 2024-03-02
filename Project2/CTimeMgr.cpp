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
	QueryPerformanceCounter(&m_llCurCount);		// 카운트 수
	QueryPerformanceFrequency(&m_llFrequency);	// 1초에 몇 번 카운트 하는 지 -> 10000000번
}
