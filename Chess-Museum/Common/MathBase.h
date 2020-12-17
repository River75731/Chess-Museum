#pragma once

const float PI = (float)3.1415926535;

inline float toArc(const float& degree) {
	return degree * PI / 180;
}

inline float toDegree(const float& arc) {
	return arc * 180 / PI;
}

const float floatError = (float)1e-7;

inline bool floatEqual(const float& x, const float& y) {
	return (x - y <= floatError) && (y - x <= floatError);
}