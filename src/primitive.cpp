#include "primitive.hpp"

#include <iostream>
#include <limits>

#include "polyroots.hpp"
#include "raycast.hpp"

using namespace std;

// --------------- Primitive ---------------

Primitive::~Primitive() { }

bool Primitive::raycast(const Point3D& point, const Vector3& direction, RaycastHit& hit) const {
    double t = getIntersection(point, direction);

    if (t > 0 && t != numeric_limits<double>::infinity()) {
        hit.point = point + t * direction;
        return true;
    } else {
        return false;
    }
}

// --------------- Sphere ---------------

Sphere::~Sphere() { }

double Sphere::getIntersection(const Point3D& point, const Vector3& direction) const {
    Vector3 v = point - Point3D::Zero;

    double roots[2];
    size_t numRoots = quadraticRoots(direction.dot(direction), 2 * direction.dot(v), v.dot(v) - 1, roots);

    if (numRoots > 0) {
        return roots[0];
    } else {
        return numeric_limits<double>::infinity();
    }
}

bool Sphere::raycast(const Point3D& point, const Vector3& direction, RaycastHit& hit) const {
    return raycastSphere(Point3D::Zero, 0, point, direction, hit);
}

// --------------- Cube ---------------

Cube::~Cube() { }

double Cube::getIntersection(const Point3D& point, const Vector3& direction) const {
    double ret = numeric_limits<double>::infinity();

    // left plane at x = 0
    {
        double t = (0 - point.x()) / direction.x();
        Point3D intersection = point + t * direction;

        if (intersection.y() >= 0 && intersection.y() <= 1 && intersection.z() >= 0 && intersection.z() <= 1) {
            ret = min(ret, t);
        }
    }

    // right plane at x = 1
    {
        double t = (1 - point.x()) / direction.x();
        Point3D intersection = point + t * direction;

        if (intersection.y() >= 0 && intersection.y() <= 1 && intersection.z() >= 0 && intersection.z() <= 1) {
            ret = min(ret, t);
        }
    }

    // bottom plane at y = 0
    {
        double t = (0 - point.y()) / direction.y();
        Point3D intersection = point + t * direction;

        if (intersection.x() >= 0 && intersection.x() <= 1 && intersection.z() >= 0 && intersection.z() <= 1) {
            ret = min(ret, t);
        }
    }

    // top plane at y = 1
    {
        double t = (1 - point.y()) / direction.y();
        Point3D intersection = point + t * direction;

        if (intersection.x() >= 0 && intersection.x() <= 1 && intersection.z() >= 0 && intersection.z() <= 1) {
            ret = min(ret, t);
        }
    }

    // front plane at z = 0
    {
        double t = (1 - point.z()) / direction.z();
        Point3D intersection = point + t * direction;

        if (intersection.x() >= 0 && intersection.x() <= 1 && intersection.y() >= 0 && intersection.y() <= 1) {
            ret = min(ret, t);
        }
    }

    return ret;
}

bool Cube::raycast(const Point3D& point, const Vector3& direction, RaycastHit& hit) const {
    return raycastBox(0, 1, 0, 1, 0, 1, point, direction, hit);
}

// --------------- NonhierSphere ---------------

NonhierSphere::NonhierSphere(const Point3D& center, double radius) : center(center), radius(radius) { }

NonhierSphere::~NonhierSphere() { }

double NonhierSphere::getIntersection(const Point3D& point, const Vector3& direction) const {
    Vector3 v = point - center;

    double roots[2];
    size_t numRoots = quadraticRoots(direction.dot(direction), 2 * direction.dot(v), v.dot(v) - radius * radius, roots);

    if (numRoots > 0) {
        return roots[0];
    } else {
        return numeric_limits<double>::infinity();
    }
}

bool NonhierSphere::raycast(const Point3D& point, const Vector3& direction, RaycastHit& hit) const {
    return raycastSphere(center, radius, point, direction, hit);
}

// --------------- NonhierBox ---------------

NonhierBox::NonhierBox(const Point3D& pos, double size) : pos(pos), size(size) { }

NonhierBox::~NonhierBox() { }

double NonhierBox::getIntersection(const Point3D& point, const Vector3& direction) const {
    double ret = numeric_limits<double>::infinity();

    // left plane at x = pos.x
    {
        double t = (pos.x() - point.x()) / direction.x();
        Point3D intersection = point + t * direction;

        if (intersection.y() >= pos.y() && intersection.y() <= pos.y() + size && intersection.z() >= pos.z() && intersection.z() <= pos.z() + size) {
            ret = min(ret, t);
        }
    }

    // right plane at x = pos.x + size
    {
        double t = (pos.x() + size - point.x()) / direction.x();
        Point3D intersection = point + t * direction;

        if (intersection.y() >= pos.y() && intersection.y() <= pos.y() + size && intersection.z() >= pos.z() && intersection.z() <= pos.z() + size) {
            ret = min(ret, t);
        }
    }

    // bottom plane at y = pos.y
    {
        double t = (pos.y() - point.y()) / direction.y();
        Point3D intersection = point + t * direction;

        if (intersection.x() >= pos.x() && intersection.x() <= pos.x() + size && intersection.z() >= pos.z() && intersection.z() <= pos.z() + size) {
            ret = min(ret, t);
        }
    }

    // top plane at y = pos.y + size
    {
        double t = (pos.y() + size - point.y()) / direction.y();
        Point3D intersection = point + t * direction;

        if (intersection.x() >= pos.x() && intersection.x() <= pos.x() + size && intersection.z() >= pos.z() && intersection.z() <= pos.z() + size) {
            ret = min(ret, t);
        }
    }

    // front plane at z = pos.z
    {
        double t = (pos.z() - point.z()) / direction.z();
        Point3D intersection = point + t * direction;

        if (intersection.x() >= pos.x() && intersection.x() <= pos.x() + size && intersection.y() >= pos.y() && intersection.y() <= pos.y() + size) {
            ret = min(ret, t);
        }
    }

    // back plane at z = pos.z + size
    {
        double t = (pos.z() + size - point.z()) / direction.z();
        Point3D intersection = point + t * direction;

        if (intersection.x() >= pos.x() && intersection.x() <= pos.x() + size && intersection.y() >= pos.y() && intersection.y() <= pos.y() + size) {
            ret = min(ret, t);
        }
    }

    return ret;
}

bool NonhierBox::raycast(const Point3D& point, const Vector3& direction, RaycastHit& hit) const {
    return raycastBox(pos.x(), pos.x() + size, pos.y(), pos.y() + size, pos.z(), pos.z() + size, point, direction, hit);
}
