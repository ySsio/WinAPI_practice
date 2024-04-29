#pragma once

struct tEvent
{
	EVENT_TYPE		eEven;
	DWORD_PTR		lParam;	// DWORD_PTR : �÷����� ���������� ����. 4byte/8byte
	DWORD_PTR		wParam;
};

class CEventMgr
{
	SINGLETON(CEventMgr);

private:
	vector<tEvent>		m_vecEvent;
	vector<CObject*>	m_vecDead;

public:
	void update();

private:
	void Execute(const tEvent& _eve);

public:
	void AddEvent(const tEvent& _eve); 
};

// ���� ���� ���� �ִ� �̺�Ʈ��
// ����
// �� ����

// �� ������Ʈ�� �Ͼ�� �ϵ��� ��� ���ð� �뿡 �Ͼ�� ���̶�� ����
// �ڵ� ��ü�� ���������� ���� �ֱ� ������ �� �����ӿ��� ������ �Ͼ��
// �� �ڵ尡 ����Ǳ� ������ ����ִٰ� �ν��ϴٰ� ���� �ڵ� ���Ŀ� �۵��ϴ� �ڵ忡����
// ��ü�� �����Ǿ��ٰ� �ν��ϴ� ���� �߻�
// ���� event�� frame ������ ����ȭ ������� ��.!!!
// => event frame sync = ����ó��
// �� �׿��ּ��� ��û => ����ó�� �ؼ� ������ �����ӿ� ��ο��� ����
// => ���� �����ӿ����� ��ΰ� ��ü ������ ������ �� ����.
// Event Manager. �� ���� ������Ʈ ���� �߻��ϴ� �̺�Ʈ ����
// �� ������ ��� ����� �� �̺�Ʈ ó��
// ���� �����ӿ��� ��� ���ÿ� ���� ����.