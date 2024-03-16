#pragma once

// 상속 기반 구조 설계
// - 예외가 생겼을 때 대처하기 어려움. 전체적인 구조를 수정해야 함.
// 컴포넌트 기반 구조 설계
// - 필요한 부분들만 클래스로 설계한 뒤 컴포넌트 클래스를 멤버로 (포인터) 만들어서 사용함.


class CObject;

// 영역 검사.
// 오브젝트의 이동에 따라 콜라이더도 이동해야 함.
// 근데 내가 신경쓰지 않아도 update에서 오브젝트를 따라다니는 이동이 보장되어야 함.
// -> 이렇게 당연히 작동해야 할 update들을 Scene에서 모아서 구현 = f//void finalupdate();				// virtual 안하면 오버라이딩 할 수 있음. 그래도 Scene에서 object 포인터로 모든 오브젝트를 관리하기 때문에 부모함수로밖에 실행 안됨..!!inalupdate().
// # 유니티 late update 같은건가.. 유니티 update 구조를 다 까먹어서..
// # 사실 final update로 만드는 이유 잘 모르겠다.. 내부적인 작업 마무리 이후 시점이라는데.. 아직 안와닿음
class CCollider
{
private:
	static UINT g_iNextID;
	CObject*	m_pOwner;		// 다형성, 자기가 따라다닐 오브젝트를 받음. 쌍방연결. 
								// 오브젝트의 CreateCollider에서 friend class니까 private 멤버인 이 변수에 접근해서 직접 오브젝트 자신의 포인터로 지정해줌.
	Vec2		m_vOffsetPos;	// 오브젝트 위치로부터 상대적인 위치
	Vec2		m_vFinalPos;	// 오브젝트 좌표 + offset으로 계산되는 최종 위치, finalupdate에서 업데이트할 위치
	Vec2		m_vScale;		// 충돌체의 크기
	UINT		m_iID;			// 충돌체의 고유한 ID 값
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
	// 충돌 시점 함수
	void OnCollision(CCollider* _pOther);		// 충돌 중인 상태에서 호출
	void OnCollisionEnter(CCollider* _pOther);	// 충돌 상태에 잔입
	void OnCollisionExit(CCollider* _pOther);	// 충돌을 막 빠져나온 상태

	CCollider& operator = (const CCollider& _origin) = delete; // 대입 연산자 사용 못하게 제한.

public:
	CCollider();
	CCollider(const CCollider& _origin); // 복사생성자. m_pOwner나 m_iID같은 고유값은 복사되면 안되므로 직접 구현
	~CCollider();

	

	friend class CObject;
};

