#include "global.h"
#include "CCamera.h"
#include "CObject.h"
#include "CCore.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "CCore.h"

CCamera::CCamera()
	: m_pTargetObj(nullptr)
	, m_fTime(1.f)
	, m_fSpeed(0.f)
	, m_fAccTime(1.f)
	, m_eEffect(CAM_EFFECT::NONE)
	, m_pVeilTex(nullptr)
	, m_fEffectDuration(0.f)
	, m_fCurTime(0.f)
{
	
}

CCamera::~CCamera()
{

}

void CCamera::init()
{
	Vec2 vResolution = CCore::GetInst()->GetResolution();
	m_pVeilTex = CResMgr::GetInst()->CreateTexture(L"CameraVeil", (UINT)vResolution.x, (UINT)vResolution.y);

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

void CCamera::render(HDC _dc)
{
	float fRatio = 0;

	switch (m_eEffect)
	{
		case CAM_EFFECT::NONE:
			return;
			break;

		case CAM_EFFECT::FADE_IN:
		{
			// 시간 누적값을 체크
			m_fCurTime += fDT;

			// 시간 넘어갔으면 효과 종료
			if (m_fEffectDuration <= m_fCurTime)
			{
				m_eEffect = CAM_EFFECT::NONE;
				return;
			}

			fRatio = 1 - m_fCurTime / m_fEffectDuration;

			break;
		}
	
		case CAM_EFFECT::FADE_OUT:
		{
			// 시간 누적값을 체크
			m_fCurTime += fDT;

			// 시간 넘어갔으면 효과 종료
			if (m_fEffectDuration <= m_fCurTime)
			{
				m_eEffect = CAM_EFFECT::NONE;
				return;
			}

			fRatio = m_fCurTime / m_fEffectDuration;

			break;
		}


	}
	
	int iWidth = (int)m_pVeilTex->Width();
	int iHeight = (int)m_pVeilTex->Height();

	BLENDFUNCTION bf = {};
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = 0;
	bf.SourceConstantAlpha = (int)(fRatio * 255);

	AlphaBlend(_dc
		, 0, 0, iWidth, iHeight
		, m_pVeilTex->GetDC()
		, 0, 0, iWidth, iHeight
		, bf);
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
