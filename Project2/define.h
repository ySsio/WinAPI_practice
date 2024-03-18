#pragma once

// 매크로 정의

// 매크로 함수
// 마지막에 붙이면 이어짐.

#define SINGLETON(type)	public:									\
							static type* GetInst()				\
							{									\
								static type mgr;				\
								return &mgr;					\
							}									\
						private:								\
							type();								\
							~type();							\

// 함수 내 정적변수로 선언 - 데이터 영역 사용. 최초 1회만 실행됨.
// 데이터 영역을 사용하므로 메모리 해제 신경 안써도 됨. 대신 지울 수도 없음.


#define fDT CTimeMgr::GetInst()->GetfDT()
#define DT CTimeMgr::GetInst()->GetDT()

#define KEY_CHECK(key, state) CKeyMgr::GetInst()->GetKeyState(KEY::key) == KEY_STATE::state
#define KEY_HOLD(key) KEY_CHECK(key,HOLD)
#define KEY_TAP(key) KEY_CHECK(key,TAP)
#define KEY_AWAY(key) KEY_CHECK(key,AWAY)
#define KEY_NONE(key) KEY_CHECK(key,NONE)

#define PI 3.1415926535f

// Scene에 존재하는 Object의 종류
enum class GROUP_TYPE
{
	DEFAULT,
	PLAYER,
	MISSILE,
	MONSTER,

	END = 32,
};


// Scene의 종류
enum class SCENE_TYPE
{
	TOOL,		// 게임 만들 때 필요한 것을 조작할 수 있는 씬
	START,

	STAGE_01,
	STAGE_02,

	END,
};

enum class BRUSH_TYPE
{
	HOLLOW,
	END,
};

enum class PEN_TYPE
{
	RED,
	GREEN,
	BLUE,
	END,
};

enum class EVENT_TYPE
{
	CREATE_OBJECT,
	DELETE_OBJECT,
	SCENE_CHANGE,
	END,
};