#pragma once
#include "../Common/Common.h"

void testVectorPosition() 
{
	Vector2f A(1, 3), B;
	Position2f P(4, 4), Q(5,6);
	A.output("A");
	B.output("B");
	P.output("P");
	Q.output("Q");
	(P - Q).output("P-Q");
	(A *= 4).output("newA");
	B.setX(3).setY(4).output("newB");
	(Q + A / 3).output("Q+A/3");
	return;
}