#pragma once
#include "Matrix.h"
#include "MyVector2.h"
#include "MyMath.h"
#include "EaseStruct.h"
#include "MyRandom.h"

#ifdef _DEBUG
#include "ImGuiManager.h"
#endif

class Camera{

private:

	Vec2f pos_;

	float left_;
	float top_;

	float right_;
	float bottom_;

	float width_;
	float height_;

	Matrix3x3 cameraWorldMatrix2{};

	//ビュー行列
	Matrix3x3 viewMatrix{};
	//正射影行列
	Matrix3x3 orthoMatrix{};
	//ビューポート行列
	Matrix3x3 viewportMatrix{};

	Matrix3x3 vpMatrix{};

	//逆ビュー行列
	Matrix3x3 InverseViewMatrix{};
	//逆正射影行列
	Matrix3x3 InverseOrthoMatrix{};
	//逆ビューポート行列
	Matrix3x3 InverseViewportMatrix{};

public:

	Camera();

	void Init();
	void Update();
	void Draw();

	Vec2f Unproject(Vec2f screenCoordinates);

	Matrix3x3 GetViewMatrix()const { return viewMatrix; }
	Matrix3x3 GetOrthoMatrix()const { return orthoMatrix; }
	Matrix3x3 GetViewportMatrix()const { return viewportMatrix; }

public:

	Matrix3x3 GetVpMatrix() const { return vpMatrix; }

};

