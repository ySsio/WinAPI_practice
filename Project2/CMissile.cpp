#include "pch.h"
#include "CMissile.h"
#include "CTimeMgr.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "CCollider.h"

CMissile::CMissile()
	: m_fTheta(0.f)
	, m_fRotateAngle(0.f)
	, m_vDir(Vec2{0,-1}) 
{
	// �̸� ����
	SetName(L"Missile");

	// ���� ����ȭ
 	m_vDir = m_vDir.Normalize();

	// Texture �ε��ϱ�
	SetTexture(CResMgr::GetInst()->LoadTexture(L"BulletTex", L"texture\\Bullet.bmp"));

	// �ݶ��̴� Ȱ��ȭ (������Ʈ ����)
	CreateCollider();
	GetCollider()->SetScale(Vec2(20.f, 20.f));
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
	vPos.y += 600.f * m_vDir.y * fDT;	// ������ ��ǥ�� y���� �ݴ�ϱ� -

	SetPos(vPos);
}

void CMissile::render(HDC _dc)
{
	// width/ height�� �翬�� ����ϱ� UINT���µ� ��ǥ�� ���� �� �� �����ϱ� int�� ��ȯ
	int iWidth = (int)GetTexture()->Width();
	int iHeight = (int)GetTexture()->Height();

	Vec2 vPos = GetPos();
	vPos = CCamera::GetInst()->GetRenderPos(vPos);

	TransparentBlt(_dc
		, (int)(vPos.x - (float)iWidth / 2)
		, (int)(vPos.y - (float)iHeight / 2)
		, iWidth, iHeight
		, GetTexture()->GetDC()
		, 0, 0, iWidth, iHeight
		, RGB(255, 0, 255));

	//m_fRotateAngle = m_fRotateAngle + 4 * PI * fDT > 2 * PI ? m_fRotateAngle + 4 * PI * fDT - 2 * PI : m_fRotateAngle + 4 * PI * fDT;

	//Vec2 pp[3] = {};
	//pp[0] = Vec2{ -(float)iWidth / 2 ,-(float)iHeight / 2 };
	//pp[1] = Vec2{ (float)iWidth / 2 ,-(float)iHeight / 2 };
	//pp[2] = Vec2{ -(float)iWidth / 2 ,(float)iHeight / 2 };

	//pp[0].Rotate(m_fRotateAngle);
	//pp[1].Rotate(m_fRotateAngle);
	//pp[2].Rotate(m_fRotateAngle);

	//POINT ppp[3] = {};
	//
	//ppp[0] = POINT{ (int)(vPos.x + pp[0].x), (int)(vPos.y + pp[0].y) };
	//ppp[1] = POINT{ (int)(vPos.x + pp[1].x), (int)(vPos.y + pp[1].y) };
	//ppp[2] = POINT{ (int)(vPos.x + pp[2].x), (int)(vPos.y + pp[2].y) };


	//PlgBlt(_dc
	//	, ppp
	//	, GetTexture()->GetDC()
	//	, 0
	//	, 0
	//	, iWidth, iHeight
	//	, NULL
	//	, 0, 0);

	// ������Ʈ ����
	component_render(_dc);
}

void CMissile::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	// �̸����� �浹�� ������Ʈ �����Ѵٰ� ����
	if (pOtherObj->GetName() == L"Monster")
	{
		DeleteObject(this);
	}
}
