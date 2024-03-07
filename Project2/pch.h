#pragma once

// Pre-Compiled Header
// 프로젝트 속성 > C/C++ > 미리 컴파일된 헤더 설정
// 1. 여기에 작성된 헤더파일을 모든 파일에서 참조해야 함. 그렇지 않으면 에러남. 따라서 모든 파일에서 pch.h를 include 해. (클래수 추가할 때 자동으로 구문 생성)
// 2. 이미 완성되어서 컴파일 할 필요 없는 코드 (std 라이브러리 등)를 등록하면 여기 등록되어 있는 애들은 변경점 없으면 컴파일 하지 않음. 컴파일 속도 올라감
// 모든 cpp 파일 **맨 위 줄**에 #include "pch.h"가 써있어야 됨 ㅋㅋㅋ

#include <Windows.h>

#include <vector>
using std::vector;

#include <string>
using std::string;
using std::wstring;

#include "define.h"
#include "struct.h"