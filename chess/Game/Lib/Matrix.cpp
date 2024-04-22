#include "Matrix.h"

//拡縮行列
Matrix3x3 MakeScaleMatrix(Vec2f scale) {
	Matrix3x3 result{};
	result.m[0][0] = scale.x;
	result.m[1][1] = scale.y;
	result.m[2][2] = 1;

	return result;
}

/*回転行列*/
Matrix3x3 MakeRotateMatrix(float theta) {
	Matrix3x3 result{};
	result.m[0][0] = cosf(theta);
	result.m[0][1] = sinf(theta);
	result.m[1][0] = -sinf(theta);
	result.m[1][1] = cosf(theta);
	result.m[2][2] = 1;

	return result;
}

/*平行移動行列*/
Matrix3x3 MakeTranslateMatrix(Vec2f translate) {
	Matrix3x3 result{};
	result.m[0][0] = 1;
	result.m[1][1] = 1;
	result.m[2][0] = translate.x;
	result.m[2][1] = translate.y;
	result.m[2][2] = 1;

	return result;
}

/*アフィン*/
Matrix3x3 MakeAffineMatrix(Vec2f scale, float theta, Vec2f translate) {
	Matrix3x3 scaleMatrix{};
	Matrix3x3 rotateMatrix{};
	Matrix3x3 translateMatrix{};
	Matrix3x3 worldMatrix{};

	scaleMatrix = MakeScaleMatrix(scale);
	rotateMatrix = MakeRotateMatrix(theta);
	translateMatrix = MakeTranslateMatrix(translate);

	worldMatrix = Multiply(Multiply(scaleMatrix, rotateMatrix), translateMatrix);

	return worldMatrix;

}

//3x3の行列の積
Matrix3x3 Multiply(Matrix3x3 matrix1, Matrix3x3 matrix2) {
	Matrix3x3 result{};
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			for (int i = 0; i < 3; i++) {
				result.m[row][col] += matrix1.m[row][i] * matrix2.m[i][col];
			}
		}
	}

	return result;
}

//2次元ベクトルを同次座標系として変換する
Vec2f Transform(Vec2f vector, Matrix3x3 matrix) {
	Vec2f result;//w=1がデカルト座標系であるので(x,y1)のベクトルとしてmatrixとの積をとる
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + 1.0f * matrix.m[2][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + 1.0f * matrix.m[2][1];
	float w = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + 1.0f * matrix.m[2][2];
	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;

	return result;
}

//3x3の逆行列
Matrix3x3 Inverse(Matrix3x3 matrix) {
	Matrix3x3 result{};
	//行列式を求める
	float determinant = 0;
	float element[6] = { 0 };
	element[0] = matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][2];
	element[1] = matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][1];
	element[2] = matrix.m[0][2] * matrix.m[1][0] * matrix.m[2][1];
	element[3] = matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][0];
	element[4] = matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][2];
	element[5] = matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][1];

	for (int i = 0; i < 6; i++) {
		if (i <= 2) {
			determinant += element[i];
		} else {
			determinant -= element[i];
		}
	}

	//逆行列を求める
	result.m[0][0] = (matrix.m[1][1] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][1]) / determinant;
	result.m[0][1] = -(matrix.m[0][1] * matrix.m[2][2] - matrix.m[0][2] * matrix.m[2][1]) / determinant;
	result.m[0][2] = (matrix.m[0][1] * matrix.m[1][2] - matrix.m[0][2] * matrix.m[1][1]) / determinant;
	result.m[1][0] = -(matrix.m[1][0] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][0]) / determinant;
	result.m[1][1] = (matrix.m[0][0] * matrix.m[2][2] - matrix.m[0][2] * matrix.m[2][0]) / determinant;
	result.m[1][2] = -(matrix.m[0][0] * matrix.m[1][2] - matrix.m[0][2] * matrix.m[1][0]) / determinant;
	result.m[2][0] = (matrix.m[1][0] * matrix.m[2][1] - matrix.m[1][1] * matrix.m[2][0]) / determinant;
	result.m[2][1] = -(matrix.m[0][0] * matrix.m[2][1] - matrix.m[0][1] * matrix.m[2][0]) / determinant;
	result.m[2][2] = (matrix.m[0][0] * matrix.m[1][1] - matrix.m[0][1] * matrix.m[1][0]) / determinant;

	return result;
}

//正射影行列
Matrix3x3 MakeOrthographicMatrix(float left, float top, float right, float bottom) {
	Matrix3x3 result{};
	result.m[0][0] = 2.0f / (right - left);
	result.m[1][1] = 2.0f / (top - bottom);
	result.m[2][0] = (left + right) / (left - right);
	result.m[2][1] = (top + bottom) / (bottom - top);
	result.m[2][2] = 1;

	return result;
}

//ビューポート行列
Matrix3x3 MakeViewportMatrix(float left, float top, float width, float height) {
	Matrix3x3 result{};
	result.m[0][0] = width / 2.0f;
	result.m[1][1] = -(height / 2.0f);
	result.m[2][0] = left + (width / 2.0f);
	result.m[2][1] = top + (height / 2.0f);
	result.m[2][2] = 1;

	return result;
}

// レンダリングパイプライン
Matrix3x3 MakeWvpVpMatrix(const Matrix3x3& worldMatrix, const Matrix3x3& view, const Matrix3x3 ortho, const Matrix3x3 viewport) {
	Matrix3x3 result;

	result = Multiply(worldMatrix, view);
	result = Multiply(result, ortho);
	result = Multiply(result, viewport);

	return result;
}