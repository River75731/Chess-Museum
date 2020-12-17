#pragma once
#include <string>
#include <vector>
#include <memory>
#include <cmath>
#include "Position.h"
#include "Vector.h"
#include "Angle.h"

#include "Chess.h"
#include "ClassicChess.h"

const float floatError = 1e-7;

inline bool floatEqual(const float& x, const float& y) {
	return (x - y <= floatError) && (y - x <= floatError);
}