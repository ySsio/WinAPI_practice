#pragma once
#include "global.h"
class CAnimator;
class CTexture;

struct tAnimFrm
{
	Vec2	vLT;		// �������� �»�� ��ǥ
	Vec2	vSlice;		// �������� �ڸ� ������ ����
	Vec2	vOffset;
	float	fDuration;	// �������� ����� �ð�
};

class CAnimation
{
private:
	wstring				m_strName;
	CAnimator*			m_pAnimator;
	CTexture*			m_pTex;		// Animation�� ����ϴ� �ؽ���
	vector<tAnimFrm>	m_vecFrm;	// �ؽ��Ŀ��� �������� ����
	int					m_iCurFrm;	// ���� �� ����������
	float				m_fAccTime;	// �ð� �귯���°� üũ�� ���� ����

	bool				m_bFinish;	// �ִϸ��̼��� �� ����Ŭ�� ��������

public:
	const wstring& GetName() { return m_strName; }
	bool IsFinish() { return m_bFinish; }
	void SetFrame(int _iFrameIdx)
	{
		m_bFinish = false;
		m_iCurFrm = _iFrameIdx;
		m_fAccTime = 0.f;
	}

	// Ư�� ������ ������ �Լ�, ���� �����ϵ��� ���۷��� ��ȯ
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

