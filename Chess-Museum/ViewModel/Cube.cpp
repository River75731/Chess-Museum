#include "Cube.h"

Cube::Cube() {}

void Cube::draw() const
{
    View::DrawModel(ViewObjectType::CUBE, transform.coordinate, transform.translate, transform.angle, transform.axis, transform.scale);
}