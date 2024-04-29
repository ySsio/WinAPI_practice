#pragma once

class CCollider;

// union : ���� ��� ������ �������� �ؼ��� �޸� �ϴ� ���.
// Test�� 4byte �ڷ���. a�� ���� ����, f�� ���� �Ǽ��� �ؼ�.
//union Test
//{
//	int a;
//	float f;
//};

// 8BYTE, ���� 4byte�� left collider ID, ���� 4byte�� right collider ID
union COLLIDER_ID
{
	struct {
		UINT Left_id;
		UINT Right_id;
	} DUMMYSTRUCTNAME;
	ULONGLONG ID;
};

class CCollisionMgr
{
	SINGLETON(CCollisionMgr);

private:
	map<ULONGLONG, bool> m_mapColInfo;						// �浹ü ���� ���� ������ �浹 ����
	UINT				m_arrCheck[(UINT)GROUP_TYPE::END];	// �׷� ���� �浹 üũ ��Ʈ����

public:
	void init();
	void update();
	// 32���� �׷��� ������ ��Ʈ�� ǥ���� ����. 32bit = 4byte, 32ũ���� �迭�� ���� 4byte�� ��Ʈ ���°� (UINT) ����
	void CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	// �浹 �����ߴ� ��� �׷��� �ʱ�ȭ��. memset�� ������ �ּҸ� ����Ʈ ������ �� �����ϴ� �Լ�.
	void Reset() { memset(m_arrCheck, 0, sizeof(m_arrCheck)); }

private:
	void CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	bool IsCollision(CCollider* _pLeftCol, CCollider* _pRightCol);
};

