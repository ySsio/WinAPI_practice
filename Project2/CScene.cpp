#include "CScene.h"
#include "CObject.h"
#include "CSceneMgr.h"
#include "CTile.h"
#include "CResMgr.h"

CScene::CScene()
	: m_iTileX(0)
	, m_iTileY(0)
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
