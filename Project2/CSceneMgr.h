#pragma once

class CScene;
class CEventMgr;
enum class GROUP_TYPE;

class CSceneMgr
{
	SINGLETON(CSceneMgr);

private:
	map<CObject*, GROUP_TYPE>	m_arrObjSaved;		// 이전 씬에서 다음 씬까지 살릴 오브젝트
	CScene*		m_arrScene[(UINT)SCENE_TYPE::END];	// 모든 씬 목록
	CScene*		m_pCurScene;						// 현재 씬
	

public:
	void init();
	void update();
	void render(HDC _dc);

public:
	CScene* GetCurScene() { return m_pCurScene; }

	void SaveObject(CObject* _pObj, GROUP_TYPE _etype);
	void LoadObject();
	void ClearObject();

private:
	void ChangeScene(SCENE_TYPE _eNext);	// eventmgr에서만 호출할 수 있도록 private으로 변경

	friend class CEventMgr;		// # friend class는 전방선언 필요 없나?
};

