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

void CAnimation::Create(CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, UINT _iFrameCount)
{

}
