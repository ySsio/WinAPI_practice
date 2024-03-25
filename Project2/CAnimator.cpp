#include "pch.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "assert.h"

CAnimator::CAnimator()
	: m_pCurAnim(nullptr)
	, m_pOwner(nullptr)
{
}

CAnimator::CAnimator(const CAnimator& _other)
{
}

CAnimator::~CAnimator()
{
	Safe_Delete_Map<wstring, CAnimation*>(m_mapAnim);
}


void CAnimator::CreateAnimation(const wstring& _strName, CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount)
{
	CAnimation* pAnim = FindAnimation(_strName);
	assert(pAnim == nullptr);

	pAnim = new CAnimation;
	
	
	pAnim->SetName(_strName);
	pAnim->m_pAnimator = this;
	pAnim->Create(_pTex,_vLT,_vSliceSize,_vStep,_fDuration,_iFrameCount);

	//m_mapAnim[_strName] = pAnim;
	m_mapAnim.insert(make_pair(_strName, pAnim));
}

CAnimation* CAnimator::FindAnimation(const wstring& _strName)
{
	map<wstring, CAnimation*>::iterator iter = m_mapAnim.find(_strName);
	if (iter == m_mapAnim.end())
		return nullptr;

	return iter->second;
}

void CAnimator::Play()
{
}

void CAnimator::update()
{
	if (m_pCurAnim != nullptr)
		m_pCurAnim->update();	// ���� �������� �ִϸ��̼� ������Ʈ ȣ��

}

void CAnimator::render(HDC _dc)
{
	if (m_pCurAnim != nullptr)
		m_pCurAnim->render(_dc);	// ���� �������� �ִϸ��̼� render ȣ��

}
