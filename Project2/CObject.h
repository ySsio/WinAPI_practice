#pragma once

class CTexture;
class CCollider;
class CEventMgr;

// 물체, 추상클래스
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
	

	// 충돌 이벤트 함수. {}로 구현해둠. 
	virtual void OnCollision(CCollider* _pOther) {}
	virtual void OnCollisionEnter(CCollider* _pOther) {}
	virtual void OnCollisionExit(CCollider* _pOther) {}

private:
	// 이벤트 매니저만 접근할 수 있도록 private으로 만들고, friend class 지정
	void SetDead() { m_bAlive = false; }

	
public:
	virtual void update() = 0;			// pure virtual function
	//void finalupdate();				// virtual 안하면 오버라이딩 할 수 있음. 그래도 Scene에서 object 포인터로 모든 오브젝트를 관리하기 때문에 부모함수로밖에 실행 안됨..!!
	virtual void finalupdate() final;	// 아예 오버라이딩 못하게 방지하는 방법. final을 붙이면 이 이상 오버라이딩을 할 수 없다는 뜻.
	
	virtual void render(HDC _dc);
	void component_render(HDC _dc);		// render()을 자체적으로 오버라이드 해서 사용하는 경우 부모쪽의 함수 호출하면 원하지 않는 기능까지 사용하게 됨.
										// 따라서 컴포넌트 렌더만 따로 구현
public:
	CObject();
	virtual ~CObject();

	friend class CEventMgr;
};

