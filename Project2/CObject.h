#pragma once

class CTexture;

// Components
class CCollider;
class CAnimator;

// 물체, 추상클래스
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
	// 애니메이션 만들면서 없어질 변수
	CTexture* m_pTex;
public:
	// 애니메이션 만들면서 없어질 함수
	void SetTexture(CTexture* _pTex) { m_pTex = _pTex; }
	CTexture* GetTexture() { return m_pTex; }
// #######################################
	

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

	virtual CObject* Clone() = 0;		// pure virtual function, 자기 자신의 복제본을 리턴


public:
	CObject();
	CObject(const CObject& _origin);	// 기본 복사생성자 호출 시 콜라이더 주소까지 복사하므로 문제. 직접 구현해준다.
	virtual ~CObject();

	friend class CEventMgr;
};

