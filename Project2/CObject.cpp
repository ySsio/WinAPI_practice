#include "pch.h"
#include "CObject.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"


CObject::CObject()
	: m_vPos{}
	, m_vScale{}
{
}

CObject::~CObject()
{
}

void CObject::render(HDC _dc)
{
	Rectangle(_dc
		, (int)(GetPos().x - GetScale().x / 2)
		, (int)(GetPos().y - GetScale().y / 2)
		, (int)(GetPos().x + GetScale().x / 2)
		, (int)(GetPos().y + GetScale().y / 2));
}
