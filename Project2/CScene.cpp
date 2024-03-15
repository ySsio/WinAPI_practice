#include "pch.h"
#include "CScene.h"
#include "CObject.h"

CScene::CScene()
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