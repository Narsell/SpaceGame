#pragma once
#include <iostream>



class Vector2 {

public:

	float x, y;

	Vector2();

	Vector2(float xy);

	Vector2(float p_x, float p_y);

	const double Lenght() const;

	void Normalize();

	const Vector2& operator+(const Vector2& other) const;
	void operator+=(const Vector2& other);

	const Vector2& operator-(const Vector2& other) const;
	void operator-=(const Vector2& other);

	const Vector2& operator*(float scalar) const;
	void operator*=(float scalar);

	const Vector2& operator/(float scalar) const;

	void Print() const;

	// STATICS

	static Vector2 ZERO;
	static Vector2 RIGHT;
	static Vector2 LEFT;
	static Vector2 UP;
	static Vector2 DOWN;



};

class Math {

public:
	//Radians to Degrees conversion.
	static const double RadiansToDegrees(const double radians);
	//Degrees to Radians conversion.
	static const double DegreesToRadians(const double radians);
	//Gets a Vector2 direction from a given angle (degrees).
	static const Vector2& GetDirectionFromAngle(const float angle);
	//Gets an angle (degrees) in degs from a given Vector2 direction.
	static const double GetAngleFromDirection(const Vector2& direction);
};


