#include "CPanelUI.h"
#include "CKeyMgr.h"


CPanelUI::CPanelUI()
	: CUI(false)	// 기본생성자를 없앴으므로 다른 생성자를 호출
{
}

CPanelUI::~CPanelUI()
{
}


void CPanelUI::update()
{
}

void CPanelUI::render(HDC _dc)
{
	CUI::render(_dc);


}



void CPanelUI::MouseOn()
{
	if (IsLbtnDown())
	{
		Vec2 vDiff = MOUSE_POS - m_vDragStart;
		Vec2 vCurPos = GetPos();
		vCurPos += vDiff;
		SetPos(vCurPos);

		m_vDragStart = MOUSE_POS;
	}
}

void CPanelUI::MouseLbtnDown()
{
	m_vDragStart = MOUSE_POS;

}

void CPanelUI::MouseLbtnUp()
{
}