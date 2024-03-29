#include "global.h"
#include "CCollisionMgr.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CObject.h"

#include "CCollider.h"



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
	map<ULONGLONG, bool>::iterator iter;

	for (size_t i = 0; i < vecLeft.size(); i++)
	{
		CCollider* pLeftCol = vecLeft[i]->GetCollider();

		// �ݶ��̴� ������Ʈ ���� ��ü�� �׳� ���
		if (pLeftCol == nullptr)
			continue;

		for (size_t j = 0; j < vecRight.size(); j++)
		{
			CCollider* pRightCol = vecRight[j]->GetCollider();

			// �ݶ��̴� ������Ʈ ���� ��ü�� �׳� ���
			if (pRightCol == nullptr)
				continue;

			// �ڱ� �ڽŰ� �浹�� �����ؾ� ��.! (����Ű�� ������Ʈ �ּҰ� ����)
			if (vecLeft[i] == vecRight[j])
				continue;

			
				

			// ���� �浹 ������ collisionmgr�� �����Ұǵ�, ������ �ʹ� ����.
			// Ž���� �����ϰ�, key������ �ʿ��� �͸� ������ �� �ִ� map�� Ȱ�� (��� hash map�� ����ϴ°� better)
			// �� �浹ü���� �����ϰ� ���� �� �ִ� key ���� ����� ���� �� �浹ü�� id �ο�.
			// �� id�� �����ؼ� key���� �����ϸ� ��.

			// �� �浹ü�� �浹 Ű ���� union���� ����!!
			COLLIDER_ID ID;
			ID.Left_id = pLeftCol->GetID();
			ID.Right_id = pRightCol->GetID();

			iter = m_mapColInfo.find(ID.ID);

			
			// �˻� ����. (�浹 ���� ����� �� ����, ���ο� �浹)
			if (iter == m_mapColInfo.end())
			{
				// �ʿ� �߰� (�ϴ� false�� �ְ� �ؿ��� �ϰ������� ����) + ���� �����ӿ� �浹 ���ߴ� ���
				iter = m_mapColInfo.insert(make_pair(ID.ID, false)).first;
			}

			// ���� �浹�� �� �ִ� ���� ����. ��¥�� �浹 ���¿� ���ؼ� �˻�.
			if (IsCollision(pLeftCol, pRightCol) && !(vecLeft[i]->IsDead() || vecRight[j]->IsDead()))
			{
				// ���� �浹 ��

				// ���� �����ӿ� �浹�� �־���.
				if (iter->second)
				{
					// ��� �浹���̴�. OnCollision
					pLeftCol->OnCollision(pRightCol);
					pRightCol->OnCollision(pLeftCol);
				}
				// ���� �����ӿ��� �浹 ������.
				else
				{
					// �浹���·� �����ߴ�. Enter
					pLeftCol->OnCollisionEnter(pRightCol);
					pRightCol->OnCollisionEnter(pLeftCol);
					iter->second = true;
				}
			}
			else
			{
				// ���� �浹 ������ ����.

				// ���� �����ӿ� �浹�� �־���.
				if (iter->second)
				{
					// �浹���� �������Դ�. Exit
					pLeftCol->OnCollisionExit(pRightCol);
					pRightCol->OnCollisionExit(pLeftCol);
					iter->second = false;
				}
			}
		}
	}

}

bool CCollisionMgr::IsCollision(CCollider* _pLeftCol, CCollider* _pRightCol)
{
	Vec2 vLeftPos = _pLeftCol->GetFinalPos();
	Vec2 vRightPos = _pRightCol->GetFinalPos();
	Vec2 vLeftScale = _pLeftCol->GetScale();
	Vec2 vRightScale = _pRightCol->GetScale();

	if (abs(vRightPos.x - vLeftPos.x) < (vRightScale.x + vLeftScale.x) / 2 &&
		abs(vRightPos.y - vLeftPos.y) < (vRightScale.y + vLeftScale.y) / 2)
	{
		return true;
	}

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

