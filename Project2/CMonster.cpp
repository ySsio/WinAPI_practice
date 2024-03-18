#include "pch.h"
#include "CMonster.h"
#include "CTimeMgr.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "CCollider.h"

CMonster::CMonster()
	: m_vSpeed(Vec2(0, 10))
	, m_vCenterPos(Vec2(0.f, 0.f))
	, m_target(0)
	, m_fSpeed(100.f)
	, m_fMaxDistance(50.f)
	, m_iDir(1)
{
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
	Vec2 vTargetPos = m_target->GetPos();

	// ##########   처음에 날아와서 제자리 (CenterPos)에 위치   ########
	float dist = (m_vCenterPos - vChangePos).Length();
	if (m_vSpeed.Length()>0.1f)
	{

		Vec2 dir = (m_vCenterPos - vChangePos).Normalize();
		
		// 중력
		//Vec2 force = dir / dist / dist * 1000000;
		//m_vSpeed += force * fDT;

		Vec2 force = dir / dist / dist * 1000000;
		m_vSpeed -= force * fDT;

		m_vSpeed += dir * dist * fDT ;

		vChangePos += m_vSpeed * fDT;
	}

	// ###############################################################



	// 제자리에 위치 완료 했으면
	if (false)
	{
		// #########   좌우 배회   #########

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

	SetPos(vChangePos);

	// ###################################
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
	if (pOtherObj->GetName() == L"Missile")
	{
		// 나(몬스터)를 삭제. => 씬의 벡터에서도 뺴줘야함.
		// 어느 시점에서 삭제해야 하는가.
		// 예를 들어 유도탄이 노리던 객체가 삭제되면 갑자기 이상한 메모리 주소를 target으로 유도됨
		// 삭제된 객체 포인터를 사용하고 있는 모든 모든 애들한테 알려줘야 한다고? 에바지

		// 문제 생길 여지 있는 이벤트들
		// 삭제
		// 씬 변경

		// 한 업데이트에 일어나는 일들은 모두 동시간 대에 일어나는 일이라고 생각
		// 코드 자체는 순차적으로 돌고 있기 때문에 한 프레임에서 삭제가 일어나면
		// 그 코드가 실행되기 전에는 살아있다고 인식하다가 삭제 코드 이후에 작동하는 코드에서는
		// 객체가 삭제되었다고 인식하는 문제 발생
		// 따라서 event를 frame 단위로 동기화 시켜줘야 함.!!!
		// => event frame sync = 지연처리
		// 날 죽여주세요 요청 => 지연처리 해서 다음번 프레임에 모두에게 적용
		// => 다음 프레임에서는 모두가 객체 삭제를 인지할 수 있음.
		// Event Manager. 한 번의 업데이트 동안 발생하는 이벤트 취합
		// 그 프레임 모두 실행된 후 이벤트 처리
		// 다음 프레임에는 모두 동시에 영향 받음.

		SetPos(GetPos() + Vec2(0, 10));
	}
}


