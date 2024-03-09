#include "pch.h"
#include "CKeyMgr.h"
#include "CCore.h"

// 가상 키값을 enum class KEY의 순서에 맞게 저장해놓은 배열
int g_arrVK[(int)KEY::LAST] =
{
	VK_LEFT,
	VK_RIGHT,
	VK_UP,
	VK_DOWN,
	'Q',
	'W',
	'E',
	'R',
	'T',
	'Y',
	'U',
	'I',
	'O',
	'P',
	'A',
	'S',
	'D',
	'F',
	'G',
	'Z',
	'X',
	'C',
	'V',
	'B',
	VK_MENU,		// alt
	VK_CONTROL,		// ctrl
	VK_LSHIFT,
	VK_SPACE,
	VK_RETURN,		// enter
	VK_ESCAPE,		// esc

	//LAST						
};

// KeyMgr => 1. 프레임 동기화. 한 프레임에서 발생한 일들은 동일한 키 입력에 대해 발생해야 한다.
//			 2. 윈도우 정의로는 눌려있는 상태만 확인할 수 있는데, 실제로는 키다운, 키업, 키홀드 등의 동작을 구분해서 감지할 필요성 존재.

CKeyMgr::CKeyMgr()
{

}

CKeyMgr::~CKeyMgr()
{

}

void CKeyMgr::init()
{
	for (int i = 0; i < (int)KEY::LAST; ++i)
	{
		m_vecKey.push_back(tKeyInfo{ KEY_STATE::NONE, false });
	}
}
void CKeyMgr::update()
{
	// 윈도우 포커싱 알아내기
	//HWND hMainWnd = CCore::GetInst()->GetMainHwnd();

	HWND hWnd = GetFocus();	// GetFocus() : 현재 포커싱 되어있는 윈도우 핸들값 알려주는 함수. 포커싱 된거 없으면 0 (nullptr) 반환


	//if (hMainWnd != hWnd)
	//	return;

	// 윈도우 포커싱 해제상태
	if (hWnd == nullptr)
	{
		// 키 눌린채로 포커싱 해제되면 키 떼는 처리를 해줘야함. 안 그러면 동꼽상태 유지됨. 아래 부분 주석처리하면 실제로 동꼽됨
		for (int i = 0; i < (int)KEY::LAST; ++i)
		{
			m_vecKey[i].bPrevPress = false;
			// TAP이나 HOLD 상태로 포커싱 없어지면 AWAY로 바꿔주고, AWAY나 NONE 상태였으면 NONE으로 설정. (1프레임만큼 처리하는 거임)
			m_vecKey[i].eState == KEY_STATE::TAP || m_vecKey[i].eState == KEY_STATE::HOLD ? m_vecKey[i].eState = KEY_STATE::AWAY : m_vecKey[i].eState = KEY_STATE::NONE;
		}

		return;
	}
		

	// 윈도우 포커싱 상태
	for (int i = 0; i < (int)KEY::LAST; ++i)
	{
		// 키가 눌렸다면
		if (GetAsyncKeyState(g_arrVK[i]) & 0x8000)
		{
			if (m_vecKey[i].bPrevPress)
			{
				m_vecKey[i].eState = KEY_STATE::HOLD;
			}
			else
			{
				m_vecKey[i].eState = KEY_STATE::TAP;
			}

			// 이번에 눌렸으니 bPrevPress를 true로 전환해둠.
			m_vecKey[i].bPrevPress = true;
			
		}
		else
		{
			if (m_vecKey[i].bPrevPress)
			{
				m_vecKey[i].eState = KEY_STATE::AWAY;
			}
			else
			{
				m_vecKey[i].eState = KEY_STATE::NONE;
			}

			// 이번에 안 눌렸으니 bPrevPress를 false로 전환해둠.
			m_vecKey[i].bPrevPress = false;
		}
		
	}
}
