#include "pch.h"
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
	QueryPerformanceCounter(&m_llPrevCount);		// ī��Ʈ ��
	QueryPerformanceFrequency(&m_llFrequency);		// 1�ʿ� �� �� ī��Ʈ �ϴ� �� -> 10000000��
}

void CTimeMgr::update()
{
	QueryPerformanceCounter(&m_llCurCount);

	// Large Integer�� ���� ���ִ°� quadpart��. ���߿� ����
	// ���� ������ (���� update ȣ��) ���� ī���� - ���� ������ (update) ī���� ���� ���� ��� (1������ �� ī��Ʈ ��)
	// �̰� �ʴ� ī��Ʈ ���� �����ָ� �����Ӵ� �ɸ��� �ð� ��������. (1������ �� ī��Ʈ �� / 1�ʴ� ī��Ʈ �� = 1������ �� �� �� = 1/FPS)
	// update ȣ���� �� �������� ������ main���� peekmessage �ݺ��� �ȿ� CCore progress()�� �����ϴµ�, progress() �ȿ��� CTimeMgr �̱��� ��ü�� update()�� ȣ���ϱ� ����
	m_dDeltaTime = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (double)m_llFrequency.QuadPart;
	m_llPrevCount = m_llCurCount;

	render();

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
