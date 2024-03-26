#pragma once

class CTexture;

// Components
class CCollider;
class CAnimator;

// ��ü, �߻�Ŭ����
class CObject
{
private:
	wstring		m_strName;

	Vec2		m_vPos;
	Vec2		m_vScale;

	// Component
	CCollider*	m_pCollider;
	CAnimator*	m_pAnimator;

	bool		m_bAlive;
	bool		m_bSceneAlive;



public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }
	
	void SetName(const wstring& _strName) { m_strName = _strName; }
	void SetSceneAlive();

	Vec2 GetPos() { return m_vPos; }
	Vec2 GetScale() { return m_vScale; }
	
	const wstring& GetName() { return m_strName; }
	bool GetSceneAlive();

	void CreateCollider();
	CCollider* GetCollider() { return m_pCollider; }

	void CreateAnimator();
	CAnimator* GetAnimator() { return m_pAnimator; }

	bool IsDead() { return !m_bAlive; }

// #####################################
private:
	// �ִϸ��̼� ����鼭 ������ ����
	CTexture* m_pTex;
public:
	// �ִϸ��̼� ����鼭 ������ �Լ�
	void SetTexture(CTexture* _pTex) { m_pTex = _pTex; }
	CTexture* GetTexture() { return m_pTex; }
// #######################################
	

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

	virtual CObject* Clone() = 0;		// pure virtual function, �ڱ� �ڽ��� �������� ����


public:
	CObject();
	CObject(const CObject& _origin);	// �⺻ ��������� ȣ�� �� �ݶ��̴� �ּұ��� �����ϹǷ� ����. ���� �������ش�.
	virtual ~CObject();

	friend class CEventMgr;
};

