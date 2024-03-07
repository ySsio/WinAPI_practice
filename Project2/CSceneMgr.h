#pragma once

class CScene;

class CSceneMgr
{
	SINGLETON(CSceneMgr);

private:
	CScene*		m_arrScene[(UINT)SCENE_TYPE::END];	// ��� �� ��� # ���� �� �� ���� �� �𸣴µ� �� �迭�� ����?
	CScene*		m_pCurScene;						// ���� ��

public:
	void init();
	void update();
	void render(HDC _dc);
};

