#include "pch.h"
#include "CScene.h"
#include "CObject.h"



CScene::CScene()
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

void CScene::DeleteGroup(GROUP_TYPE _eTarget)
{
	Safe_Delete_Vec<CObject*> (m_arrObj[(UINT)_eTarget]); // ���ø� �Լ� ȣ���� ����, <typename>�� ���� ����
}

void CScene::DeleteAll()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		DeleteGroup((GROUP_TYPE)i);
	}
}
