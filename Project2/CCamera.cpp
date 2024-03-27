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
			float velocity = vLookDir.Length() / time;	// ���� �Ÿ�/���� �ð�
			time -= fDT;
			m_vCurLookAt = m_vPrevLookAt + vLookDir.Normalize() * velocity * fDT;
		}
	}

	

	

	Vec2 vResolution = CCore::GetInst()->GetResolution();
	Vec2 vCenter = vResolution / 2.f;

	m_vDiff = m_vCurLookAt - vCenter;

	m_vPrevLookAt = m_vCurLookAt;
}
