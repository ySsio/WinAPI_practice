#pragma once

class CObject;
class CTexture;

enum class CAM_EFFECT
{
	FADE_IN,
	FADE_OUT,
	NONE,
	END,
};

struct tCamEffect
{
	CAM_EFFECT	eEffect;		// ī�޶� ȿ��
	float		fDuration;	// ī�޶� ȿ�� ���� �ð�
	float		fCurTime;		// ī�޶� ȿ�� ���� ����� �ð�
};

class CCamera
{
	SINGLETON(CCamera);

private:
	Vec2				m_vLookAt;		// ī�޶��� �߽� ��ġ, �����ϴ� ���� ��ġ
	Vec2				m_vCurLookAt;	// ���� ��ġ�� ���� ��ġ ������ ���� ��ġ
	Vec2				m_vPrevLookAt;	// ī�޶� ���� ���� ������ ��ġ

	CObject*			m_pTargetObj;	// ī�޶� �ٶ󺸴� Ÿ��
	Vec2				m_vDiff;		// �ػ� �߽���ġ�� ī�޶� LookAt���� ���� ��

	float				m_fTime;		// Ÿ���� ���󰡴µ� �ɸ��� �ð�
	float				m_fSpeed;		// Ÿ�� ���󰡴� �ӵ�
	float				m_fAccTime;		// ���� �ð�

	list<tCamEffect>	m_listCamEffect;
	CTexture*			m_pVeilTex;		// ī�޶� ȿ���� ���� ������ �ؽ���

public:
	void SetLookAt(Vec2 _vLook) {
		m_vLookAt = _vLook; 
		float fMoveDist = (m_vLookAt - m_vPrevLookAt).Length();
		m_fSpeed = fMoveDist / m_fTime;
		m_fAccTime = 0.f;
	}
	void SetTarget(CObject* _pTarget) { m_pTargetObj = _pTarget; }
	Vec2 GetLookAt() { return m_vCurLookAt; }
	Vec2 GetRenderPos(Vec2 _vObjPos) { return _vObjPos - m_vDiff; }
	Vec2 GetRealPos(Vec2 _vRenderPos) { return _vRenderPos + m_vDiff; }

	void FadeIn(float _fDuration)
	{
		assert(_fDuration != 0);
		tCamEffect ef = {};
		ef.eEffect = CAM_EFFECT::FADE_IN;
		ef.fDuration = _fDuration;
		ef.fCurTime = 0;
		m_listCamEffect.push_back(ef);
	}

	void FadeOut(float _fDuration)
	{
		assert(_fDuration != 0);
		tCamEffect ef = {};
		ef.eEffect = CAM_EFFECT::FADE_OUT;
		ef.fDuration = _fDuration;
		ef.fCurTime = 0;
		m_listCamEffect.push_back(ef);
	}

public:
	void init();
	void update();
	void render(HDC _dc);

private:
	void CalDiff();
};

