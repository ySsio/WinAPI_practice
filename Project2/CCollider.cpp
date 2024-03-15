#include "pch.h"
#include "CCollider.h"
#include "CObject.h"
#include "CCore.h"
#include "SelectGDI.h"


CCollider::CCollider()
	: m_pOwner(nullptr)
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
}

void CCollider::render(HDC _dc)
{
	// 테두리 라인만 그릴 거임.
	// 1. drawline으로 4개의 선을 그리는 방법
	// 2. hollowbrush로 지정하고 rectangle(). 테두리 색은 pen 색
	//	- 자주 쓰는 오브젝트 (펜)은 커널오브젝트?로 만든 뒤 프로그램 종료할 때 해제..? => 코어에서 관리

	// 이름 없는 객체로 선언하면 바로 소멸됨.
	SelectGDI p (_dc, PEN_TYPE::GREEN);
	SelectGDI b (_dc, BRUSH_TYPE::HOLLOW);

	Rectangle(_dc
		, (int) m_vFinalPos.x - m_vScale.x / 2.f
		, (int) m_vFinalPos.y - m_vScale.y / 2.f
		, (int) m_vFinalPos.x + m_vScale.x / 2.f
		, (int) m_vFinalPos.y + m_vScale.y / 2.f);
}
