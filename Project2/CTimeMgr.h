#pragma once


class CTimeMgr
{
	SINGLETON(CTimeMgr);
private:
	LARGE_INTEGER	m_llPrevCount;
	LARGE_INTEGER	m_llCurCount;
	LARGE_INTEGER	m_llFrequency;
	
	
	double			m_dDeltaTime;	// �����Ӵ� �ð� (1/FPS) Delta Time
	double			m_dAcc;			// ������ �ð� (��) - 1�� üũ��
	UINT			m_iCallCount;	// ȣ�� Ƚ�� (update) = ������ �� - 1�� ���� ��� ȣ�� �ƴ��� ���� ����.
	UINT			m_iFPS;			// �ʴ� update ȣ�� Ƚ�� = FPS

public:
	void init();
	void update();

public :
	double GetDT() { return m_dDeltaTime; }
	float GetfDT() { return (float)m_dDeltaTime; }
};

