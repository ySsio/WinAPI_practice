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
	// 충돌 검사
	// 1. 충돌하는 그룹 체크
	for (UINT iRow = 0; iRow < (UINT)GROUP_TYPE::END; ++iRow)
	{
		// iCol을 iRow부터 시작하는 이유는 m_arrCheck 표가 대칭적이라 나머지 절반을 검사할 필요가 없기 때문.
		for (UINT iCol = iRow; iCol < (UINT)GROUP_TYPE::END; ++iCol)
		{
			if (m_arrCheck[iRow] & (1 << iCol))
			{
				// enum class의 형변환 ㄷㄷ
				CollisionGroupUpdate((GROUP_TYPE)iRow, (GROUP_TYPE)iCol);
			}
		}
	}
}

void CCollisionMgr::CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

	// vector<CObject*> 타입으로 받으면 지역변수에 복사생성자 실행된거라 원본 참조한 게 아님..!
	// 동일하게 레퍼런스 타입으로 받아줘야 함.
	// # 근데 이러면 스택 사이즈 (레퍼런스 변수 사이즈)가 어떻게 되는거냐?? 레퍼런스 타입이 내부적으로 어떻게 동작하는건지..
	const vector<CObject*>& vecLeft = pCurScene->GetGroupObject(_eLeft);
	const vector<CObject*>& vecRight = pCurScene->GetGroupObject(_eRight);

	
	for (size_t i = 0; i < vecLeft.size(); i++)
	{
		// 콜라이더 컴포넌트 없는 객체면 그냥 통과
		if (vecLeft[i]->GetCollider() == nullptr)
			continue;

		for (size_t j = 0; j < vecRight.size(); j++)
		{
			// 콜라이더 컴포넌트 없는 객체면 그냥 통과
			if (vecRight[j]->GetCollider() == nullptr)
				continue;

			// 자기 자신과 충돌은 방지해야 함.! (가리키는 오브젝트 주소가 동일)
			if (vecLeft[i] == vecRight[j])
				continue;

			// 이제 충돌할 수 있는 조건 충족. 진짜로 충돌 상태에 대해서 검사.
			if (IsCollision(vecLeft[i]->GetCollider(), vecRight[j]->GetCollider()))
			{
				// 이전 충돌 정보를 collisionmgr에 저장할건데, 조합이 너무 많음.
				// 탐색에 유리하고, key값으로 필요한 것만 저장할 수 있는 map을 활용 (사실 hash map을 사용하는게 better)
				// 두 충돌체만이 고유하게 가질 수 있는 key 값을 만들기 위해 각 충돌체에 id 부여.
				// 두 id를 조합해서 key값을 생성하면 됨.
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
	// 더 작은 값을 행, 큰 값을 열로 설정. 대칭적인 구조이므로 한 쪽만 사용
	UINT iRow = (UINT)_eLeft;
	UINT iCol = (UINT)_eRight;

	if (iRow > iCol)
	{
		iRow = (UINT)_eRight;
		iCol = (UINT)_eLeft;
	}

	// 토글 방식. 이미 관계 있었으면 해제하고 없었으면 할당
	if (m_arrCheck[iRow] & (1 << iCol))
	{
		m_arrCheck[iRow] &= ~(1 << iCol);	// 비트 해제
	}
	else
	{
		m_arrCheck[iRow] |= (1 << iCol);	// 비트 할당
	}

}

