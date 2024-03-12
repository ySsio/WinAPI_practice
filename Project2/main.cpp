// Project2.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "Project2.h"
#include "CCore.h"


#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
// @ 메인 윈도우핸들 내가 만듦
HWND g_hWnd;
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.       // @ WCHAR은 wchar_t를 재정의 한 것. typedef wchar_t WCHAR;
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


// @ Windows SAL (주석 언어) : 지역 변수 앞에 변수의 의미/용도를 적는 것. 
// @ _In_ - 데이터가 함수에 입력된다. 
// @ _In_opt_ - 부가적인 데이터.
// @ 아무 의미 없는 데이터를 왜 받아옴? - 아마도, Windows 업데이트 되면서 필요없어졌으나 구버전의 Windows 프로그램들도 
// @ 실행할 수 있어야하기 때문에 인자 형태를 그대로 유지하는 듯하다..

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,         // @ 실행된 프로세스의 시작 주소. 스택/힙/코드/데이터 영역 등을 할당하는데 시작되는 주소
                     _In_opt_ HINSTANCE hPrevInstance,  // @ 이전 프로세스의 시작 주소.. 잔재.. 지금은 똑같은 프로그램 여러 개 실행해도 hInstance가 동일하대
                                                        // @ ㄴ # Windows 가상메모리 사용. 실제 물리적인 주소는 다른데 사용자에게는 하나의 주소인 것처럼 제공??
                     _In_ LPWSTR    lpCmdLine,          // @ 프로그램 시작할 때 문자열 받을 수 있음. args 같은거 인가 LPWSTR - WCHAR* 타입
                     _In_ int       nCmdShow)           
                                                        
{
    // @ 메모리 leak (누수) 체크
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    
    // @ 중단점 걸어주는 기능 : 위에서 메모리 누수 체크된 곳을 input으로 넣어서 어디서 난건지 확인
    //_CrtSetBreakAlloc(295); 



    UNREFERENCED_PARAMETER(hPrevInstance);      // @ define으로 정의된 매크로. 그냥 안에 있는 값이 그대로 나오는 매크로이고, 결국 아무 의미없는 코드. 컴파일러가 제거함
    UNREFERENCED_PARAMETER(lpCmdLine);          // @ 이 두 변수가 참조되지 않는다는 것을 알려주기 위해 작성한 듯. 주석 대신 잘 표시되게 쓴 것 같다.

    // TODO: 여기에 코드를 입력합니다.
    
    // 전역 문자열을 초기화합니다.
    // @ StringTable에서 IDS~~, IDC~~의 문자열을 로드해서 szTitle, szWindowClass 문자열에 복사해서 넣어줌.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);         // @ IDS_APP_TITLE, IDC_PROJECT2 값 리소스 뷰>String Table에서 확인 가능.
    LoadStringW(hInstance, IDC_PROJECT2, szWindowClass, MAX_LOADSTRING);    // @ ㄴ Resource.h에 define 전처리기로 정의되어 있음. 보니까 이 라일락 색이 다 매크로임
    
    // @ 윈도우 정보 등록. window에 어떤 정보를 띄울 것인지 세팅.
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    // @ 윈도우 생성
    // @ 윈도우 : 사용자와 프로그램 사이의 인터페이스 (사용자와 장치 사이의 소통 역할) 
    // @ 프로그램 내부 데이터를 OS를 통해 출력장치인 모니터로 시각적으로 보여주고, 내가 입력장치를 통해 조작해서 실제 메모리를 변경하는..
    // @ Process != Window. 프로세스는 window를 가질 수도, 안 가질 수도 있다.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;   // @ 윈도우 생성 못했으면 프로세스 종료.
    }


    // @ 단축키
    // @ 리소스 뷰에서 Accelarator > IDC_PROJECT2에서 확인 가능.
    // @ 지금 alt + ? 의 ID가 IDM_ABOUT으로 등록되어 있는데, 리소스 뷰 Menu > IDC_PROJECT2 켜보면 도움말 > 정보 ID가 IDM_ABOUT으로 되어있음.
    // @ IDM_ABOUT MSG(메시지)가 발생하면 정보 버튼 눌렸을 때 발생하는 이벤트가 호출됨. 근데 이걸 단축키로 발생시킬 수 있다.
    // @ 참고 : 리소스 뷰는 Resource.h 파일을 닫아놔야 볼 수 있다
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PROJECT2));

    MSG msg;

    


    // Core 초기화
    // 객체가 초기화 되지 않으면 프로그램 종료. (프로그램의 핵심적인 역할)
    if (FAILED(CCore::GetInst()->init(g_hWnd, POINT{ 1280, 768 })))
    {
        MessageBox(nullptr, L"Core 객체 초기화 실패!", L"ERROR", MB_OK);

        return FALSE;
    }
    


    // 기본 메시지 루프입니다:


    // GetMessage
    // 메세지 큐에서 메세지 확인 될 때까지 대기
    // msg.message == WM_QUIT인 경우 false를 반환 -> 프로그램 종료.
    
    // PeekMessage
    // 메세지 큐에 메세지가 없어도 대기하지 않고 그냥 반환되는 함수 <-> GetMessage()
    // 인자 하나 더 받음. 확인한 메세지가 있을 경우 메세지 큐에서 그 메세지를 제거할지 여부.
    // 메세지가 있으면 true 없으면 false 반환. 그러므로 while 문의 조건으로 사용하기엔 부적합. (메세지 있으면 프로그램 종료되니까)

    while (true)
    {   
        // 메세지가 있으면
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {

            // 받아온 메세지가 WM_QUIT일 때 while문 break 후 프로그램 종료
            if (msg.message == WM_QUIT)
                break;

            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }

        }
        // 메세지가 없으면
        else
        { 
            CCore::GetInst()->progress();

            // Game 코드 수행
            // 디자인 패턴 (설계 유형)
            // 싱글톤
        }
    }



    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
// 
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    // @ WNDCLASSEXW라는 구조체 멤버를 채워줌.
    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PROJECT2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);   // @ 커서 모양 지정
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+2);         // @ 윈도우 색 지정
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_PROJECT2);   // @ nullptr로 세팅하면 메뉴바 사용 안 함.
    wcex.lpszClassName  = szWindowClass;                    // @ key 값?
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex); // @ RegisterClassExW() : windows에서 제공하는 함수, 선언만 볼 수 있고 구현부는 볼 수 없다. Windows API를 사용해야지!
                                    // @ 어떤 기능이 필요할 때, 만들 생각보다는 먼저 만들어진게 있나 살펴보기.
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   // @ 커널오브젝트 (= OS에서 관리하는 정보) 의 ID 값을 제공, 이를 다루는 것을 윈도우 핸들이라 한다.
   g_hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!g_hWnd)
   {
      return FALSE;
   }

   ShowWindow(g_hWnd, nCmdShow);
   UpdateWindow(g_hWnd);

   

   return TRUE;
}
//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.



// @ hWnd : 메세지가 발생한 윈도우의 핸들(id)
// @ message : 발생한 메세지
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);    // @  Device Context (그리기) 만들어서 핸들 (ID)를 반환

            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            
            Rectangle(hdc, 1180, 668, 1280, 768);


            EndPaint(hWnd, &ps);
        }
        break;

    case WM_KEYDOWN:
        break;

    case WM_LBUTTONDOWN:
        break;

    case WM_LBUTTONUP:
        break;

    case WM_MOUSEMOVE:
        break;

    case WM_TIMER:
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);    // @ 윈도우 메시지가 너무 많으므로 너가 처리하고 싶은 메시지는 위에 case에서 처리하고, 그 외는
                                                                // @ DefWindowProc()로 처리를 해주겠다.
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

// 렌더링 - 화면의 변경점을 적용시키기 위해서 계속 반복해서 그리는 과정 (frame)
