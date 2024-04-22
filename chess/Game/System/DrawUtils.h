#pragma once
#include "Novice.h"
#include "RectVertex.h"
#include "MyMath.h"
#include <memory>

class DrawUtils{
public:

	DrawUtils();
	~DrawUtils();

	void Update(Matrix3x3 vpMatrix);

	/// <summary>
	/// Quadの描画
	/// </summary>
	/// <param name="worldMatrix">行列</param>
	/// <param name="localVertex">local頂点</param>
	/// <param name="drawLT">描画する左上座標</param>
	/// <param name="drawSize">描画する範囲</param>
	/// <param name="GH">画像</param>
	/// <param name="color">色</param>
	static void DrawQuad(const Matrix3x3& worldMatrix,
		const RectVerf& localVertex,
		const Vec2f& drawLT,
		const Vec2f& drawSize,
		const int& GH,
		const unsigned int& color);

private:

	static Matrix3x3 vpMatrix_;
	
};

