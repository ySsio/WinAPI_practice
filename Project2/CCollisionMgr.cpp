#include "pch.h"
#include "CCollisionMgr.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CObject.h"

CCollisionMgr::CCollisionMgr()
	: m_arrCheck{}
{

}

CCollisionMgr::~CCollisionMgr()
{
	
}

void CCollisionMgr::init()
{
}

void CCollisionMgr::update()
{
	// �浹 �˻�
	// 1. �浹�ϴ� �׷� üũ
	for (UINT iRow = 0; iRow < (UINT)GROUP_TYPE::END; ++iRow)
	{
		// iCol�� iRow���� �����ϴ� ������ m_arrCheck ǥ�� ��Ī���̶� ������ ������ �˻��� �ʿ䰡 ���� ����.
		for (UINT iCol = iRow; iCol < (UINT)GROUP_TYPE::END; ++iCol)
		{
			if (m_arrCheck[iRow] & (1 << iCol))
			{
				// enum class�� ����ȯ ����
				CollisionGroupUpdate((GROUP_TYPE)iRow, (GROUP_TYPE)iCol);
			}
		}
	}
}

void CCollisionMgr::CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

	// vector<CObject*> Ÿ������ ������ ���������� ��������� ����ȰŶ� ���� ������ �� �ƴ�..!
	// �����ϰ� ���۷��� Ÿ������ �޾���� ��.
	// # �ٵ� �̷��� ���� ������ (���۷��� ���� ������)�� ��� �Ǵ°ų�?? ���۷��� Ÿ���� ���������� ��� �����ϴ°���..
	const vector<CObject*>& vecLeft = pCurScene->GetGroupObject(_eLeft);
	const vector<CObject*>& vecRight = pCurScene->GetGroupObject(_eRight);

	
	for (size_t i = 0; i < vecLeft.size(); i++)
	{
		// �ݶ��̴� ������Ʈ ���� ��ü�� �׳� ���
		if (vecLeft[i]->GetCollider() == nullptr)
			continue;

		for (size_t j = 0; j < vecRight.size(); j++)
		{
			// �ݶ��̴� ������Ʈ ���� ��ü�� �׳� ���
			if (vecRight[j]->GetCollider() == nullptr)
				continue;

			// �ڱ� �ڽŰ� �浹�� �����ؾ� ��.! (����Ű�� ������Ʈ �ּҰ� ����)
			if (vecLeft[i] == vecRight[j])
				continue;

			// ���� �浹�� �� �ִ� ���� ����. ��¥�� �浹 ���¿� ���ؼ� �˻�.
			if (IsCollision(vecLeft[i]->GetCollider(), vecRight[j]->GetCollider()))
			{
				// ���� �浹 ������ collisionmgr�� �����Ұǵ�, ������ �ʹ� ����.
				// Ž���� �����ϰ�, key������ �ʿ��� �͸� ������ �� �ִ� map�� Ȱ�� (��� hash map�� ����ϴ°� better)
				// �� �浹ü���� �����ϰ� ���� �� �ִ� key ���� ����� ���� �� �浹ü�� id �ο�.
				// �� id�� �����ؼ� key���� �����ϸ� ��.
			}
			else
			{
				
			}

		}
	}

}

bool CCollisionMgr::IsCollision(CCollider* _pLeftCol, CCollider* _pRightCol)
{

	return false;
}

void CCollisionMgr::CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	// �� ���� ���� ��, ū ���� ���� ����. ��Ī���� �����̹Ƿ� �� �ʸ� ���
	UINT iRow = (UINT)_eLeft;
	UINT iCol = (UINT)_eRight;

	if (iRow > iCol)
	{
		iRow = (UINT)_eRight;
		iCol = (UINT)_eLeft;
	}

	// ��� ���. �̹� ���� �־����� �����ϰ� �������� �Ҵ�
	if (m_arrCheck[iRow] & (1 << iCol))
	{
		m_arrCheck[iRow] &= ~(1 << iCol);	// ��Ʈ ����
	}
	else
	{
		m_arrCheck[iRow] |= (1 << iCol);	// ��Ʈ �Ҵ�
	}

}

