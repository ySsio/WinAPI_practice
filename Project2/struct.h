#pragma once

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

	Vec2 operator + (Vec2 _vec)
	{
		return Vec2{ x + _vec.x, y + _vec.y };
	}

	Vec2 operator - (Vec2 _vec)
	{
		return Vec2{ x - _vec.x, y - _vec.y };
	}

	float Length()
	{
		return sqrtf(pow(x,2) + pow(y,2));
	}

	static float Dist(Vec2 _vec1, Vec2 _vec2)
	{
		return sqrtf(pow(_vec1.x - _vec2.x,2) + pow(_vec1.y- _vec2.y,2));
	}

	static float DistPow(Vec2 _vec1, Vec2 _vec2)
	{
		return pow(_vec1.x- _vec2.x,2) + pow(_vec1.y- _vec2.y,2);
	}

	Vec2 Normalized()
	{
		float len = this->Length();
		return Vec2{ x / len, y / len };
	}

	Vec2& operator * (float _const)
	{
		x *= _const;
		y *= _const;

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