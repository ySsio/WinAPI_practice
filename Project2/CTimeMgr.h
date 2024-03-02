#pragma once


class CTimeMgr
{
	SINGLETON(CTimeMgr);
private:
	LARGE_INTEGER	m_llCurCount;
	LARGE_INTEGER	m_llFrequency;
	// FPS
	
	// 프레임당 시간 (1/FPS) Delta Time

public:
	void init();
	
};

