#pragma once

#include "matrix.h"
#include "vector.h"
#include <math.h>

class CameraUtil {
public:
	static void genInnerParam(float focalLength, float kx, float ky,
		int imgWidth, int imgHeight, Matrix4f& dst);

	static void genOuterParamXAxis(float radian, const Vector4f& t, Matrix4f& dst);
	static void genOuterParamYAxis(float radian, const Vector4f& t, Matrix4f& dst);
	static void genOuterParamZAxis(float radian, const Vector4f& t, Matrix4f& dst);

	static void genImagePos(const Matrix4f& innerParam,
			const Matrix4f& outerParam,
			const Vector3f& worldPos,
			Vector3f& imgPos);

	static bool genWorldPos(const Matrix4f& innerParam,
			const Matrix4f& outerParam,
			const Vector3f& imgPos,
			Vector3f& worldPos);

private:
	CameraUtil() {}
};
