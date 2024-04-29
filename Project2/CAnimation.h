#pragma once
#include "global.h"
class CAnimator;
class CTexture;

struct tAnimFrm
{
	Vec2	vLT;		// 프레임의 좌상단 좌표
	Vec2	vSlice;		// 프레임을 자를 사이즈 영역
	Vec2	vOffset;
	float	fDuration;	// 프레임을 재생할 시간
};

class CAnimation
{
private:
	wstring				m_strName;
	CAnimator*			m_pAnimator;
	CTexture*			m_pTex;		// Animation이 사용하는 텍스쳐
	vector<tAnimFrm>	m_vecFrm;	// 텍스쳐에서 프레임의 정보
	int					m_iCurFrm;	// 현재 몇 프레임인지
	float				m_fAccTime;	// 시간 흘러가는거 체크할 누적 변수

	bool				m_bFinish;	// 애니메이션이 한 사이클이 끝났는지

public:
	const wstring& GetName() { return m_strName; }
	bool IsFinish() { return m_bFinish; }
	void SetFrame(int _iFrameIdx)
	{
		m_bFinish = false;
		m_iCurFrm = _iFrameIdx;
		m_fAccTime = 0.f;
	}

	// 특정 프레임 얻어오는 함수, 수정 가능하도록 레퍼런스 반환
	tAnimFrm& GetFrame(int _iIdx) { return m_vecFrm[_iIdx]; }
	int GetMaxFrame() { return (int)m_vecFrm.size(); }

private:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	

public:
	void update();
	void render(HDC _dc);

	void Create(CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount);

public:
	void Save(const wstring& _strRelativePath);
	void Load(const wstring& _strRelativePath);

public:
	CAnimation();
	~CAnimation();

	friend class CAnimator;
};

