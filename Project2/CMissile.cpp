#include "pch.h"
#include "CMissile.h"
#include "CTimeMgr.h"
#include "CResMgr.h"
#include "CTexture.h"

CMissile::CMissile()
	: m_fTheta(0.f)
	, m_fRotateAngle(0.f)
	, m_vDir(Vec2{0,-1}) 
{
 	m_vDir = m_vDir.Normalize();
	SetTexture(CResMgr::GetInst()->LoadTexture(L"BulletTex", L"texture\\Bullet.bmp"));
}

CMissile::~CMissile()
{
}

void CMissile::update()
{
	Vec2 vPos = GetPos();

	// 각 기준 계산
	//vPos.x += 600.f * cosf(m_fTheta) * fDT;
	//vPos.y += 600.f * sinf(m_fTheta) * fDT;

	// 벡터 기준 계산
	vPos.x += 600.f * m_vDir.x * fDT;
	vPos.y += 600.f * m_vDir.y * fDT;	// 윈도우 좌표계 y축이 반대니까 -

	SetPos(vPos);
}

void CMissile::render(HDC _dc)
{
	// width/ height은 당연히 양수니까 UINT였는데 좌표는 음수 될 수 있으니까 int로 변환
	int iWidth = (int)GetTexture()->Width();
	int iHeight = (int)GetTexture()->Height();

	Vec2 vPos = GetPos();

	//TransparentBlt(_dc
	//	, (int)(vPos.x - (float)iWidth / 2)
	//	, (int)(vPos.y - (float)iHeight / 2)
	//	, iWidth, iHeight
	//	, GetTexture()->GetDC()
	//	, 0, 0, iWidth, iHeight
	//	, RGB(255, 0, 255));

	m_fRotateAngle = m_fRotateAngle + 4 * PI * fDT > 2 * PI ? m_fRotateAngle + 4 * PI * fDT - 2 * PI : m_fRotateAngle + 4 * PI * fDT;

	Vec2 pp[3] = {};
	pp[0] = Vec2{ -(float)iWidth / 2 ,-(float)iHeight / 2 };
	pp[1] = Vec2{ (float)iWidth / 2 ,-(float)iHeight / 2 };
	pp[2] = Vec2{ -(float)iWidth / 2 ,(float)iHeight / 2 };

	pp[0].Rotate(m_fRotateAngle);
	pp[1].Rotate(m_fRotateAngle);
	pp[2].Rotate(m_fRotateAngle);

	POINT ppp[3] = {};
	
	ppp[0] = POINT{ (int)(vPos.x + pp[0].x), (int)(vPos.y + pp[0].y) };
	ppp[1] = POINT{ (int)(vPos.x + pp[1].x), (int)(vPos.y + pp[1].y) };
	ppp[2] = POINT{ (int)(vPos.x + pp[2].x), (int)(vPos.y + pp[2].y) };


	PlgBlt(_dc
		, ppp
		, GetTexture()->GetDC()
		, 0
		, 0
		, iWidth, iHeight
		, NULL
		, 0, 0);
}
