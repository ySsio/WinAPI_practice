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
	// 이름 지정
	SetName(L"Monster");

	// Texture 로딩하기
	SetTexture(CResMgr::GetInst()->LoadTexture(L"MonsterTex", L"texture\\Monster.bmp"));

	// 콜라이더 활성화 (오브젝트 생성)
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


	// ##########   처음에 날아와서 제자리 (CenterPos)에 위치   ########
	float dist = (m_vCenterPos - vChangePos).Length();
	if (dist>50)
	{

		Vec2 dir = (m_vCenterPos - vChangePos).Normalize();
		
		// 중력
		//Vec2 force = dir / dist / dist * 1000000;
		//m_vSpeed += force * fDT;

		m_vSpeed = dir * dist * dist / 100;

		//m_vSpeed += dir * dist * fDT ;

		vChangePos += m_vSpeed * fDT;
	}
	else {
		// 제자리에 위치 완료 했으면
		// #########   좌우 배회   #########
		m_time -= fDT;
		if (CMonster::m_time < 0)
		{
			CreateMissile();
			CMonster::m_time = 1.f;
		}

		vChangePos.x += fDT * m_iDir * m_fSpeed;

		float fDiff = abs(m_vCenterPos.x - vChangePos.x) - m_fMaxDistance;

		// 배회 거리 기준량을 넘어섰는지 확인
		if (0.f <= fDiff)
		{
			// 방향 변경
			m_iDir *= -1;
			vChangePos.x += fDiff * m_iDir;
		}
	}

	// ###############################################################


	SetPos(vChangePos);
}

void CMonster::render(HDC _dc)
{
	// width/ height은 당연히 양수니까 UINT였는데 좌표는 음수 될 수 있으니까 int로 변환
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

	// 이름으로 충돌한 오브젝트 구분한다고 가정
	if (pOtherObj->GetName() == L"Missile_Player")
	{
		// 나(몬스터)를 삭제. => 씬의 벡터에서도 뺴줘야함.
		// 어느 시점에서 삭제해야 하는가. => 지연 처리, 이벤트 매니저
		// 예를 들어 유도탄이 노리던 객체가 삭제되면 갑자기 이상한 메모리 주소를 target으로 유도됨
		// 삭제된 객체 포인터를 사용하고 있는 모든 모든 애들한테 알려줘야 한다고? 에바지

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
