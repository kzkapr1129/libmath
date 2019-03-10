#include "cameraUtil.h"

// focalLength, width, heightについては「genInnerParam_tool.xlsx」参照
void camera::genInnerParam(float focalLength, float kx, float ky,
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

void camera::genOuterParamXAxis(float radian,
		const Vector4f& t, Matrix4f& dst) {

	Matrix4f rote;
	rote.identity();
	rote.values[1][1] = cosf(radian);
	rote.values[1][2] = -sinf(radian);
	rote.values[2][1] = sinf(radian);
	rote.values[2][2] = cosf(radian);

	Matrix4f translate;
	translate.identity();
	translate.values[3][0] = -t.values[0];
	translate.values[3][1] = -t.values[1];
	translate.values[3][2] = -t.values[2];

	translate.mulMM(rote, dst);
}

void camera::genOuterParamYAxis(float radian,
		const Vector4f& t, Matrix4f& dst) {

	Matrix4f rote;
	rote.identity();
	rote.values[0][0] = cosf(radian);
	rote.values[0][2] = sinf(radian);
	rote.values[2][0] = -sinf(radian);
	rote.values[2][2] = cosf(radian);

	Matrix4f translate;
	translate.identity();
	translate.values[3][0] = -t.values[0];
	translate.values[3][1] = -t.values[1];
	translate.values[3][2] = -t.values[2];

	translate.mulMM(rote, dst);
}

void camera::genOuterParamZAxis(float radian,
		const Vector4f& t, Matrix4f& dst) {

	Matrix4f rote;
	rote.identity();
	rote.values[0][0] = cosf(radian);
	rote.values[0][1] = -sinf(radian);
	rote.values[1][0] = sinf(radian);
	rote.values[1][1] = cosf(radian);

	Matrix4f translate;
	translate.identity();
	translate.values[3][0] = -t.values[0];
	translate.values[3][1] = -t.values[1];
	translate.values[3][2] = -t.values[2];

	translate.mulMM(rote, dst);
}

void camera::genOuterParamLookat(const Vector3f& eye, const Vector3f& at,
	    const Vector3f& up, Matrix4f& ret) {

	Vector3f zAxis = eye - at;
	zAxis.normalize();

	Vector3f xAxis;
	up.cross(zAxis, xAxis);

	Vector3f yAxis;
	zAxis.cross(xAxis, yAxis);

	xAxis.normalize();
	yAxis.normalize();

	Matrix4f rote;
	rote.identity();
	rote.values[0][0] = xAxis.values[0];
	rote.values[1][0] = xAxis.values[1];
	rote.values[2][0] = xAxis.values[2];

	rote.values[0][1] = yAxis.values[0];
	rote.values[1][1] = yAxis.values[1];
	rote.values[2][1] = yAxis.values[2];

	rote.values[0][2] = zAxis.values[0];
	rote.values[1][2] = zAxis.values[1];
	rote.values[2][2] = zAxis.values[2];

	Matrix4f translate;
	translate.identity();
	translate.values[3][0] = -eye.values[0];
	translate.values[3][1] = -eye.values[1];
	translate.values[3][2] = -eye.values[2];

	translate.mulMM(rote, ret);
}

bool camera::extractOuterParamFromInOutMat(const Matrix4f& inoutMat,
		const Matrix4f& innerParam, Matrix4f& outParam) {

	Matrix4f invInnerParam;

	// 内部パラメータの逆行列を取得
    if (!innerParam.inverse(invInnerParam)) {
		return false;
	}

	// InnerParam * OuterParam行列からOuterParam行列を取り出す
    invInnerParam.mulMM(inoutMat, outParam);

	return true;
}

void camera::genImagePos(const Matrix4f& innerParam,
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

bool camera::genWorldPos(const Matrix4f& innerParam,
			const Matrix4f& outerParam,
			const Vector3f& imgPos,
			Vector3f& worldPos,
			bool mulz) {

	Vector<float, 4> projPos = {
		imgPos.values[0],
		imgPos.values[1],
		imgPos.values[2],
		1
	};

	if (mulz) {
		projPos.values[0] *= projPos.values[2];
		projPos.values[1] *= projPos.values[2];
	}

	projPos.values[2] = imgPos.values[2];
	projPos.values[3] = 1;

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