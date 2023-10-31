#pragma once
#include "enums.h"
#include <Windows.h>

struct Vec2
{
	float x;
	float y;

	void Switch()
	{
		float tmp = x;
		x = y;
		y = tmp;
	}

	Vec2()
	{
		x = 0;
		y = 0;
	}

	Vec2(float _x, float _y)
	{
		x = _x;
		y = _y;
	}

	Vec2(float _v)
	{
		x = _v;
		y = _v;
	}

	Vec2(int _v)
	{
		x = _v;
		y = _v;
	}

	Vec2(Vec2* other)
	{
		x = other->x;
		y = other->y;
	}

	Vec2(const POINT& other)
	{
		x = other.x;
		y = other.y;
	}

	void operator =(const POINT& other)
	{
		x = other.x;
		y = other.y;
	}

	void operator +=(const Vec2& other)
	{
		x += other.x;
		y += other.y;
	}

	void operator -=(const Vec2& other)
	{
		x -= other.x;
		y -= other.y;
	}

	Vec2 operator / (int other)const
	{
		return Vec2(x / other, y / other);
	}

	Vec2 operator - (Vec2 other)const
	{
		return Vec2(x - other.x, y - other.y);
	}

	Vec2 operator + (Vec2 other)const
	{
		return Vec2(x + other.x, y + other.y);
	}

	Vec2 operator * (Vec2 other)const
	{
		return Vec2(x * other.x, y * other.y);
	}

	Vec2 operator * (int other) const
	{
		return Vec2(x * other, y * other);
	}

	bool operator == (Vec2 other) const
	{
		return x == other.x && y == other.y;
	}

	bool operator != (Vec2 other) const
	{
		return x != other.x || y != other.y;
	}

	static Vec2 ZERO() { return Vec2(0); }
	static Vec2 ONE() { return Vec2(1); }
};


struct KEY_DATA
{
	KEY eKey;
	KEY_STATE eState;
	bool bPressed;
};