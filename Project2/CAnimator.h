#pragma once

class CObject;
class CAnimation;
class CTexture;

class CAnimator
{
private:
	map<wstring, CAnimation*>	m_mapAnim;	// 모든 애니메이션을 map으로 관리
	CAnimation*					m_pCurAnim;	// 현재 재생중인 Animation
	CObject*					m_pOwner;	// Animator 소유 오브젝트


public:
	void CreateAnimation(const wstring& _strName, CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, UINT _iFrameCount);	// 애니메이션을 만들 텍스처 파일, 시작 위치 (가로로 1줄이 한 애니메이션임), 간격(한 장면의 사이즈), 간격..?, 프레임 수
	CAnimation*  FindAnimation(const wstring& _strName);
	void Play();

	

	void update();
	void render(HDC _dc);

public:
	CAnimator();
	CAnimator(const CAnimator& _other);
	~CAnimator();

	friend class CObject;
};

