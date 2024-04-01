#include "CUI.h"

CUI::CUI()
	: m_pParentUI(nullptr)
{
}

CUI::~CUI()
{
}

void CUI::update()
{
	
	update_child();
}

void CUI::finalupdate()
{
	CObject::finalupdate();	// 부모의 final update (콜라이더, 애니메이터)

	m_vFinalPos = GetPos();

	if (m_pParentUI)
	{
		Vec2 vParentPos = m_pParentUI->GetFinalPos();
		m_vFinalPos += vParentPos;
	}

	finalupdate_child();
}

void CUI::render(HDC _dc)
{
	Vec2 vPos = GetFinalPos();
	Vec2 vScale = GetScale();

	// UI는 카메라 좌표에 영향을 받지 않는다. ? 다 그런건 아니다.
	// -> 자식 클래스로 분류해서 구현 예정
	Rectangle(_dc
		, int(vPos.x)
		, int(vPos.y)
		, int(vPos.x + vScale.x)
		, int(vPos.y + vScale.y));

	// ui child render
	render_child(_dc);
}

void CUI::update_child()
{
	for (auto child : m_vecChildUI)
	{
		child->update();
	}
}

void CUI::finalupdate_child()
{
	for (auto child : m_vecChildUI)
	{
		child->finalupdate();
	}
}

void CUI::render_child(HDC _dc)
{
	for (auto child : m_vecChildUI)
	{
		child->render(_dc);
	}
}
