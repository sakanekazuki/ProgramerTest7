#pragma once

struct Vector2
{
	int x = 0;
	int y = 0;

	Vector2(int x = 0, int y = 0) :x(x), y(y)
	{}

	Vector2(const Vector2&) = default;

	Vector2& operator=(const Vector2&) = default;

	Vector2& operator+=(const Vector2& vec)
	{
		x += vec.x;
		y += vec.y;

		return *this;
	}

	Vector2& operator-=(const Vector2& vec)
	{
		x -= vec.x;
		y -= vec.y;

		return *this;
	}

	Vector2 operator+(const Vector2& vec)
	{
		return Vector2(x + vec.x, y + vec.y);
	}

	Vector2 operator-(const Vector2& vec)
	{
		return Vector2(x - vec.x, y - vec.y);
	}

	bool operator==(const Vector2& vec)const
	{
		return (x == vec.x) && (y == vec.y);
	}
};