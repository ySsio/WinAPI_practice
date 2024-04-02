#include "global.h"
#include "CUI.h"
#include "CKeyMgr.h"
#include "CCamera.h"
#include "SelectGDI.h"
#include "CCore.h"

CUI::CUI(bool _bCamAff)
	: m_pParentUI(nullptr)
	, m_bCamAffected(_bCamAff)
	, m_bMouseOn(false)
	, m_bLbtnDown(false)
{
}

CUI::~CUI()
{
	Safe_Delete_Vec(m_vecChildUI);
}

void CUI::update()
{
	
	update_child();
}

void CUI::finalupdate()
{
	CObject::finalupdate();	// �θ��� final update (�ݶ��̴�, �ִϸ�����)

	m_vFinalPos = GetPos();	// position�� �θ� ���� offsetpos�� ����� ����

	if (m_pParentUI)
	{
		Vec2 vParentPos = m_pParentUI->GetFinalPos();
		m_vFinalPos += vParentPos;
	}

	// UI Mouse üũ
	MouseOnCheck();

	

	finalupdate_child();
}

void CUI::render(HDC _dc)
{
	Vec2 vPos = GetFinalPos();
	Vec2 vScale = GetScale();

	if (m_bCamAffected)
		vPos = CCamera::GetInst()->GetRenderPos(vPos);

	HPEN hPen = CCore::GetInst()->GetPen(PEN_TYPE::BLUE);
	HBRUSH hBrush = CCore::GetInst()->GetBrush(BRUSH_TYPE::WHITE);

	if (m_bLbtnDown)
	{
		hPen = CCore::GetInst()->GetPen(PEN_TYPE::RED);
		hBrush = CCore::GetInst()->GetBrush(BRUSH_TYPE::BLACK);
	}

	HPEN m_hDefaultPen = (HPEN)SelectObject(_dc, hPen);
	HBRUSH m_hDefaultBrush = (HBRUSH)SelectObject(_dc, hBrush);

	// UI�� ī�޶� ��ǥ�� ������ ���� �ʴ´�. ? �� �׷��� �ƴϴ�.
	// -> �ڽ� Ŭ������ �з��ؼ� ���� ����
	Rectangle(_dc
		, int(vPos.x)
		, int(vPos.y)
		, int(vPos.x + vScale.x)
		, int(vPos.y + vScale.y));


	
	SelectObject(_dc, m_hDefaultPen);
	SelectObject(_dc, m_hDefaultBrush);

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

void CUI::MouseOnCheck()
{
	Vec2 vMousePos = MOUSE_POS;
	Vec2 vScale = GetScale();

	if (m_bCamAffected)
	{
		vMousePos = CCamera::GetInst()->GetRealPos(vMousePos);
	}

	if (m_vFinalPos.x <= vMousePos.x && vMousePos.x <= m_vFinalPos.x + vScale.x
		&& m_vFinalPos.y <= vMousePos.y && vMousePos.y <= m_vFinalPos.y + vScale.y)
	{
		m_bMouseOn = true;
	}
	else
	{
		m_bMouseOn = false;
	}
}

void CUI::MouseOn()
{
	
}

void CUI::MouseLbtnDown()
{
}

void CUI::MouseLbtnUp()
{
}

void CUI::MouseLbtnClicked()
{
}
