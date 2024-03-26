#pragma once

class CObject;
class CAnimation;
class CTexture;

class CAnimator
{
private:
	map<wstring, CAnimation*>	m_mapAnim;	// ��� �ִϸ��̼��� map���� ����
	CAnimation*					m_pCurAnim;	// ���� ������� Animation
	CObject*					m_pOwner;	// Animator ���� ������Ʈ
	bool						m_bRepeat;

public:
	void CreateAnimation(const wstring& _strName, CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount);	// �ִϸ��̼��� ���� �ؽ�ó ����, ���� ��ġ (���η� 1���� �� �ִϸ��̼���), ����(�� ����� ������), ����..?, ������ ��
	CAnimation*  FindAnimation(const wstring& _strName);
	void Play(const wstring& _strName, bool _bRepeat);

	CObject* GetObj() { return m_pOwner; }

	void update();
	void render(HDC _dc);

public:
	CAnimator();
	CAnimator(const CAnimator& _other);
	~CAnimator();

	friend class CObject;
};

