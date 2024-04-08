#include "global.h"
#include "CCamera.h"
#include "CObject.h"
#include "CCore.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"

CCamera::CCamera()
	: m_pTargetObj(nullptr)
	, m_fTime(1.f)
	, m_fSpeed(0.f)
	, m_fAccTime(1.f)
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



	if (!vLookDir.IsZero())
	{
		if (m_fAccTime > m_fTime)
		{
			m_vCurLookAt = m_vLookAt;
		}
		else
		{
			float v0 = 2 * vLookDir.Length() / m_fTime;
			float a = -v0 / m_fTime;
			float v = v0 + a * ((m_fAccTime*2+fDT)/2.f);
			m_fAccTime += fDT;
			m_vCurLookAt = m_vPrevLookAt + vLookDir.Normalize() * v * fDT;
		}
	}

	

	

	Vec2 vResolution = CCore::GetInst()->GetResolution();
	Vec2 vCenter = vResolution / 2.f;

	m_vDiff = m_vCurLookAt - vCenter;

	m_vPrevLookAt = m_vCurLookAt;
}
