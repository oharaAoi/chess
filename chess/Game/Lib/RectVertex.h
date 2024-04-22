#pragma once
#include "MyVector2.h"

template <typename T>
class RectVertex{

public:

	T lt;
	T rt;
	T lb;
	T rb;

	RectVertex operator+(const RectVertex& obj)const {

	}


};

using RectVer = RectVertex<Vec2>;
using RectVerf = RectVertex<Vec2f>;
