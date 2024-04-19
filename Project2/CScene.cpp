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
	// scene�� �����ϴ� ��� object�� �޸𸮿��� ������.
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{	
			// i��° �׷��� j�� ������Ʈ�� ���޸𸮿��� ��������.
			delete m_arrObj[i][j];
		}

		// �� ���� �޸� ���Ŵ� ������ �Ҹ��ڰ� �˾Ƽ� ���ش�..  ���� ����?
		// ������ ���(������)�� ����Ű�� ��ü�� ���� ������� ��. �ȱ׷��� ���� ���� ��
	}

}


void CScene::update()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			// ���� ������ ������Ʈ�� update ����
			if (m_arrObj[i][j]->IsDead()) continue;

			m_arrObj[i][j]->update();
		}
	}
}

// ���� ���, Collider�� ������Ʈ�� ���󰡴� �۾�.
void CScene::finalupdate()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			m_arrObj[i][j]->finalupdate();
			// + ���� ������ ������Ʈ�� ���Ϳ��� ����
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
			// ���� ������ ������Ʈ�� render ����
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
	int iLTIdx = m_iTileX * iLTRow + iLTCol;	// ī�޶� �»�� ������ �����ϴ� Ÿ���� �ε���

	int iClientWidth = (int)vResolution.x / iTileSize;	// ȭ�� ���� Ÿ�� ���� ����
	int iClientHeight = (int)vResolution.y / iTileSize;	// ȭ�� ���� Ÿ�� ���� ����

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
	//Safe_Delete_Vec<CObject*> (m_arrObj[(UINT)_eTarget]); // ���ø� �Լ� ȣ���� ����, <typename>�� ���� ����
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
	// file open�� �ߴµ��� ������ nullptr -> ���� ���� �����ߴٴ� ��.
	assert(pFile);

	UINT xCount = 0;
	UINT yCount = 0;

	fread(&xCount, sizeof(UINT), 1, pFile);
	fread(&yCount, sizeof(UINT), 1, pFile);

	// �ҷ��� ������ �°� EmptyTile �����.
	CreateTile(xCount, yCount);

	// ���Ͽ� �� ������� �����͸� ������ ��!! ������ ���� ������� �˸°� ���� �� �ִ�.
	const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);

	for (size_t i = 0; i < vecTile.size(); ++i)
	{
		((CTile*)vecTile[i])->Load(pFile);
	}


	// ���� �ݱ� (file stream ����?)
	fclose(pFile);
}
