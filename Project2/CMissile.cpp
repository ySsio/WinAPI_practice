#include "pch.h"
#include "CMissile.h"
#include "CTimeMgr.h"
#include "CPlayer.h"

CMissile::CMissile()
	: m_fDir(1.f)
	, m_vCenterPos{}
	, m_fDist(20.f)
	, m_fSpeed(200.f)
	, i_Dir(1)
	, target(0)
	, m_vAcc{}
{
}

CMissile::~CMissile()
{
}

void CMissile::update()
{
	Vec2 vPos = GetPos();

	//vPos.y += 600.f * fDT * m_fDir;
	
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

	// ####### ����ź #######
	// ���ӵ� ���, �÷��̾�� �����η� (�Ÿ��� �ݺ���� ��) �ۿ�
	if (target != nullptr)
	{
		// �ӽ� ����

		Vec2 m_vDir = (target->GetPos() - GetPos()).Normalized();
		float dist2Target = Vec2::Dist(target->GetPos(), GetPos());

		if (dist2Target > 10.f)
		{
			m_vAcc = m_vDir * (1 / dist2Target) * 50000000;
		}
		else {
			m_vAcc = Vec2{ 0,0 };
		}

		
	}

	// ######################
	//    ������ġ   +            �ӵ�     * �ð�  +  
	vPos = vPos + Vec2(0.f,300.f * m_fDir) * fDT + m_vAcc * pow(fDT, 2);

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
