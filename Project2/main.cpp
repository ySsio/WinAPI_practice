// Project2.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "Project2.h"

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

    // @ timer로 매 시간마다 메시지 발생시킨다.
    //SetTimer(g_hWnd, 10, 0, nullptr); // uElapse -> 1000ms = 1초
    // @ 커널 오브젝트이므로 제거해줘야 함. KillTimer();

    // 기본 메시지 루프입니다:
    // @ 무한 반복문.
    // @ 해당 window가 종료된다고 판단되면 while문을 빠져나와서 프로세스를 중단시키는 구조. 즉, process != window. 프로세스 안에서 윈도우를 만들고,
    // @ 윈도우가 꺼지면 프로세스를 종료하는 로직을 구현해서 맞물리게 해 놓았을 뿐이다.


    // @ GetMessage() : 프로그램 프로세스에 메시지 큐라는 것이 있음. 현재 포커싱 된 윈도우 프로세스에 메시지가 전달되어서 이벤트 수행한다..? 잘 이해 안댐
    // @ 메시지 큐에서 메시지를 꺼내서 msg 변수에 넣음. 레퍼런스 타입으로 받아서 멤버 건드림.
    // @ 중요한 특징 - 메세지 큐에서 메세지 확인될 때까지 대기. 메세지 없으면 리턴하지 않는 함수.
    // @ 그럼 GetMessage()가 true/false 반환하는 건 메세지의 종류에 의존적이겠지?
    // @ 확인해본 메세지의 메세지 타입이 msg.message == WM_QUIT 인 경우 false를 반환. => while 문 종료 => 프로세스 종료
    // @ 프로그램 끄고 싶을 때, window 다 종료하는 등 마무리 작업을 위한 메세지가 발생한 후에 가장 마지막에 메세지 타입이 WM_QUIT인 메세지가 발생.

    while (GetMessage(&msg, nullptr, 0, 0))  
    {   
        // @ 테이블에 등록되어 있는 단축키 입력이 발생했는지를 계속 검사.
        // @ msg.hwnd = 메시지 핸들, 메시지가 발생한 윈도우, 즉 포커싱된 윈도우를 말하는 듯.
        // @ 하나의 프로세스 안에서 여러 윈도우를 만들 수 있는데, 구체적으로 어떤 윈도우인지 알 수 있음.
        // @ 그 메시지 처리하는 건 각 윈도우에 딸려있는 함수가 처리함. 프로시저 함수 = 처리기 함수. 각 윈도우는 이벤트 발생햇을 때 처리하는 함수 (프로시저)를 같이 들고 있음.
        // @ wcex.lpfnWndProc (함수 포인터 변수) .. 프로시저
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    // @ 프로그램이 메세지 반응형태로 구성됨. 프로그램이 동작하려면 반드시 메세지가 있어야 하고, 그걸 처리하는 형태로 프로그램이 동작함.
    // @ 메세지가 없으면 하염없이 메세지 큐를 바라보고 있을 것.
    // @ => 게임을 만들기에는 부적합한 방식임.

    // @ 메시지 꺼내와서 처리하라고 하면 그 메시지 발생한 해당 윈도우의 프로시저로 들어갈 거임.

    //KillTimer(g_hWnd, 10);

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

unsigned short g_x = 0;
unsigned short g_y = 0;

#include <vector>
using std::vector;


struct tObjInfo
{
    POINT g_ptObjPos;
    POINT g_ptObjScale;
};

vector <tObjInfo> g_vecInfo;

bool bLbtnDown = false;

POINT g_ptLT;
POINT g_ptRB;

POINT g_ptObjPos = { 500, 300 };
POINT g_ptObjScale = { 100, 100 };

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
    case WM_PAINT:  // @ MSDN ) 윈도우에 무효화 영역(invalidate)이 발생한 경우. 다른 윈도우에 의해 가려졌던 영역?
                    // @ - 과거엔 그랬는데 이제는 화면에 그려졌던 데이터를 비트맵 형식으로 저장해두고 있어서 안 그럼.
                    // @ 창이 줄어들었다 커졌다.. 하는 상황?
                    // http://www.soen.kr/lecture/win32api/reference/Message/WM_PAINT.htm
                    // ① 윈도우가 처음 생성되었을 때                          (O)
                    // ② 윈도우의 위치가 이동되었을 때                        (X)
                    // ③ 윈도우의 크기가 변경되었을 때.최대, 최소화되었을 때    (O)
                    // ④ 다른 윈도우에 가려져 있다가 드러날 때                 (X)  - 근데 화면 밖으로 나갔다가 들어올 떄는 (O)
                    // ⑤ 스크롤 될 때                                        (확인 못해봄)
        
        // @ case 문에 {} block 뭐냐 ? - case 문 내부에서 지역 변수를 선언할 때 지역을 설정해줘야 함.
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);    // @  Device Context (그리기) 만들어서 핸들 (ID)를 반환
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            
            // @ 윈도우 핸들
            // @ HWND, HDC, HPEN, HBRUSH 등은 DECLARE_HANDLE 매크로로 정의 되어 있는 타입임. DECLARE_HANDLE은 이름을 받아서 int 하나 들어있는 구조체를 반환해줌
            // @ 어차피 int (id 값) 하나 들어있는 구조체인데 왜 여러 종류를 만드는 거지?
            // @ 사용자 입장에서는 어차피 다 id 값 하나 들고있는 구조체니까 통일해서 써도 되지않냐? 특히 나는 그냥 변수명으로 구분지으면 되지 않냐 생각했는데
            // @ 이걸 받아서 사용하는 함수 입장에서는 이게 윈도우 id인지 device context id인지 구별하는게 어려우니까 각각 별개의 자료형으로 만들어 둔거다.
            // @ 예를 들어 어떤 함수는 윈도우 id를 받아서 사용해야 되는데 타입을 구분을 안해놨으면 id를 받아서 이게 윈도우 id 면 실행하고 아니면 예외처리하고
            // @ 이러한 과정이 복잡해지니까 자료형 자체를 구분해서 사용하는 듯 함. 다른 핸들을 실수로 잘못넣으면 컴파일 단계에서 오류를 잡을 수 있기 때문에.


            // @ 윈도우 좌표
            // @ 작업영역 - 수정하고 바꿀 수 있는 영역. 타이틀 바 밑 메뉴 바 밑 그 아래 영역.
            // @ (0,0) = 좌상단, 1픽셀 픽셀 하나하나가 메모리 값
            // @ 픽셀 하나가 RGB 각 1바이트 씩, 총 3바이트.. 1920x1080이면 약 6MiB 차지


            // @ HDC?
            // @ 어떤 커널오브젝트 device context의 id를 갖고있는 핸들.
            // @ device context란? 그리기 작업 수행하는데 필요한 데이터 집합. - 그리는 목적지 (윈도우), 펜 (선 그리기), 브러쉬 (도형 그리면 내부 채우는 색)
            // @ 지정 안해주면 디폴트  : 윈도우는 처음에 받았고, 펜은 검은색, 브러쉬는 흰색으로 설정

            // @ 직접 펜을 만들어서 DC에 제공
            HPEN hRedPen = CreatePen(PS_DOT,1,RGB(0,0,0));
            // @ RGB(r,g,b) => ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))
            // @ red 1바이트에 8bit left shift한 g, 16bit left shift한 b를 합침 (b/g/r)순으로 메모리에 들어감.
            // @ 형변환은 BYTE가 unsigned char, WORD가 unsigned short, DWORD가 unsigned long인데, 
            // @ r: 1byte는 unsinged char에, g: 8bit shift하면 2byte 차지하니까 unsigned short, b : 16bit shift하면 3byte 차지하니까 unsinged long (최대 4byte)
            // @ 로 캐스팅 해준 것.

            // @ 자주 쓰는 펜과 브러쉬를 만들어놨음. 삭제/관리하면 안됨.
            HBRUSH hHollowBrush = (HBRUSH)GetStockObject(HOLLOW_BRUSH);    // @ 투명 브러쉬
            HBRUSH hBlueBrush = CreateSolidBrush(RGB(0, 0, 100));
            

            // @ SelectObject(HDC,HGDIOBJ) : DC가 bitmap, brush, pen, font, 지역 등의 오브젝트를 선택하는 함수. 이전에 사용하던 오브젝트를 반환함. (여기선 펜)
            // @ HGDIOBJ는 void 포인터. 리턴타입이 void 포인터이므로 형변환해줘야 함. (malloc 같은 느낌)
            HPEN hDefaultPen = (HPEN) SelectObject(hdc, hRedPen);
            HBRUSH hDefaultBrush = (HBRUSH) SelectObject(hdc, hBlueBrush);

            // @ 사각형 그리는 함수
            if (bLbtnDown) 
            {
                Rectangle(hdc, g_ptLT.x, g_ptLT.y
                    , g_ptRB.x, g_ptRB.y);

            }

            // @ 벡터에 저장한 사각형을 그린다.
            // @ 문제점 1. 화면에 그리는 타이밍이 동체시력 프레임이랑 안맞으면 깜빡거리는 현상 발생
            // @ => 두 개의 도화지 관리할 것. 하나에 미리 싹 그려놓고 그거로 업데이트.
            // @ 문제점 2. 메시지가 발생해야 그림이 업데이트 됨. 매 순간순간 체크하면서 돌아가야 함. 메시지 방식은 메세지 입력이 생겨야 작동하는 방식이라 문제.
            // @ => 강제로 메시지를 일정시간마다 발생시키면 되지 않냐? SetTimer()
            // @ 그럼에도 너무 느리고 비효율적임. 윈도우 메세지 처리기반은 사용하지 않는 방향으로 갈거임.
            for (size_t i = 0; i < g_vecInfo.size(); i++)
            {
                Rectangle(hdc
                    , g_vecInfo[i].g_ptObjPos.x - g_vecInfo[i].g_ptObjScale.x / 2
                    , g_vecInfo[i].g_ptObjPos.y - g_vecInfo[i].g_ptObjScale.y / 2
                    , g_vecInfo[i].g_ptObjPos.x + g_vecInfo[i].g_ptObjScale.x / 2
                    , g_vecInfo[i].g_ptObjPos.y + g_vecInfo[i].g_ptObjScale.y / 2);
            }
            
            // @ 원래 펜으로 되돌려줌.
            SelectObject(hdc, hDefaultPen);

            // @ 커널 오브젝트 삭제
            DeleteObject(hRedPen);


            EndPaint(hWnd, &ps);
        }
        break;
    // @ 키가 눌렸을 때 발생하는 메시지
    // @ 계속 누를 때, 텀이 존재함. 1초?
    case WM_KEYDOWN:
    {
        // @ 무슨 키인지? - WndProc의 인자 중 wParam, lParam이 부연설명해주는 인자값 . 예를 들어 마우스 클릭 -> lParam에 커서 좌표, 키다운 -> wParam에 키값 들어옴
        switch (wParam)
        {
            // @ https://learn.microsoft.com/ko-kr/windows/win32/inputdev/virtual-key-codes - 키 코드
            // @ 일반 문자는 ascii 코드 값으로 지정되어있음. 예) a 누르면 'A' (대문자 기준)
        case VK_UP: // @ 방향키 화살표 위
        case 'W':   // @ W키
            g_ptObjPos.y -= 10;
            InvalidateRect(hWnd, nullptr, true);   // @ 무효화 영역을 직접 설정. nullptr 넣으면 영역 전체 지정.
            // @ 마지막 인자를 false로 지정하면 이전 픽셀 (메모리)에 그냥 값이 그대로 남아있음. 모든 픽셀을 초기화 해줘야 함.
            // @ => 마지막 인자를 true로 지정하면 전체 지웠다가 다시 그림.
            break;
        case VK_DOWN:
        case 'S':   
            g_ptObjPos.y += 10;
            InvalidateRect(hWnd, nullptr, true);
            break;
        case VK_LEFT:
        case 'A':   
            g_ptObjPos.x -= 10;
            InvalidateRect(hWnd, nullptr, true);
            break;
        case VK_RIGHT: 
        case 'D':   
            g_ptObjPos.x += 10;
            InvalidateRect(hWnd, nullptr, true);
            break;
        }
    }

        break;

    case WM_LBUTTONDOWN:
        // @ lParam에 좌표값 들어옴 (LPARAM이 int64__ 타입이므로 8byte 정수) - 
        // @ 유튜브 강의에서는 long 타입이라 4byte 였는데 바꼈네.. : 4byte니까 x좌표, y좌표 2byte씩 쪼개서 씀 [y(2byte)|x(2byte)] (2byte면 65536개 숫자 표현가능)
        // @ #define LOWORD(l)           ((WORD)(((DWORD_PTR)(l)) & 0xffff))           
        // @ #define HIWORD(l)           ((WORD)((((DWORD_PTR)(l)) >> 16) & 0xffff))
        // @  - DWORD_PTR은 unsigned int64__ (8byte), WORD는 unsigned short(2byte)
        // @  - 괄호 안의 값을 8byte로 바꾼 뒤 LOWORD()는 맨 아래 2byte 추출, HIWORD는 그 다음 2byte 추출 (3,4byte자리)
        // @ # 그럼 lParam이 8byte인데 위에 4byte는 그냥 버리는거임?
        g_ptLT.x = LOWORD(lParam); // @ x좌표
        g_ptLT.y = HIWORD(lParam); // @ y좌표 - 좌표는 작업영역 기준으로 나옴.
        bLbtnDown = true;
        break;

    case WM_LBUTTONUP:
    {
        tObjInfo info = {};
        info.g_ptObjPos.x = (g_ptLT.x + g_ptRB.x) / 2;
        info.g_ptObjPos.y = (g_ptLT.y + g_ptRB.y) / 2;
        info.g_ptObjScale.x = abs(g_ptLT.x - g_ptRB.x);
        info.g_ptObjScale.y = abs(g_ptLT.y - g_ptRB.y);

        g_vecInfo.push_back(info);
        bLbtnDown = false;
        InvalidateRect(hWnd, nullptr, true);
    }
        

        break;

    case WM_MOUSEMOVE:
        g_ptRB.x = LOWORD(lParam);
        g_ptRB.y = HIWORD(lParam);
        InvalidateRect(hWnd, nullptr, true);
        break;

    case WM_TIMER:
        InvalidateRect(hWnd, nullptr, true);
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
