#pragma once
#include <assert.h>

struct Vec2
{
	float x;
	float y;


public:
	Vec2& operator = (POINT _pt)
	{
		x = (float)_pt.x;
		y = (float)_pt.y;
	}

public:
	float Length()
	{
		return sqrt(x * x + y * y);
	}

	Vec2& Normalize()
	{
		float fLen = Length();

		assert(fLen != 0.f);	// 0���� ������ ��Ȳ ����

		x /= fLen;
		y /= fLen;
		return *this;
	}

public :
	Vec2()
		: x(0.f)
		, y(0.f)
	{}

	Vec2 (float _x, float _y)
		: x(_x)
		, y(_y)
	{}

	Vec2(int _x, int _y)
		: x((float)_x)
		, y((float)_y)
	{}

	Vec2(long _x, long _y)
		: x((float)_x)
		, y((float)_y)
	{}

	Vec2 (POINT _pt)
		: x((float)_pt.x)
		, y((float)_pt.y)
	{}
};