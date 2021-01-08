#include "Sphere.h"

Sphere::Sphere() {}

void Sphere::draw() const
{
    View::DrawModel(ViewObjectType::SPHERE, transform.coordinate, transform.translate, transform.angle, transform.axis, transform.scale);
}