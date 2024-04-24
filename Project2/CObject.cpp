#include "CObject.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CTexture.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CRigidBody.h"
#include "CGravity.h"

CObject::CObject()
	: m_vPos{}
	, m_vScale{}
	, m_pTex(nullptr)
	, m_pCollider(nullptr)
	, m_pAnimator(nullptr)
	, m_pRigidBody(nullptr)
	, m_pGravity(nullptr)
	, m_bAlive(true)
	, m_bSceneAlive(false)
{
}

CObject::CObject(const CObject& _origin)
	: m_strName(_origin.m_strName)
	, m_vPos(_origin.m_vPos)
	, m_vScale(_origin.m_vScale)
	, m_pCollider(nullptr)
	, m_pAnimator(nullptr)
	, m_pRigidBody(nullptr)
	, m_pGravity(nullptr)
	, m_bAlive(true)
	, m_bSceneAlive(false)
	, m_pTex(_origin.m_pTex)
{
	if (_origin.m_pCollider)
	{
		m_pCollider = new CCollider(*_origin.m_pCollider); // 콜라이더 복사생성자 ㄷ
		m_pCollider->m_pOwner = this;
	}

	if (_origin.m_pAnimator)
	{
		m_pAnimator = new CAnimator(*_origin.m_pAnimator); // 콜라이더 복사생성자 ㄷ
		m_pAnimator->m_pOwner = this;
	}

	if (_origin.m_pRigidBody)
	{
		m_pRigidBody = new CRigidBody(*_origin.m_pRigidBody); // 콜라이더 복사생성자 ㄷ
		m_pRigidBody->m_pOwner = this;
	}

	if (_origin.m_pGravity)
	{
		m_pGravity = new CGravity(*_origin.m_pGravity); // 콜라이더 복사생성자 ㄷ
		m_pGravity->m_pOwner = this;
	}
}

CObject::~CObject()
{
	if (m_pCollider != nullptr)
		delete m_pCollider;

	if (m_pAnimator != nullptr)
		delete m_pAnimator;

	if (m_pRigidBody != nullptr)
		delete m_pRigidBody;

	if (m_pGravity != nullptr)
		delete m_pGravity;
}

void CObject::SetSceneAlive()
{
	m_bSceneAlive = true;
}

bool CObject::GetSceneAlive()
{
	return m_bSceneAlive;
}

void CObject::CreateCollider()
{
	m_pCollider = new CCollider;
	m_pCollider->m_pOwner = this;
}

void CObject::CreateAnimator()
{
	m_pAnimator = new CAnimator;
	m_pAnimator->m_pOwner = this;
}

void CObject::CreateRigidBody()
{
	m_pRigidBody = new CRigidBody;
	m_pRigidBody->m_pOwner = this;
}

void CObject::CreateGravity()
{
	m_pGravity = new CGravity;
	m_pGravity->m_pOwner = this;
}

void CObject::finalupdate()
{
	if (m_pCollider)
		m_pCollider->finalupdate();

	if (m_pAnimator)
		m_pAnimator->finalupdate();

	// Rigidbody에 선행해서 업데이트
	if (m_pGravity)
		m_pGravity->finalupdate();

	if (m_pRigidBody)
		m_pRigidBody->finalupdate();
}

void CObject::render(HDC _dc)
{
	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(m_vPos);

	// width/ height은 당연히 양수니까 UINT였는데 좌표는 음수 될 수 있으니까 int로 변환
	int iWidth = (int)GetTexture()->Width();
	int iHeight = (int)GetTexture()->Height();

	Vec2 vPos = GetPos();

	TransparentBlt(_dc
		, (int)(vRenderPos.x - (float)iWidth / 2)
		, (int)(vRenderPos.y - (float)iHeight / 2)
		, iWidth, iHeight
		, GetTexture()->GetDC()
		, 0, 0, iWidth, iHeight
		, RGB(255, 0, 255));

	// 컴포넌트 렌더
	component_render(_dc);
}

void CObject::component_render(HDC _dc)
{
	if (m_pAnimator != nullptr)
		m_pAnimator->render(_dc);

	if (m_pCollider != nullptr)
		m_pCollider->render(_dc);
}
