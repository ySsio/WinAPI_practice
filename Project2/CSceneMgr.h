#pragma once

class CScene;
class CEventMgr;

class CSceneMgr
{
	SINGLETON(CSceneMgr);

private:
	CScene*		m_arrScene[(UINT)SCENE_TYPE::END];	// 모든 씬 목록
	CScene*		m_pCurScene;						// 현재 씬

public:
	void init();
	void update();
	void render(HDC _dc);

public:
	CScene* GetCurScene() { return m_pCurScene; }

private:
	void ChangeScene(SCENE_TYPE _eNext);	// eventmgr에서만 호출할 수 있도록 private으로 변경

	friend class CEventMgr;		// # friend class는 전방선언 필요 없나?
};

