#pragma once

class CScene;

class CSceneMgr
{
	SINGLETON(CSceneMgr);

private:
	CScene*		m_arrScene[(UINT)SCENE_TYPE::END];	// 모든 씬 목록 # 씬이 몇 개 있을 줄 모르는데 왜 배열로 하지?
	CScene*		m_pCurScene;						// 현재 씬

public:
	void init();
	void update();
	void render(HDC _dc);
};

