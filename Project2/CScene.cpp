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
		}
	}
}

void CScene::render(HDC _dc)
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			m_arrObj[i][j]->render(_dc);
		}
	}
}