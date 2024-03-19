#include "pch.h"
#include "CMonster.h"
#include "CTimeMgr.h"
#include "CResMgr.h"
#include "CEventMgr.h"

#include "CTexture.h"
#include "CCollider.h"
#include "CMissile.h"

#include "CSceneMgr.h"
#include "CScene.h"

CMonster::CMonster()
	: m_vSpeed(Vec2(0, 150))
	, m_vCenterPos(Vec2(0.f, 0.f))
	, m_target(0)
	, m_fSpeed(100.f)
	, m_fMaxDistance(50.f)
	, m_iDir(1)
	, m_time(1.f)
	, m_iHP(5)
{
	// �̸� ����
	SetName(L"Monster");

	// Texture �ε��ϱ�
	SetTexture(CResMgr::GetInst()->LoadTexture(L"MonsterTex", L"texture\\Monster.bmp"));

	// �ݶ��̴� Ȱ��ȭ (������Ʈ ����)
	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(-2.f, -10.f));
	GetCollider()->SetScale(Vec2(40.f, 30.f));
}

CMonster::~CMonster()
{
}

void CMonster::update()
{
	Vec2 vChangePos = GetPos();


	// ##########   ó���� ���ƿͼ� ���ڸ� (CenterPos)�� ��ġ   ########
	float dist = (m_vCenterPos - vChangePos).Length();
	if (dist>50)
	{

		Vec2 dir = (m_vCenterPos - vChangePos).Normalize();
		
		// �߷�
		//Vec2 force = dir / dist / dist * 1000000;
		//m_vSpeed += force * fDT;

		m_vSpeed = dir * dist * dist / 100;

		//m_vSpeed += dir * dist * fDT ;

		vChangePos += m_vSpeed * fDT;
	}
	else {
		// ���ڸ��� ��ġ �Ϸ� ������
		// #########   �¿� ��ȸ   #########
		m_time -= fDT;
		if (CMonster::m_time < 0)
		{
			CreateMissile();
			CMonster::m_time = 1.f;
		}

		vChangePos.x += fDT * m_iDir * m_fSpeed;

		float fDiff = abs(m_vCenterPos.x - vChangePos.x) - m_fMaxDistance;

		// ��ȸ �Ÿ� ���ط��� �Ѿ���� Ȯ��
		if (0.f <= fDiff)
		{
			// ���� ����
			m_iDir *= -1;
			vChangePos.x += fDiff * m_iDir;
		}
	}

	// ###############################################################


	SetPos(vChangePos);
}

void CMonster::render(HDC _dc)
{
	// width/ height�� �翬�� ����ϱ� UINT���µ� ��ǥ�� ���� �� �� �����ϱ� int�� ��ȯ
	int iWidth = (int)GetTexture()->Width();
	int iHeight = (int)GetTexture()->Height();

	Vec2 vPos = GetPos();

	TransparentBlt(_dc
		, (int)(vPos.x - (float)iWidth / 2)
		, (int)(vPos.y - (float)iHeight / 2)
		, iWidth, iHeight
		, GetTexture()->GetDC()
		, 0, 0, iWidth, iHeight
		, RGB(255, 0, 255));

	component_render(_dc);

}

void CMonster::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	// �̸����� �浹�� ������Ʈ �����Ѵٰ� ����
	if (pOtherObj->GetName() == L"Missile_Player")
	{
		// ��(����)�� ����. => ���� ���Ϳ����� �������.
		// ��� �������� �����ؾ� �ϴ°�. => ���� ó��, �̺�Ʈ �Ŵ���
		// ���� ��� ����ź�� �븮�� ��ü�� �����Ǹ� ���ڱ� �̻��� �޸� �ּҸ� target���� ������
		// ������ ��ü �����͸� ����ϰ� �ִ� ��� ��� �ֵ����� �˷���� �Ѵٰ�? ������

		--m_iHP;
	}

	if (m_iHP == 0)
	{
		DeleteObject(this);
	}
	
}


void CMonster::CreateMissile()
{
	Vec2 vMissilePos = GetPos();
	vMissilePos.y += GetScale().y / 2.f;

	CMissile* pMissile = new CMissile;
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(20.f, 20.f));
	pMissile->SetDir(Vec2(0.f, 1.f));

	CreateObject(pMissile, GROUP_TYPE::PROJ_MONSTER);
}
