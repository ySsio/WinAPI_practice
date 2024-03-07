#pragma once

// ���漱���� ��� ������ Ÿ���� ����� �� �ִ�. (������Ÿ�� = �ּҴ� ũ�Ⱑ �����̴ϱ�)
// ������ �ӵ��� ���� x. ��� ���������� CObject�� ������� ������ ���⿡���� �װſ� ���� �����Ϸ��� ��Ȯ���� �ʿ䰡 ����.. ? ������� ������ �����ϰ��� ���漱�� ���.
class CObject;

class CScene
{
private:
	// �پ��� ������ ������Ʈ�� �ְ� ���� CObject*�� �޾Ƽ� ��Ʈ��. ������. �ڽ�Ŭ���� �����͸� �θ�Ŭ���� ������ Ÿ������ ���� �� ����.
	// ������Ʈ ���� ���Ͱ� �׷츶�� �����ؾ� ��. ����Ÿ���� �޴� ����Ʈ�� ����, ũ��� �׷��� ������ ����. �׷��� pch.h�� ���ǵǾ� ����.
	vector<CObject*>	m_arrObj[(UINT)GROUP_TYPE::END];
	wstring				m_strName;	// Scene �̸�

public :
	void SetName(const wstring& _strName) { m_strName = _strName;}
	const wstring& GetName() { return m_strName; }

	void update();
	void render(HDC _dc);

	// ���� �����Լ� pure virtual function => �ڽ� Ŭ�������� ���� ���ϸ� ����
	// �����ϸ� �߻�Ŭ���� => �θ�Ŭ���� ��ü ���� �Ұ���
	virtual void Enter() = 0;	// ����
	virtual void Exit() = 0;	// Ż��

protected:
	// Ŭ���� �Լ� ����� �����ϸ� �ڵ����� inline ó��. �Լ� ȣ�� ��� x �ش� ���ÿ��� ó����.
	void AddObject(CObject* _pObj, GROUP_TYPE _etype)
	{
		m_arrObj[(UINT)_etype].push_back(_pObj);
		return;
	}

public:
	CScene();
	virtual ~CScene();
};

