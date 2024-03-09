#pragma once


class CTimeMgr
{
	SINGLETON(CTimeMgr);
private:
	LARGE_INTEGER	m_llPrevCount;
	LARGE_INTEGER	m_llCurCount;
	LARGE_INTEGER	m_llFrequency;
	
	
	double			m_dDeltaTime;	// 프레임당 시간 (1/FPS) Delta Time
	double			m_dAcc;			// 누적된 시간 (초) - 1초 체크용
	UINT			m_iCallCount;	// 호출 횟수 (update) = 프레임 수 - 1초 동안 몇번 호출 됐는지 세기 위함.
	UINT			m_iFPS;			// 초당 update 호출 횟수 = FPS

public:
	void init();
	void update();

public :
	double GetDT() { return m_dDeltaTime; }
	float GetfDT() { return (float)m_dDeltaTime; }
};

