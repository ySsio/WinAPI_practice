#include "pch.h"
#include "CCollider.h"
#include "CObject.h"
#include "CCore.h"
#include "SelectGDI.h"

UINT CCollider::g_iNextID = 0;

CCollider::CCollider()
	: m_pOwner(nullptr)
	, m_iID(g_iNextID++)	// id�� �Ҵ��ϸ鼭 static ������ 1 ���� ��Ű�鼭 �ߺ� ����
{
}

CCollider::CCollider(const CCollider& _origin)
	: m_pOwner (nullptr)
	, m_vOffsetPos(_origin.m_vOffsetPos)		// �ʱ�ȭ ���ϸ� Vec2�� �⺻�����ڰ� �ʱ�ȭ ���� �ž�!
	, m_vScale(_origin.m_vScale)
	, m_iID(g_iNextID++)
{

}

CCollider::~CCollider()
{
}


void CCollider::finalupdate()
{
	// ������Ʈ ��ġ ����.
	Vec2 vObjectPos = m_pOwner->GetPos();
	m_vFinalPos = vObjectPos + m_vOffsetPos;

	assert(m_iCol >= 0);
}

void CCollider::render(HDC _dc)
{
	// �׵θ� ���θ� �׸� ����.
	// 1. drawline���� 4���� ���� �׸��� ���
	// 2. hollowbrush�� �����ϰ� rectangle(). �׵θ� ���� pen ��
	//	- ���� ���� ������Ʈ (��)�� Ŀ�ο�����Ʈ?�� ���� �� ���α׷� ������ �� ����..? => �ھ�� ����

	PEN_TYPE ePen = PEN_TYPE::GREEN;

	if (m_iCol)
		ePen = PEN_TYPE::RED;

	// �̸� ���� ��ü�� �����ϸ� �ٷ� �Ҹ��.
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
