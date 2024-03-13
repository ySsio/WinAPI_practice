#pragma once

class CTexture;

// 물체, 추상클래스
class CObject
{
private:
	Vec2	m_vPos;
	Vec2	m_vScale;

private:
	CTexture* m_pTex;

public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }
	void SetTexture(CTexture* _pTex) { m_pTex = _pTex; }

	Vec2 GetPos() { return m_vPos; }
	Vec2 GetScale() { return m_vScale; }
	CTexture* GetTexture() { return m_pTex; }
	

	virtual void update() = 0;		// pure virtual function
	virtual void render(HDC _dc);

public:
	CObject();
	virtual ~CObject();


};

