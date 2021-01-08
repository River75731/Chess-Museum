#include "Cylinder.h"

Cylinder::Cylinder() {}

void Cylinder::draw() const
{
    View::DrawModel(ViewObjectType::CYLINDER, transform.coordinate, transform.translate, transform.angle, transform.axis, transform.scale);
}