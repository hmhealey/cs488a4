#include "primitive.hpp"

#include <limits>

#include "polyroots.hpp"

using namespace std;

// --------------- Primitive ---------------

Primitive::~Primitive() { }

// --------------- Sphere ---------------

Sphere::~Sphere() { }

double Sphere::getIntersection(const Point3D& point, const Vector3& direction) const {
    Vector3 v = point - Point3D::Zero;

    double roots[2];
    size_t numRoots = quadraticRoots(direction.dot(direction), direction.dot(v), v.dot(v), roots);

    if (numRoots > 0) {
        return roots[0];
    } else {
        return numeric_limits<double>::infinity();
    }
}

// --------------- Cube ---------------

Cube::~Cube() { }

double Cube::getIntersection(const Point3D& point, const Vector3& direction) const {
    // TODO
    (void) point;
    (void) direction;
    return numeric_limits<double>::infinity();
}

// --------------- NonhierSphere ---------------

NonhierSphere::NonhierSphere(const Point3D& center, double radius) : center(center), radius(radius) { }

NonhierSphere::~NonhierSphere() { }

double NonhierSphere::getIntersection(const Point3D& point, const Vector3& direction) const {
    Vector3 v = point - center;

    double roots[2];
    size_t numRoots = quadraticRoots(direction.dot(direction), direction.dot(v), v.dot(v), roots);

    if (numRoots > 0) {
        return roots[0];
    } else {
        return numeric_limits<double>::infinity();
    }
}

// --------------- NonhierBox ---------------

NonhierBox::NonhierBox(const Point3D& pos, double size) : pos(pos), size(size) { }

NonhierBox::~NonhierBox() { }

double NonhierBox::getIntersection(const Point3D& point, const Vector3& direction) const {
    // TODO
    (void) point;
    (void) direction;
    return numeric_limits<double>::infinity();
}
