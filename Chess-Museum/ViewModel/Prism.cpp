#include "Prism.h"

Prism::Prism(int a)
    : a(a)
{
}

void Prism::draw() const
{
    if (a == 3)
        View::DrawModel(ViewObjectType::PRISM3, transform.coordinate, transform.translate, transform.angle, transform.axis, transform.scale);
}