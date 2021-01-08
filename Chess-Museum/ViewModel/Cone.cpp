#include "Cone.h"

Cone::Cone() {}

void Cone::draw() const
{
    View::DrawModel(ViewObjectType::CONE, transform.coordinate, transform.translate, transform.angle, transform.axis, transform.scale);
}