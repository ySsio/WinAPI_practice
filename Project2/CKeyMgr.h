#pragma once

// KeyMgr => 1. ������ ����ȭ. �� �����ӿ��� �߻��� �ϵ��� ������ Ű �Է¿� ���� �߻��ؾ� �Ѵ�.
//			 2. ������ ���Ƿδ� �����ִ� ���¸� Ȯ���� �� �ִµ�, �����δ� Ű�ٿ�, Ű��, ŰȦ�� ���� ������ �����ؼ� ������ �ʿ伺 ����.



enum class KEY_STATE
{
	TAP,		// �� ���� ���� (KEY DOWN)
	HOLD,		// ������ �ִ�
	AWAY,		// �� �� ���� (KEY UP)
	NONE,		// ��������, ���ݵ� �ȴ����ִ� ����
};

enum class KEY
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	Q,W,E,R,T,Y,U,I,O,P,A,S,D,F,G,Z,X,C,V,B,
	ALT,
	CTRL,
	LSHIFT,
	SPACE,
	ENTER,
	ESC,

	LAST						// �������� �˸��� ��. enum class KEY�� �� �� �ִ� �� �˾Ƴ� �� �ְ� ��.
};

struct tKeyInfo
{
	KEY_STATE	eState;			// Ű�� ���°� (enum : TAP, HOLD, AWAY, NONE)
	bool		bPrevPress;		// ���� �����ӿ� �� Ű�� �����־�����
};

class CKeyMgr
{
	SINGLETON(CKeyMgr);

private:
	vector<tKeyInfo> m_vecKey;	// �� ���Ϳ��� enum class KEY�� ���ǵ� KEY���� ������� ������ ����. ��) 0������ LEFT, 1������ RIGHT, ..

public:
	void init();
	void update();

public:
	KEY_STATE GetKeyState(KEY _eKey)
	{
		return m_vecKey[(int)_eKey].eState;
	};
}; 

