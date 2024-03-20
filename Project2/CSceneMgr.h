#pragma once

class CScene;
class CEventMgr;

class CSceneMgr
{
	SINGLETON(CSceneMgr);

private:
	CScene*		m_arrScene[(UINT)SCENE_TYPE::END];	// ��� �� ���
	CScene*		m_pCurScene;						// ���� ��

public:
	void init();
	void update();
	void render(HDC _dc);

public:
	CScene* GetCurScene() { return m_pCurScene; }

private:
	void ChangeScene(SCENE_TYPE _eNext);	// eventmgr������ ȣ���� �� �ֵ��� private���� ����

	friend class CEventMgr;		// # friend class�� ���漱�� �ʿ� ����?
};

