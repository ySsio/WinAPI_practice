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
		if (m_pTargetObj->IsDead())	// ��ü�� dead object��� target ����
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

	// ȭ�� �߾���ǥ�� ī�޶� LookAt ��ǥ���� ���̰� ���
	CalDiff();
}

void CCamera::CalDiff()
{
	// ���� LookAt�� ���� LookAt�� ���̰��� �����ؼ� ���� LookAt�� ���Ѵ�
	
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
