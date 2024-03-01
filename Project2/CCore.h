#pragma once

// 싱글톤 패턴
// 1. 객체의 생성을 1개로 제한.
// 2. 어디서든 접근 가능해야 함. 

//      => 생성자 소멸자를 private으로 숨긴다?  extern 선언도 할 수 없다. (2번 위배)
//		=> extern?  class를 extern으로 선언한다는 거 자체가 객체를 여러 개 만들 수 있다는 뜻. (1번 위배)
// => 특정 함수를 만들어서 그 함수로만 객체를 제공?  근데 객체가 있어야 멤버 함수 사용가능
// => static 함수 : 객체가 없어도 호출할 수 없는 멤버 함수. 객체를 통해 호출해도 객체의 멤버에 접근할 수 없음. this가 없음.




// 싱글톤 구현
// 1. class의 static 변수로 관리 (객체는 heap에, 포인터는 data 영역에 저장)
// 2. 전역변수 활용 ? - 객체를 데이터 영역에 올리는 방법



// 구현 1.
//class CCore
//{
//public:
//	static CCore* g_pInst;	// 정적 멤버 (데이터 영역) - 객체를 선언해도 스택(지역변수)/힙(동적할당)에 존재하지 않고 데이터 영역에 계속 하나로만 유지됨.
//							// 클래스 내부에서만 접근 가능
//
//							// GetInstance의 정적변수로 만들면 Release 함수에서 GetInstance를 호출해서 힙메모리 비울 수는 있는데, Release 했는데 나중에 다시 
//							// 객체를 만들어서 사용하려고 할 때 포인터변수는 그 삭제된 곳을 가리키고 있기 때문에 nullptr이 아닌 문제 발생.
//							// 결국 포인터 변수도 nullptr로 바꿔줘야 되는데, 포인터 변수가 GetInstance에서만 접근할수 있으니까 불가능.
//							// 결국 두 함수 다 접근 할 수 있도록 클래스 정적 변수로 선언해줌.
//
// // 생성자, 소멸자 숨김
//private:
//	CCore();
//	~CCore();
//
//public :
//	// 정적 멤버 함수, 객체 없이 호출 가능, this가 없다 (멤버에 접근 불가) - static 멤버는 접근 가능
//	static CCore* GetInstance()
//	{
//		// 함수가 최초 호출 된 경우 - 객체 생성 (동적 할당)
//		if (g_pInst == nullptr)
//		{
//			g_pInst = new CCore;
//		}
//		// => pCore라는 포인터 정적변수는 데이터 영역에, 실제 CCore 객체는 힙 영역에 저장됨.										
//
//		// 2번 이상 호출 된 경우
//		// 이미 만들어져 있는 걸 반환
//
//		return g_pInst;
//	}
//
//	static void Release()
//	{
//		if (g_pInst == nullptr)
//		{
//			delete g_pInst;
//			g_pInst = nullptr;
//		}
//		
//		return;
//	}
//
//};


// 구현 2.
class CCore
{
	SINGLETON(CCore);

private:
	HWND	m_hWnd;			// 메인 윈도우 핸들
	POINT	m_ptResolution; // 메인 윈도우 해상도

public :
	int init(HWND _hWnd, POINT _ptResolution);
	void progress();

private :
	CCore();		// # 생성자 소멸자도 Static? 생략되어 있는 건가
	~CCore();
};

// 매니저 같은 애들을 싱글톤 패턴으로 자주 구현할 예정임. => 매크로 함수로 만들어 두자.