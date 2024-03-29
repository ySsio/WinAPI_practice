#include "global.h"
#include "framework.h"
#include "CTimeMgr.h"
#include "CCore.h"


CTimeMgr::CTimeMgr()
	: m_llPrevCount{}
	, m_llCurCount{}
	, m_llFrequency{}
	, m_dDeltaTime(0.)
	, m_dAcc(0.)
	, m_iCallCount(0)
	, m_iFPS(0)
{

}

CTimeMgr::~CTimeMgr()
{

}

void CTimeMgr::init()
{
	QueryPerformanceCounter(&m_llPrevCount);		// 카운트 수
	QueryPerformanceFrequency(&m_llFrequency);		// 1초에 몇 번 카운트 하는 지 -> 10000000번
}

void CTimeMgr::update()
{
	QueryPerformanceCounter(&m_llCurCount);

	// Large Integer의 값이 들어가있는게 quadpart래. 나중에 설명
	// 이전 프레임 (이전 update 호출) 때의 카운팅 - 현재 프레임 (update) 카운팅 값의 차이 계산 (1프레임 당 카운트 수)
	// 이걸 초당 카운트 수로 나눠주면 프레임당 걸리는 시간 나오겠지. (1프레임 당 카운트 수 / 1초당 카운트 수 = 1프레임 당 초 수 = 1/FPS)
	// update 호출이 매 프레임인 이유는 main에서 peekmessage 반복문 안에 CCore progress()를 실행하는데, progress() 안에서 CTimeMgr 싱글톤 객체의 update()를 호출하기 때문
	m_dDeltaTime = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (double)m_llFrequency.QuadPart;
	m_llPrevCount = m_llCurCount;


	// 디버그 모드일 때만 포함시키는 전처리기. Release 때는 무시됨.
	// 프로젝트 속성 > C/C++ > 전처리기 > 전처리기 정의
	// deltatime이 1/60초 보다 커지면 다 1/60초로 처리함.
	// 디버그 걸어놔도 실제 시간은 계속 흘러가기 때문에 그 시간과 디버그 끝내고 
	// 다시 진행시킬 때 다음 프레임의 시간을 찾아서 그 차이를 구하면 엄청난 시간이 흘렀을 것.
	// 디버그 걸어놔도 시간이 거의 흐르지 않게 설정함.
#ifdef _DEBUG
	if (m_dDeltaTime > (1. / 60.))
		m_dDeltaTime = 1. / 60.;
#endif

}

void CTimeMgr::render()
{
	++m_iCallCount;
	m_dAcc += m_dDeltaTime;
	if (m_dAcc >= 1.)
	{
		m_iFPS = m_iCallCount;
		m_dAcc = 0.;
		m_iCallCount = 0;

		wchar_t szBuffer[255] = {};
		swprintf_s(szBuffer, L"FPS : %d, DT : %f", m_iFPS, m_dDeltaTime);
		SetWindowText(CCore::GetInst()->GetMainHwnd(), szBuffer);
	}
}
