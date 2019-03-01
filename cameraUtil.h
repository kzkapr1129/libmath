#pragma once

#include "matrix.h"
#include "vector.h"
#include <math.h>

class CameraUtil {
public:
	static void genInnerParam(float focalLength, float kx, float ky,
		int imgWidth, int imgHeight, Matrix<float, 4, 4>& dst);

	static void genOuterParamXAxis(float radian, const Vector<float, 4>& t, Matrix<float, 4, 4>& dst);
	static void genOuterParamYAxis(float radian, const Vector<float, 4>& t, Matrix<float, 4, 4>& dst);
	static void genOuterParamZAxis(float radian, const Vector<float, 4>& t, Matrix<float, 4, 4>& dst);

	static void genImagePos(const Matrix<float, 4, 4>& innerParam,
			const Matrix<float, 4, 4>& outerParam,
			const Vector<float, 3>& worldPos,
			Vector<float, 3>& imgPos);

	static bool genWorldPos(const Matrix<float, 4, 4>& innerParam,
			const Matrix<float, 4, 4>& outerParam,
			const Vector<float, 3>& imgPos,
			Vector<float, 3>& worldPos);

private:
	CameraUtil() {}
};
