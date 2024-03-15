#pragma once

class CTexture;
class CCollider;

// 물체, 추상클래스
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
	//void finalupdate();				// virtual 안하면 오버라이딩 할 수 있음. 그래도 Scene에서 object 포인터로 모든 오브젝트를 관리하기 때문에 부모함수로밖에 실행 안됨..!!
	virtual void finalupdate() final;	// 아예 오버라이딩 못하게 방지하는 방법. final을 붙이면 이 이상 오버라이딩을 할 수 없다는 뜻.
	
	virtual void render(HDC _dc);
	void component_render(HDC _dc);		// render()을 자체적으로 오버라이드 해서 사용하는 경우 부모쪽의 함수 호출하면 원하지 않는 기능까지 사용하게 됨.
										// 따라서 컴포넌트 렌더만 따로 구현
public:
	CObject();
	virtual ~CObject();


};

