#include "pch.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CTexture.h"

CAnimation::CAnimation()
	: m_pAnimator(nullptr)
{
}

CAnimation::~CAnimation()
{
}


void CAnimation::update()
{
}

void CAnimation::render(HDC _dc)
{
}

void CAnimation::Create(CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount)
{
	m_pTex = _pTex;
	tAnimFrm frm = {};
	for (int i = 0; i < _iFrameCount; ++i)
	{
		frm.vLT = _vLT + _vStep * i;
		frm.vSlice = _vSliceSize;
		frm.fDuration = _fDuration;

		m_vecFrm.push_back(frm);
	}
}
