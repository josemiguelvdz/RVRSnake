#include "Vector2.h"
#include <math.h>

Vector2::Vector2() {
	x = 0;
	y = 0;
}

Vector2::Vector2(float a, float b) {
	x = a;
	y = b;
}

Vector2::Vector2(const Vector2& v) {
	x = v.x;
	y = v.y;
}

Vector2 Vector2::operator+(const  Vector2& v) {
	return Vector2(x + v.x, y + v.y);
}

Vector2 Vector2::operator-(const  Vector2& v) {
	return Vector2(x - v.x, y - v.y);
}

Vector2 Vector2::operator*(const float v) {
	return Vector2(x * v, y * v);
}

Vector2 Vector2::operator*(const int v) {
	return Vector2(x * v, y * v);
}

Vector2 Vector2::lerp(const Vector2 a, const Vector2 b, float f)
{
	return Vector2(SimpleLerp::Lerp(a.x, b.x, f), SimpleLerp::Lerp(a.y, b.y, f));
}

void Vector2::operator=(const Vector2 & v)
{
	x = v.x;
	y = v.y;
}

void Vector2::operator=(const Vector2 * v)
{
	x = v->x;
	y = v->y;
}

bool Vector2::operator==(const Vector2 & v)
{
	return (x == v.x && y == v.y);
}

bool Vector2::operator!=(const Vector2& v)
{
	return (x != v.x || y != v.y);
}

float Vector2::magnitude()
{
	return sqrt(x * x + y * y);
}

float Vector2::distance(const Vector2& v)
{
	return Vector2(v.x - x, v.y - y).magnitude();
}

