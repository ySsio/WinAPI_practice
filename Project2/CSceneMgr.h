#pragma once

class CScene;
class CEventMgr;
enum class GROUP_TYPE;

class CSceneMgr
{
	SINGLETON(CSceneMgr);

private:
	map<CObject*, GROUP_TYPE>	m_arrObjSaved;		// ���� ������ ���� ������ �츱 ������Ʈ
	CScene*		m_arrScene[(UINT)SCENE_TYPE::END];	// ��� �� ���
	CScene*		m_pCurScene;						// ���� ��
	

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
	void ChangeScene(SCENE_TYPE _eNext);	// eventmgr������ ȣ���� �� �ֵ��� private���� ����

	friend class CEventMgr;		// # friend class�� ���漱�� �ʿ� ����?
};

