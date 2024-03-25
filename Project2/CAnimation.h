#pragma once

class CAnimator;
class CTexture;

struct tAnimFrm
{
	Vec2	vLT;		// 프레임의 좌상단 좌표
	Vec2	vSlice;		// 프레임을 자를 사이즈 영역
	float	fDuration;	// 프레임을 재생할 시간
};

class CAnimation
{
private:
	wstring				m_strName;
	CAnimator*			m_pAnimator;
	CTexture*			m_pTex;		// Animation이 사용하는 텍스쳐
	vector<tAnimFrm>	m_vecFrm;	// 텍스쳐에서 프레임의 정보

public:
	const wstring& GetName() { return m_strName; }

private:
	void SetName(const wstring& _strName) { m_strName = _strName; }

public:
	void update();
	void render(HDC _dc);

	void Create(CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount);

public:
	CAnimation();
	~CAnimation();

	friend class CAnimator;
};

