#pragma once
#include "global.h"
// ���漱���� ��� ������ Ÿ���� ����� �� �ִ�. (������Ÿ�� = �ּҴ� ũ�Ⱑ �����̴ϱ�)
// ������ �ӵ��� ���� x. ��� ���������� CObject�� ������� ������ ���⿡���� �װſ� ���� �����Ϸ��� ��Ȯ���� �ʿ䰡 ����.. ? ������� ������ �����ϰ��� ���漱�� ���.
class CObject;

class CScene
{
private:
	// �پ��� ������ ������Ʈ�� �ְ� ���� CObject*�� �޾Ƽ� ��Ʈ��. ������. �ڽ�Ŭ���� �����͸� �θ�Ŭ���� ������ Ÿ������ ���� �� ����.
	// ������Ʈ ���� ���Ͱ� �׷츶�� �����ؾ� ��. ����Ÿ���� �޴� ����Ʈ�� ����, ũ��� �׷��� ������ ����. �׷��� pch.h�� ���ǵǾ� ����.
	vector<CObject*>	m_arrObj[(UINT)GROUP_TYPE::END];	// ���� �迭 ���� ��. []�� ����ؼ� [] ���� ũ�⸸ŭ �迭�� �����, �� �迭 �ȿ� ���Ͱ� ����. �� ���Ͱ� �迭�� 32�� �ִ� ����
	wstring				m_strName;	// Scene �̸�

public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	virtual void update();
	virtual void finalupdate();		// ������ �۾� ������Ʈ.
	virtual void render(HDC _dc);

	// ���� �����Լ� pure virtual function => �ڽ� Ŭ�������� ���� ���ϸ� ����
	// �����ϸ� �߻�Ŭ���� => �θ�Ŭ���� ��ü ���� �Ұ���
	virtual void Enter() = 0;	// ����
	virtual void Exit() = 0;	// Ż��

public:
	// Ŭ���� �Լ� ����� �����ϸ� �ڵ����� inline ó��. �Լ� ȣ�� ��� x �ش� ���ÿ��� ó����.
	void AddObject(CObject* _pObj, GROUP_TYPE _etype)
	{
		m_arrObj[(UINT)_etype].push_back(_pObj);
		return;
	}
	void SaveObject(CObject* _pObj, GROUP_TYPE _etype);
	
	const vector<CObject*>& GetGroupObject(GROUP_TYPE _etype) { return m_arrObj[(UINT)_etype]; }
	void DeleteGroup(GROUP_TYPE _eTarget);
	void DeleteAll();

	const vector<CObject*> GetArrObj(GROUP_TYPE _etype) { return m_arrObj[(UINT)_etype]; }


public:
	CScene();
	virtual ~CScene();
};

