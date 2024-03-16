#pragma once

// ��� ��� ���� ����
// - ���ܰ� ������ �� ��ó�ϱ� �����. ��ü���� ������ �����ؾ� ��.
// ������Ʈ ��� ���� ����
// - �ʿ��� �κе鸸 Ŭ������ ������ �� ������Ʈ Ŭ������ ����� (������) ���� �����.


class CObject;

// ���� �˻�.
// ������Ʈ�� �̵��� ���� �ݶ��̴��� �̵��ؾ� ��.
// �ٵ� ���� �Ű澲�� �ʾƵ� update���� ������Ʈ�� ����ٴϴ� �̵��� ����Ǿ�� ��.
// -> �̷��� �翬�� �۵��ؾ� �� update���� Scene���� ��Ƽ� ���� = f//void finalupdate();				// virtual ���ϸ� �������̵� �� �� ����. �׷��� Scene���� object �����ͷ� ��� ������Ʈ�� �����ϱ� ������ �θ��Լ��ιۿ� ���� �ȵ�..!!inalupdate().
// # ����Ƽ late update �����ǰ�.. ����Ƽ update ������ �� ��Ծ..
// # ��� final update�� ����� ���� �� �𸣰ڴ�.. �������� �۾� ������ ���� �����̶�µ�.. ���� �ȿʹ���
class CCollider
{
private:
	static UINT g_iNextID;
	CObject*	m_pOwner;		// ������, �ڱⰡ ����ٴ� ������Ʈ�� ����. �ֹ濬��. 
								// ������Ʈ�� CreateCollider���� friend class�ϱ� private ����� �� ������ �����ؼ� ���� ������Ʈ �ڽ��� �����ͷ� ��������.
	Vec2		m_vOffsetPos;	// ������Ʈ ��ġ�κ��� ������� ��ġ
	Vec2		m_vFinalPos;	// ������Ʈ ��ǥ + offset���� ���Ǵ� ���� ��ġ, finalupdate���� ������Ʈ�� ��ġ
	Vec2		m_vScale;		// �浹ü�� ũ��
	UINT		m_iID;			// �浹ü�� ������ ID ��
	UINT		m_iCol;

public:
	void SetOffsetPos(Vec2 _vPos) { m_vOffsetPos = _vPos;}
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetOffsetPos() { return m_vOffsetPos; }
	Vec2 GetScale() { return m_vScale; }

	Vec2 GetFinalPos() { return m_vFinalPos; }

	UINT GetID() { return m_iID; }

public:
	void finalupdate();
	void render(HDC _dc);

public:
	// �浹 ���� �Լ�
	void OnCollision(CCollider* _pOther);		// �浹 ���� ���¿��� ȣ��
	void OnCollisionEnter(CCollider* _pOther);	// �浹 ���¿� ����
	void OnCollisionExit(CCollider* _pOther);	// �浹�� �� �������� ����

	CCollider& operator = (const CCollider& _origin) = delete; // ���� ������ ��� ���ϰ� ����.

public:
	CCollider();
	CCollider(const CCollider& _origin); // ���������. m_pOwner�� m_iID���� �������� ����Ǹ� �ȵǹǷ� ���� ����
	~CCollider();

	

	friend class CObject;
};

