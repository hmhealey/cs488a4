#include "primitive.hpp"

Primitive::~Primitive() { }

Sphere::~Sphere() { }

Cube::~Cube() { }

NonhierSphere::NonhierSphere(const Point3D& pos, double radius) : pos(pos), radius(radius) { }

NonhierSphere::~NonhierSphere() { }

NonhierBox::NonhierBox(const Point3D& pos, double size) : pos(pos), size(size) { }

NonhierBox::~NonhierBox() { }
