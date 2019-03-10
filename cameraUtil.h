#pragma once

#include "matrix.h"
#include "vector.h"
#include <math.h>

namespace camera {
	void genInnerParam(float focalLength, float kx, float ky,
		float width, float height, Matrix4f& dst);

	void genOuterParamXAxis(float radian, const Vector4f& t, Matrix4f& dst);
	void genOuterParamYAxis(float radian, const Vector4f& t, Matrix4f& dst);
	void genOuterParamZAxis(float radian, const Vector4f& t, Matrix4f& dst);
	void genOuterParamLookat(const Vector3f& eye, const Vector3f& at, const Vector3f& up, Matrix4f& matrix);

	bool extractOuterParamFromInOutMat(const Matrix4f& inoutMat, const Matrix4f& innerParam, Matrix4f& outParam);

	void genImagePos(const Matrix4f& innerParam,
			const Matrix4f& outerParam,
			const Vector3f& worldPos,
			Vector3f& imgPos);

	bool genWorldPos(const Matrix4f& innerParam,
			const Matrix4f& outerParam,
			const Vector3f& imgPos,
			Vector3f& worldPos,
			bool mulz = true);
};
