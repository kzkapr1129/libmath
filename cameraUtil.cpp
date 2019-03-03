#include "cameraUtil.h"

// focalLength, width, heightについては「genInnerParam_tool.xlsx」参照
void CameraUtil::genInnerParam(float focalLength, float kx, float ky,
		float width, float height, Matrix4f& dst) {

	dst.values[0][0] = focalLength * kx;  // FKx
	dst.values[0][1] = 0;
	dst.values[0][2] = width / 2.f;    // cx
	dst.values[0][3] = 0;

	dst.values[1][0] = 0;
	dst.values[1][1] = -focalLength * ky; // FKy
	dst.values[1][2] = height / 2.f;   // cy
	dst.values[1][3] = 0;

	dst.values[2][0] = 0;
	dst.values[2][1] = 0;
	dst.values[2][2] = 1;
	dst.values[2][3] = 0;

	dst.values[3][0] = 0;
	dst.values[3][1] = 0;
	dst.values[3][2] = 0;
	dst.values[3][3] = 1;
}

void CameraUtil::genOuterParamXAxis(float radian,
		const Vector4f& t, Matrix4f& dst) {
	dst.values[0][0] = 1;
	dst.values[0][1] = 0;
	dst.values[0][2] = 0;
	dst.values[0][3] = t.values[0];

	dst.values[1][0] = 0;
	dst.values[1][1] = cosf(radian);
	dst.values[1][2] = -sinf(radian);
	dst.values[1][3] = t.values[1];

	dst.values[2][0] = 0;
	dst.values[2][1] = sinf(radian);
	dst.values[2][2] = cosf(radian);
	dst.values[2][3] = t.values[2];

	dst.values[3][0] = 0;
	dst.values[3][1] = 0;
	dst.values[3][2] = 0;
	dst.values[3][3] = t.values[3];
}

void CameraUtil::genOuterParamYAxis(float radian,
		const Vector4f& t, Matrix4f& dst) {
	dst.values[0][0] = cosf(radian);
	dst.values[0][1] = 0;
	dst.values[0][2] = sinf(radian);
	dst.values[0][3] = t.values[0];

	dst.values[1][0] = 0;
	dst.values[1][1] = 1;
	dst.values[1][2] = 0;
	dst.values[1][3] = t.values[1];

	dst.values[2][0] = -sinf(radian);
	dst.values[2][1] = 0;
	dst.values[2][2] = cosf(radian);
	dst.values[2][3] = t.values[2];

	dst.values[3][0] = 0;
	dst.values[3][1] = 0;
	dst.values[3][2] = 0;
	dst.values[3][3] = t.values[3];
}

void CameraUtil::genOuterParamZAxis(float radian,
		const Vector4f& t, Matrix4f& dst) {
	dst.values[0][0] = cosf(radian);
	dst.values[0][1] = -sinf(radian);
	dst.values[0][2] = 0;
	dst.values[0][3] = t.values[0];

	dst.values[1][0] = sinf(radian);
	dst.values[1][1] = cosf(radian);
	dst.values[1][2] = 0;
	dst.values[1][3] = t.values[1];

	dst.values[2][0] = 0;
	dst.values[2][1] = 0;
	dst.values[2][2] = 1;
	dst.values[2][3] = t.values[2];

	dst.values[3][0] = 0;
	dst.values[3][1] = 0;
	dst.values[3][2] = 0;
	dst.values[3][3] = t.values[3];
}

void CameraUtil::genImagePos(const Matrix4f& innerParam,
			const Matrix4f& outerParam,
			const Vector3f& worldPos,
			Vector3f& imgPos) {

	// カメラ座標 = 外部パラメータ * ワールド座表
	Vector<float, 4> cameraPos = {
		worldPos.values[0],
		worldPos.values[1],
		worldPos.values[2], 1};

	cameraPos.mulMV(outerParam);

	// 画像座標 = 内部パラメータ * 外部パラメータ * ワールド座表
	Vector<float, 4> imagePos(cameraPos);
	imagePos.mulMV(innerParam);

	imgPos.values[0] = imagePos.values[0] / imagePos.values[2];
	imgPos.values[1] = imagePos.values[1] / imagePos.values[2];
}

bool CameraUtil::genWorldPos(const Matrix4f& innerParam,
			const Matrix4f& outerParam,
			const Vector3f& imgPos,
			Vector3f& worldPos) {

	Vector<float, 4> projPos = {
		imgPos.values[0] * imgPos.values[2],
		imgPos.values[1] * imgPos.values[2],
		imgPos.values[2], 1};

	Matrix<float, 4, 4> imatrix;
	innerParam.mulMM(outerParam, imatrix);

	bool ret = imatrix.inverse();
	if (!ret) return false;

	projPos.mulMV(imatrix);

	worldPos.values[0] = projPos.values[0];
	worldPos.values[1] = projPos.values[1];
	worldPos.values[2] = projPos.values[2];

	return true;
}