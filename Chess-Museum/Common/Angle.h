#pragma once

const float PI = 3.1415926535;

inline float toArc(const float& degree) {
	return degree * PI / 180;
}

inline float toDegree(const float& arc) {
	return arc * 180 / PI;
}