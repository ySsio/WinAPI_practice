#include "pch.h"
#include "CMissile.h"
#include "CTimeMgr.h"

CMissile::CMissile()
	: m_fTheta(0.f)
	, m_vDir(Vec2{-1,7})
{
 	m_vDir = m_vDir.Normalize();
}

CMissile::~CMissile()
{
}

void CMissile::update()
{
	Vec2 vPos = GetPos();

	// �� ���� ���
	//vPos.x += 600.f * cosf(m_fTheta) * fDT;
	//vPos.y += 600.f * sinf(m_fTheta) * fDT;

	// ���� ���� ���
	vPos.x += 600.f * m_vDir.x * fDT;
	vPos.y -= 600.f * m_vDir.y * fDT;	// ������ ��ǥ�� y���� �ݴ�ϱ� -

	SetPos(vPos);
}

void CMissile::render(HDC _dc)
{
	Ellipse(_dc
		, (int)(GetPos().x - GetScale().x / 2)
		, (int)(GetPos().y - GetScale().y / 2)
		, (int)(GetPos().x + GetScale().x / 2)
		, (int)(GetPos().y + GetScale().y / 2));
}
