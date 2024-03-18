#pragma once

// ��ũ�� ����

// ��ũ�� �Լ�
// �������� ���̸� �̾���.

#define SINGLETON(type)	public:									\
							static type* GetInst()				\
							{									\
								static type mgr;				\
								return &mgr;					\
							}									\
						private:								\
							type();								\
							~type();							\

// �Լ� �� ���������� ���� - ������ ���� ���. ���� 1ȸ�� �����.
// ������ ������ ����ϹǷ� �޸� ���� �Ű� �Ƚᵵ ��. ��� ���� ���� ����.


#define fDT CTimeMgr::GetInst()->GetfDT()
#define DT CTimeMgr::GetInst()->GetDT()

#define KEY_CHECK(key, state) CKeyMgr::GetInst()->GetKeyState(KEY::key) == KEY_STATE::state
#define KEY_HOLD(key) KEY_CHECK(key,HOLD)
#define KEY_TAP(key) KEY_CHECK(key,TAP)
#define KEY_AWAY(key) KEY_CHECK(key,AWAY)
#define KEY_NONE(key) KEY_CHECK(key,NONE)

#define PI 3.1415926535f

// Scene�� �����ϴ� Object�� ����
enum class GROUP_TYPE
{
	DEFAULT,
	PLAYER,
	MISSILE,
	MONSTER,

	END = 32,
};


// Scene�� ����
enum class SCENE_TYPE
{
	TOOL,		// ���� ���� �� �ʿ��� ���� ������ �� �ִ� ��
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