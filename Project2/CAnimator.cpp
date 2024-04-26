#include "CAnimator.h"
#include "CAnimation.h"
#include "assert.h"

CAnimator::CAnimator()
	: m_pCurAnim(nullptr)
	, m_pOwner(nullptr)
	, m_bRepeat(false)
{
}

CAnimator::CAnimator(const CAnimator& _other)
	: m_pCurAnim(_other.m_pCurAnim)
	, m_pOwner(nullptr)
	, m_bRepeat(_other.m_bRepeat)
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

void CAnimator::LoadAnimation(const wstring& _strRelativePath)
{
	CAnimation* anim = new CAnimation;
	anim->Load(_strRelativePath);
	anim->m_pAnimator = this;
	m_mapAnim.emplace(anim->GetName(),anim);
}

void CAnimator::Play(const wstring& _strName, bool _bRepeat)
{
	m_pCurAnim = FindAnimation(_strName);
	m_bRepeat = _bRepeat;
}



void CAnimator::update()
{
	
}

void CAnimator::finalupdate()
{
	if (m_pCurAnim != nullptr)
	{
		m_pCurAnim->update();	// 현재 진행중인 애니메이션 업데이트 호출
		if (m_bRepeat && m_pCurAnim->IsFinish())
		{
			m_pCurAnim->SetFrame(0);
		}
	}
}

void CAnimator::render(HDC _dc)
{
	if (m_pCurAnim != nullptr)
		m_pCurAnim->render(_dc);	// 현재 진행중인 애니메이션 render 호출

}

