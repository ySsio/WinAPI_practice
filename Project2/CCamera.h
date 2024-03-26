#pragma once

class CObject;


class CCamera
{
	SINGLETON(CCamera);

private:
	Vec2		m_vLookAt;		// 카메라의 중심 위치
	CObject*	m_pTargetObj;	// 카메라가 바라보는 타겟

	Vec2		m_vDiff;		// 해상도 중심위치와 카메라 LookAt간의 차이 값
	

public:
	void SetLookAt(Vec2 _vLook) { m_vLookAt = _vLook; }
	void SetTarget(CObject* _pTarget) { m_pTargetObj = _pTarget; }
	Vec2 GetRenderPos(Vec2 _vObjPos) { return _vObjPos - m_vDiff; }

public:
	void update();

private:
	void CalDiff();
};

