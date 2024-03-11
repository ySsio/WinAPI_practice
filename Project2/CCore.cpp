#include "pch.h"
#include "CCore.h"
#include "CObject.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CPathMgr.h"


// 구현 1.
// 클래스에서 선언한 정적 멤버는 밖에서 반드시 초기화 해줘야 한다. 안하면 링크에러 남
// CCore* CCore::g_pInst = nullptr;



// 구현 2.
CCore::CCore()
	: m_hWnd(0)
	, m_ptResolution{}
	, m_hDC(0)
	, m_hBit(0)
	, m_memDC(0)

{

}

CCore::~CCore()
{
	// DC를 메모리에서 해제.
	ReleaseDC(m_hWnd, m_hDC);

	// 사본 DC를 삭제. 메인 윈도우 DC와 다르게 DeleteDC를 사용해야 한대.
	DeleteDC(m_memDC);
	DeleteObject(m_hBit);
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



	// 이중 버퍼링 용도의 비트맵과 DC 생성
	m_hBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);
	m_memDC = CreateCompatibleDC(m_hDC);

	// 이렇게 각각 만들어줘도 서로 연관 없음. DC를 Bitmap에 연결해줘야 함. => SelectObject() 
	// => 원래 비트맵이 반환됨. DC 생성할 때 기본적으로 목적지가 필요하므로 1비트 짜리 bitmap이 등록되어 있음. 이걸 반환받아서 지워줌.
	HBITMAP hOldBit = (HBITMAP)SelectObject(m_memDC, m_hBit);
	DeleteObject(hOldBit);



	// Manager 초기화
	CPathMgr::GetInst()->init();
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CSceneMgr::GetInst()->init();


	
	return S_OK;
}

#include <iostream>

void CCore::progress()
{
	// Manager update
	CTimeMgr::GetInst()->update();
	CKeyMgr::GetInst()->update();
	CSceneMgr::GetInst()->update();
	
	// =========
	// Rendering
	// =========
	
	// 화면 청소
	Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	CSceneMgr::GetInst()->render(m_memDC);

	// 비트맵에서 윈도울 복사 (BitBlt = Bit-Block transfer).. 프레임 ㅈㄴ드랍됐음..!!
	// 엄청난 반복처리 (단순작업이지만) .. CPU 혹사
	// => 그래픽카드. Direct X는 그래픽카드를 다루는 함수 사용.
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y, m_memDC, 0, 0, SRCCOPY);

	//CTimeMgr::GetInst()->render();
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


	// 이렇게 구현하면 1프레임에 동시에 여러 일들을 작업하는데, 작업 중간에 키 상태가 바뀌어버리면 1프레임 안에서 다른 키에 대한 동작을 수행하는 경우가 발생할 수 있음.
	// KeyMgr => 1. 프레임 동기화. 한 프레임에서 발생한 일들은 동일한 키 입력에 대해 발생해야 한다.
	//			 2. 윈도우 정의로는 눌려있는 상태만 확인할 수 있는데, 실제로는 키다운, 키업, 키홀드 등의 동작을 구분해서 감지할 필요성 존재.
	//if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	//	vPos.x -= 400.f * fDT;
	// # 근데 찾아 보니까 0, 0x8000, 1, 0x8001로 NONE, TAP, AWAY, HOLD 처럼 구분하는거 같은데 아닌가?

}

void CCore::render()
{
	
	
}
