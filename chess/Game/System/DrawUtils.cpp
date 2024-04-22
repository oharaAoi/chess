#include "DrawUtils.h"

Matrix3x3 DrawUtils::vpMatrix_{};

DrawUtils::DrawUtils(){}

DrawUtils::~DrawUtils(){}

void DrawUtils::Update(Matrix3x3 vpMatrix){
	vpMatrix_ = vpMatrix;
}

void DrawUtils::DrawQuad(const Matrix3x3& worldMatrix,
	const RectVerf& localVertex,
	const Vec2f& drawLT,
	const Vec2f& drawSize,
	const int& GH,
	const unsigned int& color){

	RectVerf screenVertex = MakeVertex(localVertex, Multiply(worldMatrix, vpMatrix_));

	Novice::DrawQuad(
		static_cast<int>(screenVertex.lt.x),
		static_cast<int>(screenVertex.lt.y),
		static_cast<int>(screenVertex.rt.x),
		static_cast<int>(screenVertex.rt.y),
		static_cast<int>(screenVertex.lb.x),
		static_cast<int>(screenVertex.lb.y),
		static_cast<int>(screenVertex.rb.x),
		static_cast<int>(screenVertex.rb.y),
		static_cast<int>(drawLT.x),
		static_cast<int>(drawLT.y),
		static_cast<int>(drawSize.x),
		static_cast<int>(drawSize.y),
		GH,
		color
	);
}
