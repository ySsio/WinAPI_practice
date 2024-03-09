#include "pch.h"
#include "CKeyMgr.h"
#include "CCore.h"

// ���� Ű���� enum class KEY�� ������ �°� �����س��� �迭
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

// KeyMgr => 1. ������ ����ȭ. �� �����ӿ��� �߻��� �ϵ��� ������ Ű �Է¿� ���� �߻��ؾ� �Ѵ�.
//			 2. ������ ���Ƿδ� �����ִ� ���¸� Ȯ���� �� �ִµ�, �����δ� Ű�ٿ�, Ű��, ŰȦ�� ���� ������ �����ؼ� ������ �ʿ伺 ����.

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
	// ������ ��Ŀ�� �˾Ƴ���
	//HWND hMainWnd = CCore::GetInst()->GetMainHwnd();

	HWND hWnd = GetFocus();	// GetFocus() : ���� ��Ŀ�� �Ǿ��ִ� ������ �ڵ鰪 �˷��ִ� �Լ�. ��Ŀ�� �Ȱ� ������ 0 (nullptr) ��ȯ


	//if (hMainWnd != hWnd)
	//	return;

	// ������ ��Ŀ�� ��������
	if (hWnd == nullptr)
	{
		// Ű ����ä�� ��Ŀ�� �����Ǹ� Ű ���� ó���� �������. �� �׷��� ���Ż��� ������. �Ʒ� �κ� �ּ�ó���ϸ� ������ ���ŵ�
		for (int i = 0; i < (int)KEY::LAST; ++i)
		{
			m_vecKey[i].bPrevPress = false;
			// TAP�̳� HOLD ���·� ��Ŀ�� �������� AWAY�� �ٲ��ְ�, AWAY�� NONE ���¿����� NONE���� ����. (1�����Ӹ�ŭ ó���ϴ� ����)
			m_vecKey[i].eState == KEY_STATE::TAP || m_vecKey[i].eState == KEY_STATE::HOLD ? m_vecKey[i].eState = KEY_STATE::AWAY : m_vecKey[i].eState = KEY_STATE::NONE;
		}

		return;
	}
		

	// ������ ��Ŀ�� ����
	for (int i = 0; i < (int)KEY::LAST; ++i)
	{
		// Ű�� ���ȴٸ�
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

			// �̹��� �������� bPrevPress�� true�� ��ȯ�ص�.
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

			// �̹��� �� �������� bPrevPress�� false�� ��ȯ�ص�.
			m_vecKey[i].bPrevPress = false;
		}
		
	}
}
