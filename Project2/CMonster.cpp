#include "CMonster.h"
#include "CTimeMgr.h"
#include "CResMgr.h"
#include "CEventMgr.h"

#include "CTexture.h"
#include "CCollider.h"
#include "CMissile.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "AI.h"

CMonster::CMonster()
	: m_tInfo{}
	, m_pAI(nullptr)
{
	// �̸� ����
	SetName(L"Monster");

	// Texture �ε��ϱ�
	SetTexture(CResMgr::GetInst()->LoadTexture(L"MonsterTex_A", L"texture\\Monster_A.bmp"));

	// �ݶ��̴� Ȱ��ȭ (������Ʈ ����)
	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(-2.f, -10.f));
	GetCollider()->SetScale(Vec2(40.f, 30.f));
}

CMonster::~CMonster()
{
	if (m_pAI != nullptr)
		delete m_pAI;
}

void CMonster::SetAI(AI* _AI)
{
	m_pAI = _AI; m_pAI->m_pOwner = this;
}

void CMonster::update()
{
	if (m_pAI != nullptr)
		m_pAI->update();
}

void CMonster::render(HDC _dc)
{
	// width/ height�� �翬�� ����ϱ� UINT���µ� ��ǥ�� ���� �� �� �����ϱ� int�� ��ȯ
	int iWidth = (int)GetTexture()->Width();
	int iHeight = (int)GetTexture()->Height();

	Vec2 vPos = GetPos();
	vPos = CCamera::GetInst()->GetRenderPos(vPos);

	BLENDFUNCTION bf = {};
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = AC_SRC_ALPHA;
	bf.SourceConstantAlpha = 127;

	AlphaBlend(_dc
		, (int)(vPos.x - (float)iWidth / 2)
		, (int)(vPos.y - (float)iHeight / 2)
		, iWidth, iHeight
		, GetTexture()->GetDC()
		, 0, 0, iWidth, iHeight
		, bf);

	//TransparentBlt(_dc
	//	, (int)(vPos.x - (float)iWidth / 2)
	//	, (int)(vPos.y - (float)iHeight / 2)
	//	, iWidth, iHeight
	//	, GetTexture()->GetDC()
	//	, 0, 0, iWidth, iHeight
	//	, RGB(255, 0, 255));

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

		--m_tInfo.m_fHP;
	}

	if (m_tInfo.m_fHP == 0)
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
