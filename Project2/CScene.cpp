#include "CScene.h"
#include "CObject.h"
#include "CSceneMgr.h"
#include "CTile.h"
#include "CResMgr.h"
#include "CPathMgr.h"
#include "CCore.h"
#include "CCamera.h"

CScene::CScene()
	: m_iTileX(0)
	, m_iTileY(0)
	, m_pPlayer(nullptr)
{
}

CScene::~CScene()
{
	// scene에 존재하던 모든 object를 메모리에서 제거함.
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{	
			// i번째 그룹의 j번 오브젝트를 힙메모리에서 제거해줌.
			delete m_arrObj[i][j];
		}

		// 각 벡터 메모리 제거는 벡터의 소멸자가 알아서 해준대..  ㅅㅂ 뭐냐?
		// 벡터의 요소(포인터)가 가리키던 객체는 내가 지워줘야 됨. 안그러면 힙에 남게 됨
	}

}


void CScene::update()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			// 데드 상태인 오브젝트는 update 제외
			if (m_arrObj[i][j]->IsDead()) continue;

			m_arrObj[i][j]->update();
		}
	}
}

// 예를 들면, Collider가 오브젝트를 따라가는 작업.
void CScene::finalupdate()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			m_arrObj[i][j]->finalupdate();
			// + 데드 상태인 오브젝트를 벡터에서 빼줌
		}
	}
}

void CScene::render(HDC _dc)
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		if (i == (UINT)GROUP_TYPE::TILE)
		{
			render_tile(_dc);
			continue;
		}

		vector<CObject*>::iterator iter = m_arrObj[i].begin();
		for (; iter != m_arrObj[i].end();)
		{
			// 데드 상태인 오브젝트는 render 제외
			if ((*iter)->IsDead())
			{
				iter = m_arrObj[i].erase(iter);
				continue;
			}
			(*iter)->render(_dc);
			++iter;
		}
	}
}

void CScene::render_tile(HDC _dc)
{
	vector<CObject*> vecTile = GetGroupObject(GROUP_TYPE::TILE);

	Vec2 vCamLook = CCamera::GetInst()->GetLookAt();
	Vec2 vResolution = CCore::GetInst()->GetResolution();
	Vec2 vLeftTop = vCamLook - vResolution / 2.f;
	
	int iTileSize = TILE_SIZE;

	int iLTCol = (int)vLeftTop.x / iTileSize;
	int iLTRow = (int)vLeftTop.y / iTileSize;
	int iLTIdx = m_iTileX * iLTRow + iLTCol;	// 카메라 좌상단 지점을 포함하는 타일의 인덱스

	int iClientWidth = (int)vResolution.x / iTileSize;	// 화면 상의 타일 가로 개수
	int iClientHeight = (int)vResolution.y / iTileSize;	// 화면 상의 타일 세로 개수

	for (int row = iLTRow; row <= iLTRow + iClientHeight; ++row)
	{
		for (int col = iLTCol; col <= iLTCol + iClientWidth; ++col)
		{
			if (col < 0 || col >= m_iTileX
				|| row < 0 || row >= m_iTileY)
				continue;

			int iIdx = m_iTileX * row + col;
			vecTile[iIdx]->render(_dc);
		}
	}


}

void CScene::SaveObject(CObject* _pObj, GROUP_TYPE _etype)
{
	_pObj->SetSceneAlive();
	CSceneMgr::GetInst()->SaveObject(_pObj, _etype);
}

void CScene::DeleteGroup(GROUP_TYPE _eTarget)
{
	//Safe_Delete_Vec<CObject*> (m_arrObj[(UINT)_eTarget]); // 템플릿 함수 호출의 정석, <typename>은 생략 가능
	vector<CObject*>& _vec = m_arrObj[(UINT)_eTarget];

	for (size_t i = 0; i < _vec.size(); ++i)
	{
		if (_vec[i] != nullptr && !_vec[i]->GetSceneAlive())
			delete _vec[i];
	}
	_vec.clear();
}

void CScene::DeleteAll()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		DeleteGroup((GROUP_TYPE)i);
	}
}

void CScene::CreateTile(UINT _iXCount, UINT _iYCount)
{
	DeleteGroup(GROUP_TYPE::TILE);

	m_iTileX = _iXCount;
	m_iTileY = _iYCount;

	CTexture* pTileTex = CResMgr::GetInst()->LoadTexture(L"Tile", L"texture\\tile.bmp");

	for (UINT i = 0; i < _iYCount; i++)
	{
		for (UINT j = 0; j < _iXCount; j++)
		{
			CTile* pTile = new CTile;
			pTile->SetPos(Vec2((float)j * TILE_SIZE, (float)i * TILE_SIZE));
			pTile->SetTexture(pTileTex);

			AddObject(pTile, GROUP_TYPE::TILE);
		}
	}
}


void CScene::LoadTile(const wstring _strRelativePath)
{
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	FILE* pFile = nullptr;

	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");
	// file open을 했는데도 여전히 nullptr -> 파일 열기 실패했다는 뜻.
	assert(pFile);

	UINT xCount = 0;
	UINT yCount = 0;

	fread(&xCount, sizeof(UINT), 1, pFile);
	fread(&yCount, sizeof(UINT), 1, pFile);

	// 불러온 개수에 맞게 EmptyTile 만들기.
	CreateTile(xCount, yCount);

	// 파일에 쓴 순서대로 데이터를 읽으면 됨!! 데이터 형식 상관없이 알맞게 읽을 수 있다.
	const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);

	for (size_t i = 0; i < vecTile.size(); ++i)
	{
		((CTile*)vecTile[i])->Load(pFile);
	}


	// 파일 닫기 (file stream 종료?)
	fclose(pFile);
}
