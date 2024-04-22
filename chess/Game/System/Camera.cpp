#include "Camera.h"

Camera::Camera() {
	Init();
}

void Camera::Init() {

	pos_.x = 256.0f;
	pos_.y = 256.0f;

	left_ = -640.0f;
	top_ = 360.0f;

	right_ = 640.0f;
	bottom_ = -360.0f;

	width_ = 1280.0f;
	height_ = 720.0f;

	cameraWorldMatrix2.m[0][0] = 1.0f;
	cameraWorldMatrix2.m[1][1] = 1.0f;
	cameraWorldMatrix2.m[2][0] = pos_.x;
	cameraWorldMatrix2.m[2][1] = pos_.y;
	cameraWorldMatrix2.m[2][2] = 1;

	viewMatrix = Inverse(cameraWorldMatrix2);
	//カメラの正射影行列を作成
	orthoMatrix = MakeOrthographicMatrix(left_, top_, right_, bottom_);
	//カメラのビューポート行列を作成
	viewportMatrix = MakeViewportMatrix(0.0f, 0.0f, width_, height_);

	vpMatrix = Multiply(viewMatrix, Multiply(orthoMatrix, viewportMatrix));
}

void Camera::Update() {

	cameraWorldMatrix2.m[0][0] = 1;
	cameraWorldMatrix2.m[1][1] = 1;
	cameraWorldMatrix2.m[2][0] = pos_.x;
	cameraWorldMatrix2.m[2][1] = pos_.y;
	cameraWorldMatrix2.m[2][2] = 1;

	//カメラのビュー行列を作成
	viewMatrix = Inverse(cameraWorldMatrix2);
	//カメラの正射影行列を作成
	orthoMatrix = MakeOrthographicMatrix(left_, top_, right_, bottom_);
	//カメラのビューポート行列を作成
	viewportMatrix = MakeViewportMatrix(0.0f, 0.0f, width_, height_);
	// 
	vpMatrix = Multiply(viewMatrix, Multiply(orthoMatrix, viewportMatrix));

	//カメラのビュー行列を作成
	InverseViewMatrix = Inverse(viewMatrix);
	//カメラの正射影行列を作成
	InverseOrthoMatrix = Inverse(orthoMatrix);
	//カメラのビューポート行列を作成
	InverseViewportMatrix = Inverse(viewportMatrix);
}

void Camera::Draw() {
	/*Novice::ScreenPrintf(10, 400, "cameraPos.x:%f", pos_.x);
	Novice::ScreenPrintf(10, 420, "cameraPos.y:%f", pos_.y);*/

#ifdef _DEBUG

	ImGui::Begin("Camera");

	ImGui::SliderFloat("left", &left_, -1280.0f, -640.0f);
	ImGui::SliderFloat("right", &right_, 640.0f, 1280.0f);
	ImGui::SliderFloat("top", &top_, 360.0f, 640.0f);
	ImGui::SliderFloat("bottom", &bottom_, -640.0f, -360.0f);

	ImGui::End();

#endif

}

Vec2f Camera::Unproject(Vec2f screenCoordinates) {
	Vec2f normalizedDeviceCoordinates = { 0.0f, 0.0f };

	normalizedDeviceCoordinates = Transform(screenCoordinates, InverseViewportMatrix);

	Vec2f viewCoord = Transform(normalizedDeviceCoordinates, InverseOrthoMatrix);

	Vec2f  worldCoord = Transform(viewCoord, InverseViewMatrix);

	return  worldCoord;
}
