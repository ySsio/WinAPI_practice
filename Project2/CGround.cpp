#include "CGround.h"
#include "CCollider.h"
#include "CCamera.h"
#include "CGravity.h"

CGround::CGround()
{
	CreateCollider();
}

CGround::~CGround()
{
}

void CGround::start()
{
	GetCollider()->SetScale(GetScale());
}

void CGround::update()
{

}

void CGround::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"Player")
	{
		pOtherObj->GetGravity()->SetGround(true);

		Vec2 vColPos = _pOther->GetFinalPos();
		Vec2 vColScale = _pOther->GetScale();

		Vec2 vPos = GetCollider()->GetFinalPos();
		Vec2 vScale = GetCollider()->GetScale();

		float fLen = abs(vColPos.y - vPos.y);
		float depth = (vColScale.y / 2.f + vScale.y / 2.f) - fLen;

		if (depth > 0)
		{
			Vec2 vObjPos = pOtherObj->GetPos();
			vObjPos.y -= depth-1;
			pOtherObj->SetPos(vObjPos);
		}
	}
}

void CGround::OnCollision(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"Player")
	{
		pOtherObj->GetGravity()->SetGround(true);

		Vec2 vColPos = _pOther->GetFinalPos();
		Vec2 vColScale = _pOther->GetScale();

		Vec2 vPos = GetCollider()->GetFinalPos();
		Vec2 vScale = GetCollider()->GetScale();

		float fLen = abs(vColPos.y - vPos.y);
		float depth = (vColScale.y / 2.f + vScale.y / 2.f) - fLen;

		if (depth > 0)
		{
			Vec2 vObjPos = pOtherObj->GetPos();
			vObjPos.y -= depth-1;
			pOtherObj->SetPos(vObjPos);
		}
	}
}

void CGround::OnCollisionExit(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	pOtherObj->GetGravity()->SetGround(false);
}

void CGround::render(HDC _dc)
{
	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 vScale = GetScale();

	Rectangle(_dc
		, (int)(vPos.x - vScale.x / 2.f)
		, (int)(vPos.y - vScale.y / 2.f)
		, (int)(vPos.x + vScale.x / 2.f)
		, (int)(vPos.y + vScale.y / 2.f));
}


