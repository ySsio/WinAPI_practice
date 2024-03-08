#include "pch.h"
#include "CMissile.h"
#include "CTimeMgr.h"

CMissile::CMissile()
	: m_fDir(1.f)
	, m_vCenterPos{}
	, m_fDist(20.f)
	, m_fSpeed(200.f)
	, i_Dir(1)
{
}

CMissile::~CMissile()
{
}

void CMissile::update()
{
	Vec2 vPos = GetPos();

	vPos.y += 600.f * fDT * m_fDir;

	
	// ### zigzag missile ###
	//vPos.x += m_fSpeed * fDT * i_Dir;

	//if (vPos.x > m_vCenterPos.x + m_fDist)
	//{
	//	vPos.x = 2 * (m_vCenterPos.x + m_fDist) - vPos.x;
	//	i_Dir = -1.f;
	//}
	//else if (vPos.x < m_vCenterPos.x - m_fDist)
	//{
	//	vPos.x = 2 * (m_vCenterPos.x - m_fDist) - vPos.x;
	//	i_Dir = 1.f;
	//}
	// ######################

	
	

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
