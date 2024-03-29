#include "global.h"
#include "CTile.h"
#include "CTexture.h"

CTile::CTile()
	: m_pTileTex(nullptr)
	, m_iImgIdx(0)
{
	SetScale(Vec2(TILE_SIZE,TILE_SIZE));
}

CTile::~CTile()
{
}

void CTile::update()
{
}

void CTile::render(HDC _dc)
{
	if (m_pTileTex == nullptr)
		return;

	UINT iWidth = m_pTileTex->Width();
	UINT iHeight = m_pTileTex->Height();

	UINT iMaxCol = iWidth / TILE_SIZE;	// 타일 열 개수
	UINT iMaxRow = iHeight / TILE_SIZE; // 타일 행 개수

	UINT iCurRow = (UINT)m_iImgIdx / iMaxCol;
	UINT iCurCol = (UINT)m_iImgIdx % iMaxCol;

	// 텍스처 범위를 벗어난 인덱스
	if (iMaxRow <= iCurRow)
		assert(nullptr);

	Vec2 vScale = GetScale();

	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(GetPos());


	BitBlt(_dc
		, (int)vRenderPos.x
		, (int)vRenderPos.y
		, (int)vScale.x
		, (int)vScale.y
		, m_pTileTex->GetDC()
		, (int)(iCurCol * vScale.x)
		, (int)(iCurRow * vScale.y)
		, SRCCOPY);


}