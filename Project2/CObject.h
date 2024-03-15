#pragma once

class CTexture;
class CCollider;

// ��ü, �߻�Ŭ����
class CObject
{
private:
	Vec2	m_vPos;
	Vec2	m_vScale;

	CCollider* m_pCollider;

private:
	CTexture* m_pTex;

public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }
	void SetTexture(CTexture* _pTex) { m_pTex = _pTex; }

	Vec2 GetPos() { return m_vPos; }
	Vec2 GetScale() { return m_vScale; }
	CTexture* GetTexture() { return m_pTex; }

	void CreateCollider();
	CCollider* GetCollider() { return m_pCollider; }

	
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


};

