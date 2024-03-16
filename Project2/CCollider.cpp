#include "pch.h"
#include "CCollider.h"
#include "CObject.h"
#include "CCore.h"
#include "SelectGDI.h"

UINT CCollider::g_iNextID = 0;

CCollider::CCollider()
	: m_pOwner(nullptr)
	, m_iID(g_iNextID++)	// id를 할당하면서 static 변수를 1 증가 시키면서 중복 피함
{
}

CCollider::CCollider(const CCollider& _origin)
	: m_pOwner (nullptr)
	, m_vOffsetPos(_origin.m_vOffsetPos)		// 초기화 안하면 Vec2의 기본생성자가 초기화 해줄 거야!
	, m_vScale(_origin.m_vScale)
	, m_iID(g_iNextID++)
{

}

CCollider::~CCollider()
{
}


void CCollider::finalupdate()
{
	// 오브젝트 위치 따라감.
	Vec2 vObjectPos = m_pOwner->GetPos();
	m_vFinalPos = vObjectPos + m_vOffsetPos;

	assert(m_iCol >= 0);
}

void CCollider::render(HDC _dc)
{
	// 테두리 라인만 그릴 거임.
	// 1. drawline으로 4개의 선을 그리는 방법
	// 2. hollowbrush로 지정하고 rectangle(). 테두리 색은 pen 색
	//	- 자주 쓰는 오브젝트 (펜)은 커널오브젝트?로 만든 뒤 프로그램 종료할 때 해제..? => 코어에서 관리

	PEN_TYPE ePen = PEN_TYPE::GREEN;

	if (m_iCol)
		ePen = PEN_TYPE::RED;

	// 이름 없는 객체로 선언하면 바로 소멸됨.
	SelectGDI p (_dc, ePen);
	SelectGDI b (_dc, BRUSH_TYPE::HOLLOW);

	Rectangle(_dc
		, (int) m_vFinalPos.x - m_vScale.x / 2.f
		, (int) m_vFinalPos.y - m_vScale.y / 2.f
		, (int) m_vFinalPos.x + m_vScale.x / 2.f
		, (int) m_vFinalPos.y + m_vScale.y / 2.f);
}

void CCollider::OnCollision(CCollider* _pOther)
{
}

void CCollider::OnCollisionEnter(CCollider* _pOther)
{
	++m_iCol;
}

void CCollider::OnCollisionExit(CCollider* _pOther)
{
	--m_iCol;
}
