#pragma once
#include "global.h"
// 전방선언한 경우 포인터 타입은 사용할 수 있다. (포인터타입 = 주소는 크기가 고정이니까)
// 컴파일 속도에 영향 x. 헤더 참조했으면 CObject가 변경사항 있으면 여기에서는 그거에 대해 컴파일러가 재확인할 필요가 없다.. ? 헤더끼리 참조를 방지하고자 전방선언 사용.
class CObject;

class CScene
{
private:
	// 다양한 종류의 오브젝트를 최고 조상 CObject*로 받아서 컨트롤. 다형성. 자식클래스 포인터를 부모클래스 포인터 타입으로 받을 수 있음.
	// 오브젝트 관리 벡터가 그룹마다 존재해야 함. 벡터타입을 받는 리스트를 선언, 크기는 그룹의 개수로 지정. 그룹은 pch.h에 정의되어 있음.
	vector<CObject*>	m_arrObj[(UINT)GROUP_TYPE::END];	// 벡터 배열 선언 법. []를 사용해서 [] 안의 크기만큼 배열을 만들고, 각 배열 안에 벡터가 있음. 즉 벡터가 배열로 32개 있는 거임
	wstring				m_strName;	// Scene 이름

public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	virtual void update();
	virtual void finalupdate();		// 마무리 작업 업데이트.
	virtual void render(HDC _dc);

	// 순수 가상함수 pure virtual function => 자식 클래스에서 구현 안하면 에러
	// 포함하면 추상클래스 => 부모클래스 객체 생성 불가능
	virtual void Enter() = 0;	// 진입
	virtual void Exit() = 0;	// 탈출

public:
	// 클래스 함수 헤더에 구현하면 자동으로 inline 처리. 함수 호출 비용 x 해당 스택에서 처리함.
	void AddObject(CObject* _pObj, GROUP_TYPE _etype)
	{
		m_arrObj[(UINT)_etype].push_back(_pObj);
		return;
	}
	void SaveObject(CObject* _pObj, GROUP_TYPE _etype);
	
	const vector<CObject*>& GetGroupObject(GROUP_TYPE _etype) { return m_arrObj[(UINT)_etype]; }
	void DeleteGroup(GROUP_TYPE _eTarget);
	void DeleteAll();

	const vector<CObject*> GetArrObj(GROUP_TYPE _etype) { return m_arrObj[(UINT)_etype]; }


public:
	CScene();
	virtual ~CScene();
};

