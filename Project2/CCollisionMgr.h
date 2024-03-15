#pragma once

class CCollider;

class CCollisionMgr
{
	SINGLETON(CCollisionMgr);

private:
	// �浹ü ���� ���� ������ �浹 ����
	UINT	m_arrCheck[(UINT)GROUP_TYPE::END];	// �׷� ���� �浹 üũ ��Ʈ����

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

