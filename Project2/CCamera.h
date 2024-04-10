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

class CCamera
{
	SINGLETON(CCamera);

private:
	Vec2		m_vLookAt;		// ī�޶��� �߽� ��ġ, �����ϴ� ���� ��ġ
	Vec2		m_vCurLookAt;	// ���� ��ġ�� ���� ��ġ ������ ���� ��ġ
	Vec2		m_vPrevLookAt;	// ī�޶� ���� ���� ������ ��ġ

	CObject*	m_pTargetObj;	// ī�޶� �ٶ󺸴� Ÿ��
	Vec2		m_vDiff;		// �ػ� �߽���ġ�� ī�޶� LookAt���� ���� ��

	float		m_fTime;		// Ÿ���� ���󰡴µ� �ɸ��� �ð�
	float		m_fSpeed;		// Ÿ�� ���󰡴� �ӵ�
	float		m_fAccTime;		// ���� �ð�

	CAM_EFFECT	m_eEffect;		// ī�޶� ȿ��
	CTexture*	m_pVeilTex;		// ī�޶� ȿ���� ���� ������ �ؽ���
	float		m_fEffectDuration;	// ī�޶� ȿ�� ���� �ð�
	float		m_fCurTime;		// ī�޶� ȿ�� ���� ����� �ð�

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
		m_eEffect = CAM_EFFECT::FADE_IN;
		m_fEffectDuration = _fDuration;
	}

	void FadeOut(float _fDuration)
	{
		assert(_fDuration != 0);
		m_eEffect = CAM_EFFECT::FADE_OUT;
		m_fEffectDuration = _fDuration;
	}

public:
	void init();
	void update();
	void render(HDC _dc);

private:
	void CalDiff();
};

