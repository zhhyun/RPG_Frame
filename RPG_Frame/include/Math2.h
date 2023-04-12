#ifndef __Math2__
#define __Math2__

namespace GameFrame {
	class Vector2 {
	public:
		int x;
		int y;

		Vector2();
		Vector2(int X, int Y);

		static const Vector2 up;
		static const Vector2 down;
		static const Vector2 left;
		static const Vector2 right;

		friend Vector2 operator+(const Vector2& a, const Vector2& b);
		friend Vector2 operator-(const Vector2& a, const Vector2& b);
		friend Vector2 operator*(const Vector2& a, const Vector2& b);
		friend Vector2 operator*(const Vector2& a, float b);
		friend Vector2 operator*(int a, const Vector2& b);
	};
}
#endif // 

