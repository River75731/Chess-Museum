#include "ClassicChess.h"

bool ClassicChessPosition::isValid()
{
	return (x >= 1) && (x <= 8) && (y >= 1) && (y <= 8);
}
