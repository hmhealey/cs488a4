#include "primitive.hpp"

#include "raycast.hpp"

// --------------- Primitive ---------------

Primitive::~Primitive() { }

// --------------- Sphere ---------------

Sphere::~Sphere() { }

bool Sphere::raycast(const Point3D& point, const Vector3& direction, RaycastHit& hit) const {
    return raycastSphere(Point3D::Zero, 0, point, direction, hit);
}

// --------------- Cube ---------------

Cube::~Cube() { }

bool Cube::raycast(const Point3D& point, const Vector3& direction, RaycastHit& hit) const {
    return raycastBox(0, 1, 0, 1, 0, 1, point, direction, hit);
}

// --------------- NonhierSphere ---------------

NonhierSphere::NonhierSphere(const Point3D& center, double radius) : center(center), radius(radius) { }

NonhierSphere::~NonhierSphere() { }

bool NonhierSphere::raycast(const Point3D& point, const Vector3& direction, RaycastHit& hit) const {
    return raycastSphere(center, radius, point, direction, hit);
}

// --------------- NonhierBox ---------------

NonhierBox::NonhierBox(const Point3D& pos, double size) : pos(pos), size(size) { }

NonhierBox::~NonhierBox() { }

bool NonhierBox::raycast(const Point3D& point, const Vector3& direction, RaycastHit& hit) const {
    return raycastBox(pos.x(), pos.x() + size, pos.y(), pos.y() + size, pos.z(), pos.z() + size, point, direction, hit);
}
