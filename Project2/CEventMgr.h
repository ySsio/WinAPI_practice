#pragma once

struct tEvent
{
	EVENT_TYPE	aEven;
	DWORD		lParam;
	DWORD		wParam;
};

class CEventMgr
{
	SINGLETON(CEventMgr);

private:
	vector<tEvent>	m_vecEvent;

public:
	void update();
};

