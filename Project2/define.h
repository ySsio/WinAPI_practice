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