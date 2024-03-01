#include "CCore.h"

// 구현 1.
// 클래스에서 선언한 정적 멤버는 밖에서 반드시 초기화 해줘야 한다. 안하면 링크에러 남
CCore* CCore::g_pInst = nullptr;