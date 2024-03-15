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

	Vec2 operator + (Vec2 _vOther)
	{
		return Vec2( x + _vOther.x, y + _vOther.y );
	}
	Vec2 operator - (Vec2 _vOther)
	{
		return Vec2(x - _vOther.x, y - _vOther.y);
	}
	Vec2 operator * (Vec2 _vOther)
	{
		return Vec2(x * _vOther.x, y * _vOther.y);
	}
	Vec2 operator / (Vec2 _vOther)
	{
		assert(_vOther.x != 0.f && _vOther.y != 0.f);
		return Vec2(x / _vOther.x, y / _vOther.y);
	}


	void Rotate(float _rad)
	{
		float tempx = x;
		float tempy = y;
		float costheta = cos(_rad);
		float sintheta = sin(_rad);
		x = costheta * tempx - sintheta * tempy;
		y = sintheta * tempx + costheta * tempy;
	}

public:
	float Length()
	{
		return sqrt(x * x + y * y);
	}

	Vec2& Normalize()
	{
		float fLen = Length();

		assert(fLen != 0.f);	// 0으로 나누는 상황 방지

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