#pragma once

// Pre-Compiled Header
// ������Ʈ �Ӽ� > C/C++ > �̸� �����ϵ� ��� ����
// 1. ���⿡ �ۼ��� ��������� ��� ���Ͽ��� �����ؾ� ��. �׷��� ������ ������. ���� ��� ���Ͽ��� pch.h�� include ��. (Ŭ���� �߰��� �� �ڵ����� ���� ����)
// 2. �̹� �ϼ��Ǿ ������ �� �ʿ� ���� �ڵ� (std ���̺귯�� ��)�� ����ϸ� ���� ��ϵǾ� �ִ� �ֵ��� ������ ������ ������ ���� ����. ������ �ӵ� �ö�
// ��� cpp ���� **�� �� ��**�� #include "pch.h"�� ���־�� �� ������

#include <Windows.h>

#include <vector>
using std::vector;

#include <string>
using std::string;
using std::wstring;

#include "define.h"
#include "struct.h"