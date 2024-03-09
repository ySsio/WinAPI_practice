#pragma once

// KeyMgr => 1. 프레임 동기화. 한 프레임에서 발생한 일들은 동일한 키 입력에 대해 발생해야 한다.
//			 2. 윈도우 정의로는 눌려있는 상태만 확인할 수 있는데, 실제로는 키다운, 키업, 키홀드 등의 동작을 구분해서 감지할 필요성 존재.



enum class KEY_STATE
{
	TAP,		// 막 누른 시점 (KEY DOWN)
	HOLD,		// 누르고 있는
	AWAY,		// 막 뗀 시점 (KEY UP)
	NONE,		// 예전에도, 지금도 안눌려있는 상태
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

	LAST						// 마지막을 알리는 뜻. enum class KEY에 몇 개 있는 지 알아낼 수 있게 함.
};

struct tKeyInfo
{
	KEY_STATE	eState;			// 키의 상태값 (enum : TAP, HOLD, AWAY, NONE)
	bool		bPrevPress;		// 이전 프레임에 이 키가 눌려있었는지
};

class CKeyMgr
{
	SINGLETON(CKeyMgr);

private:
	vector<tKeyInfo> m_vecKey;	// 이 벡터에서 enum class KEY에 정의된 KEY들을 순서대로 관리할 것임. 예) 0번쨰는 LEFT, 1번쨰는 RIGHT, ..

public:
	void init();
	void update();

public:
	KEY_STATE GetKeyState(KEY _eKey)
	{
		return m_vecKey[(int)_eKey].eState;
	};
}; 

