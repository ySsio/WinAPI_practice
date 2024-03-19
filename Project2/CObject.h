#pragma once

class CTexture;
class CCollider;
class CEventMgr;

// ��ü, �߻�Ŭ����
class CObject
{
private:
	wstring		m_strName;

	Vec2		m_vPos;
	Vec2		m_vScale;

	CCollider*	m_pCollider;

	bool		m_bAlive;

private:
	CTexture* m_pTex;

public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }
	void SetTexture(CTexture* _pTex) { m_pTex = _pTex; }
	void SetName(const wstring& _strName) { m_strName = _strName; }

	Vec2 GetPos() { return m_vPos; }
	Vec2 GetScale() { return m_vScale; }
	CTexture* GetTexture() { return m_pTex; }
	const wstring& GetName() { return m_strName; }

	void CreateCollider();
	CCollider* GetCollider() { return m_pCollider; }

	bool IsDead() { return !m_bAlive; }
	

	// �浹 �̺�Ʈ �Լ�. {}�� �����ص�. 
	virtual void OnCollision(CCollider* _pOther) {}
	virtual void OnCollisionEnter(CCollider* _pOther) {}
	virtual void OnCollisionExit(CCollider* _pOther) {}

private:
	// �̺�Ʈ �Ŵ����� ������ �� �ֵ��� private���� �����, friend class ����
	void SetDead() { m_bAlive = false; }

	
public:
	virtual void update() = 0;			// pure virtual function
	//void finalupdate();				// virtual ���ϸ� �������̵� �� �� ����. �׷��� Scene���� object �����ͷ� ��� ������Ʈ�� �����ϱ� ������ �θ��Լ��ιۿ� ���� �ȵ�..!!
	virtual void finalupdate() final;	// �ƿ� �������̵� ���ϰ� �����ϴ� ���. final�� ���̸� �� �̻� �������̵��� �� �� ���ٴ� ��.
	
	virtual void render(HDC _dc);
	void component_render(HDC _dc);		// render()�� ��ü������ �������̵� �ؼ� ����ϴ� ��� �θ����� �Լ� ȣ���ϸ� ������ �ʴ� ��ɱ��� ����ϰ� ��.
										// ���� ������Ʈ ������ ���� ����
public:
	CObject();
	virtual ~CObject();

	friend class CEventMgr;
};

