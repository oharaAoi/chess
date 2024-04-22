#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <assert.h>
#include "MyVector2.h"

struct Matrix3x3 {
	float m[3][3];
};

/*関数*/
/*拡縮行列*/
Matrix3x3 MakeScaleMatrix(Vec2f scale);

/*回転行列*/
Matrix3x3 MakeRotateMatrix(float theta);

/*平行移動行列*/
Matrix3x3 MakeTranslateMatrix(Vec2f translate);

/*アフィン*/
Matrix3x3 MakeAffineMatrix(Vec2f scale, float theta, Vec2f translate);

/*3x3の行列の積*/
Matrix3x3 Multiply(Matrix3x3 matrix1, Matrix3x3 matrix2);

/*2次元ベクトルを同次座標系として変換する*/
Vec2f Transform(Vec2f vector, Matrix3x3 matrix);

/*逆行列*/
Matrix3x3 Inverse(Matrix3x3 matrix);

//正射影行列
Matrix3x3 MakeOrthographicMatrix(float left, float top, float right, float bottom);

//ビューポート行列
Matrix3x3 MakeViewportMatrix(float left, float top, float width, float height);

// レンダリングパイプライン
Matrix3x3 MakeWvpVpMatrix(const Matrix3x3& worldMatrix, const Matrix3x3& view, const Matrix3x3 ortho, const Matrix3x3 viewport);