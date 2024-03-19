#pragma once

struct tEvent
{
	EVENT_TYPE		eEven;
	DWORD_PTR		lParam;	// DWORD_PTR : 플랫폼에 가변적으로 변함. 4byte/8byte
	DWORD_PTR		wParam;
};

class CEventMgr
{
	SINGLETON(CEventMgr);

private:
	vector<tEvent>		m_vecEvent;
	vector<CObject*>	m_vecDead;

public:
	void update();

private:
	void Execute(const tEvent& _eve);

public:
	void AddEvent(const tEvent& _eve); 
};

// 문제 생길 여지 있는 이벤트들
// 삭제
// 씬 변경

// 한 업데이트에 일어나는 일들은 모두 동시간 대에 일어나는 일이라고 생각
// 코드 자체는 순차적으로 돌고 있기 때문에 한 프레임에서 삭제가 일어나면
// 그 코드가 실행되기 전에는 살아있다고 인식하다가 삭제 코드 이후에 작동하는 코드에서는
// 객체가 삭제되었다고 인식하는 문제 발생
// 따라서 event를 frame 단위로 동기화 시켜줘야 함.!!!
// => event frame sync = 지연처리
// 날 죽여주세요 요청 => 지연처리 해서 다음번 프레임에 모두에게 적용
// => 다음 프레임에서는 모두가 객체 삭제를 인지할 수 있음.
// Event Manager. 한 번의 업데이트 동안 발생하는 이벤트 취합
// 그 프레임 모두 실행된 후 이벤트 처리
// 다음 프레임에는 모두 동시에 영향 받음.