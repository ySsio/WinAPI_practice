#include "pch.h"
#include "CCamera.h"
#include "CObject.h"
#include "CCore.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"

CCamera::CCamera()
	: m_pTargetObj(nullptr)
{

}

CCamera::~CCamera()
{

}

void CCamera::update()
{
	if (m_pTargetObj)
	{
		if (m_pTargetObj->IsDead())	// 물체가 dead object라면 target 해제
		{
			m_pTargetObj = nullptr;
		}
		else
		{
			m_vLookAt = m_pTargetObj->GetPos();
		}
	}

	if (KEY_HOLD(KEY::UP))
		m_vLookAt.y -= 500.f * fDT;
	if (KEY_HOLD(KEY::DOWN))
		m_vLookAt.y += 500.f * fDT;
	if (KEY_HOLD(KEY::LEFT))
		m_vLookAt.x -= 500.f * fDT;
	if (KEY_HOLD(KEY::RIGHT))
		m_vLookAt.x += 500.f * fDT;

	// 화면 중앙좌표와 카메라 LookAt 좌표간의 차이값 계산
	CalDiff();
}

void CCamera::CalDiff()
{
	// 이전 LookAt과 목적 LookAt의 차이값을 보정해서 현재 LookAt을 구한다
	
	Vec2 vLookDir = m_vLookAt - m_vPrevLookAt;
	static float time = 1.f;

	if (vLookDir.x != 0 || vLookDir.y != 0)
	{
		if (time <= 0)
		{
			time = 1.f;
			m_vCurLookAt = m_vLookAt;
		}
		else
		{
			float velocity = vLookDir.Length() / time;	// 남은 거리/남은 시간
			time -= fDT;
			m_vCurLookAt = m_vPrevLookAt + vLookDir.Normalize() * velocity * fDT;
		}
	}

	

	

	Vec2 vResolution = CCore::GetInst()->GetResolution();
	Vec2 vCenter = vResolution / 2.f;

	m_vDiff = m_vCurLookAt - vCenter;

	m_vPrevLookAt = m_vCurLookAt;
}
