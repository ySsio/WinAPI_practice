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
	// 이름 지정
	SetName(L"Monster");

	// Texture 로딩하기
	SetTexture(CResMgr::GetInst()->LoadTexture(L"MonsterTex_A", L"texture\\Monster_A.bmp"));

	// 콜라이더 활성화 (오브젝트 생성)
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
	// width/ height은 당연히 양수니까 UINT였는데 좌표는 음수 될 수 있으니까 int로 변환
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

	// 이름으로 충돌한 오브젝트 구분한다고 가정
	if (pOtherObj->GetName() == L"Missile_Player")
	{
		// 나(몬스터)를 삭제. => 씬의 벡터에서도 뺴줘야함.
		// 어느 시점에서 삭제해야 하는가. => 지연 처리, 이벤트 매니저
		// 예를 들어 유도탄이 노리던 객체가 삭제되면 갑자기 이상한 메모리 주소를 target으로 유도됨
		// 삭제된 객체 포인터를 사용하고 있는 모든 모든 애들한테 알려줘야 한다고? 에바지

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
