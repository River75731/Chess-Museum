#include "Circle.h"

Circle::Circle() {}

void Circle::draw() const
{
    View::DrawModel(ViewObjectType::CIRCLE, transform.coordinate, transform.translate, transform.angle, transform.axis, transform.scale);
}