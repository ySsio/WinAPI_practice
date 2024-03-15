#pragma once

class CCollider;

class CCollisionMgr
{
	SINGLETON(CCollisionMgr);

private:
	// 충돌체 간의 이전 프레임 충돌 정보
	UINT	m_arrCheck[(UINT)GROUP_TYPE::END];	// 그룹 간의 충돌 체크 매트릭스

public:
	void init();
	void update();
	// 32가지 그룹의 조합을 비트로 표현할 거임. 32bit = 4byte, 32크기의 배열에 각각 4byte의 비트 상태값 (UINT) 저장
	void CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	// 충돌 지정했던 모든 그룹을 초기화함. memset은 지정한 주소를 바이트 단위로 값 세팅하는 함수.
	void Reset() { memset(m_arrCheck, 0, sizeof(m_arrCheck)); }

private:
	void CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	bool IsCollision(CCollider* _pLeftCol, CCollider* _pRightCol);
};

