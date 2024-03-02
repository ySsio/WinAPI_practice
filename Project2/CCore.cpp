#include "pch.h"
#include "CCore.h"
#include "CObject.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"

CObject g_obj;

// 구현 1.
// 클래스에서 선언한 정적 멤버는 밖에서 반드시 초기화 해줘야 한다. 안하면 링크에러 남
// CCore* CCore::g_pInst = nullptr;



// 구현 2.
CCore::CCore()
	: m_hWnd(0)
	, m_ptResolution{}
	, m_hDC(0)
{

}

CCore::~CCore()
{
	// DC를 메모리에서 해제.
	ReleaseDC(m_hWnd, m_hDC);
}

int CCore::init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;

	// 해상도에 맞게 윈도우 크기 조정
	// 우리가 원하는 해상도로 사각형 좌표 만듦
	RECT rt = { 0, 0, _ptResolution.x, _ptResolution.y };

	// AdjustWindowRect : 우리가 설정하려는 해상도를 넘겨주면 타이틀, 메뉴바, 테두리 등의 고려사항을 적용해서 SetWindowPos에 넣어야 할 값으로 수정해 줌. (리턴값 x)
	// 보통 리턴값이 너무 크면 (레지스터에 담았다가 메모리에 저장하기 비효율적인 경우) 받은 인자에 다시 결과값을 저장해주는 방식을 채택함.
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);	// 3번째 인자는 메뉴바 고려해야 하는지 여부

	// SetWindowPos : 타이틀 창, 메뉴 바, 윈도우 테두리를 포함한 크기를 조절함
	SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);

	// Device Context 커널 오브젝트 -> 그리기 위해 필요
	// 메세지 방식은 BeginPaint/EndPaint로 DC를 생성하고 release 했는데,
	// 메세지 방식 안사용하면 GetDC로 DC를 강제로 만들고, 그림 다 그리고 나서 release할 필요도 없이 프로그램 종료할 때 해제해주면 됨. (소멸자에 구현)
	m_hDC = GetDC(m_hWnd);



	// Manager 초기화
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();


	g_obj.SetPos(Vec2{ m_ptResolution.x / 2, m_ptResolution.y / 2 });
	g_obj.SetScale(Vec2{ 100, 100 });
	
	return S_OK;
}

#include <iostream>

void CCore::progress()
{
	static int callcount = 0;
	++callcount;

	static int iprevcount = GetTickCount();

	int icurcount = GetTickCount();
	if (icurcount - iprevcount > 1000)
	{
		iprevcount = icurcount;
		callcount = 0;
	}
		


	update();

	render();
	
}

void CCore::update()
{
	// 물체의 변경점을 체크.

	// 비동기 키 입출력 함수
	// 대신 창이 포커싱 되었는지 따질 수 없고 백그라운드에 있어도 항상 수행됨
	// GetAsyncKeyState : 리턴값으로 키가 눌렸는지 뗐는지 이런 상태값을 비트표현으로 주는데, 키 눌린 상태를 확인하려면 0x8000 자리 확인하면 된대. 맨 앞자리?

	// 컴퓨터 처리속도가 너무 빨라서 키 눌렸을 때 픽셀 단위로 조절하면 몇만 픽셀씩 막 움직임 한번에
	// 그렇다고 단순히 실수로 변환해서 관리해도 컴퓨터 성능에 따라 이동이 달라질 수 있음. 
	// => 시간 동기화. 컴퓨터가 아무리 빨리 연산해도 현실 시간과 매칭이 되어야 한다. 한 프레임마다 움직이는 값이 고정 값이면 안 됨.
	// 컴퓨터 속도에 따라 가변적으로 1초를 맞춰야 함. (컴퓨터가 좋으면 업데이트마다 조금 움직이고 안좋으면 업데이트마다 많이 움직이게)

	Vec2 vPos = g_obj.GetPos();
	
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		vPos.x -= 0.01f;
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		vPos.x += 0.01f;
	if (GetAsyncKeyState(VK_UP) & 0x8000)
		vPos.y -= 0.01f;
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		vPos.y += 0.01f;

	g_obj.SetPos(vPos);

}

void CCore::render()
{
	Vec2 vPos = g_obj.GetPos();
	Vec2 vScale = g_obj.GetScale();

	// 그리기
	Rectangle (m_hDC
		, vPos.x - vScale.x / 2
		, vPos.y - vScale.y / 2
		, vPos.x + vScale.x / 2
		, vPos.y + vScale.y / 2 );
}
