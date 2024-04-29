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
	, m_pVeilTex(nullptr)
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

	if (m_listCamEffect.empty())
		return;

	tCamEffect& effect = m_listCamEffect.front();

	// 시간 누적값을 체크
	effect.fCurTime += fDT;

	switch (effect.eEffect)
	{
		case CAM_EFFECT::FADE_IN:
		{
			fRatio = 1 - effect.fCurTime / effect.fDuration;
			break;
		}
	
		case CAM_EFFECT::FADE_OUT:
		{
			fRatio = effect.fCurTime / effect.fDuration;
			break;
		}
	}

	if (fRatio < 0.f)
	{
		fRatio = 0.f;
	}
	else if (fRatio > 1.f)
	{
		fRatio = 1.f;
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

	// 시간 넘어갔으면 효과 종료
	if (effect.fDuration <= effect.fCurTime)
	{
		m_listCamEffect.pop_front();
	}

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
