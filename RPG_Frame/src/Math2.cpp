#include "Math2.h"


namespace GameFrame {
	GameFrame::Vector2::Vector2()
	{
		x = 0.0f;
		y = 0.0f;
	}

	GameFrame::Vector2::Vector2(int X, int Y)
	{
		x = X;
		y = Y;
	}

	const Vector2 Vector2::up = Vector2(0, -1);
	const Vector2 Vector2::down = Vector2(0, 1);
	const Vector2 Vector2::left = Vector2(-1, 0);
	const Vector2 Vector2::right = Vector2(1, 0);
	const Vector2 Vector2::ZERO = Vector2(0, 0);
	const Vector2 Vector2::idle = Vector2(0, 0);

	Vector2 GameFrame::operator+(const Vector2& a, const Vector2& b)
	{
		return Vector2(a.x + b.x, a.y + b.y);
	}

	Vector2 operator-(const Vector2& a, const Vector2& b)
	{
		return Vector2(a.x - b.x, a.y - b.y);
	}

	Vector2 operator*(const Vector2& a, const Vector2& b)
	{
		return Vector2(a.x * b.x, a.y * b.y);
	}

	bool operator==(const Vector2& a, const Vector2& b)
	{
		if(a.x == b.x && a.y == b.y)
			return true;
		return false;
	}

	Vector2 operator*(const Vector2& a, float b)
	{
		return Vector2(a.x * b, a.y * b);
	}

	Vector2 operator*(int a, const Vector2& b)
	{
		return Vector2(a * b.x, a * b.y);
	}


}

