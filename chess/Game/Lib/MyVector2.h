#pragma once

template <typename T>
class MyVector2{

public:

	T x, y;

	// ベクトルの加算
	MyVector2 operator+(const MyVector2& obj)const {
		return MyVector2(x + obj.x, y + obj.y);
	}

	MyVector2 operator+(const float& obj)const {
		return MyVector2(x + obj, y + obj);
	}

	MyVector2 operator += (const MyVector2 & obj) {
		x += obj.x;
		y += obj.y;
		return *this;
	}

	MyVector2 operator += (const float& obj) {
		x = x + obj;
		y = y + obj;
		return *this;
	}

	// ベクトルの減算
	MyVector2 operator-(const MyVector2& obj)const{
		return MyVector2(x - obj.x, y - obj.y);
	}

	MyVector2 operator-(const float& obj)const {
		return MyVector2(x - obj, y - obj);
	}

	MyVector2 operator -= (const float& obj) {
		x -= obj;
		y -= obj;
		return *this;
	}

	MyVector2 operator-= (const MyVector2 & obj) {
		x -= obj.x;
		y -= obj.y;
		return *this;
	}

	// ベクトルの乗算
	MyVector2 operator*(const MyVector2& obj)const {
		return MyVector2(x * obj.x, y * obj.y);
	}

	MyVector2 operator*=(const MyVector2& obj){
		x *= obj.x;
		y *= obj.y;
		return  *this;
	}

	// ベクトルの除算
	MyVector2 operator/(const MyVector2 & obj)const {
		return MyVector2(x / obj.x, y / obj.y);
	}

	MyVector2 operator/=(const MyVector2& obj)const {
		x /= obj.x;
		y /= obj.y;
		return  *this;
	}
};

using Vec2f = MyVector2<float>;
using Vec2 = MyVector2<int>;
