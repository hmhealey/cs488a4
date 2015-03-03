#include "primitive.hpp"

#include "raycast.hpp"

using namespace std;

// --------------- Primitive ---------------

Primitive::~Primitive() { }

const Primitive* Primitive::getBounds() const {
    return this;
}

// --------------- Sphere ---------------

Sphere::~Sphere() { }

bool Sphere::raycast(const Point3D& point, const Vector3& direction, RaycastHit& hit) const {
    return raycastSphere(Point3D::Zero, 1, point, direction, hit);
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

NonhierSphere* NonhierSphere::makeBoundingSphere(const vector<Point3D>& points) {
    // find the average of all points in the mesh to use as the center of the bounding sphere
    Point3D center;

    for (auto i = points.cbegin(); i != points.cend(); i++) {
        center.x() += i->x();
        center.y() += i->y();
        center.z() += i->z();
    }

    center.x() /= points.size();
    center.y() /= points.size();
    center.z() /= points.size();

    // find the distance to the furthest point to use as the radius
    double radius = 0;

    for (auto i = points.cbegin(); i != points.cend(); i++) {
        radius = max(radius, (center - *i).length());
    }

    return new NonhierSphere(center, radius);
}

// --------------- NonhierBox ---------------

NonhierBox::NonhierBox(const Point3D& pos, double size) : left(pos.x()), right(pos.x() + size),
        bottom(pos.y()), top(pos.y() + size), front(pos.z()), back(pos.z() + size) { }

NonhierBox::NonhierBox(double left, double right, double bottom, double top, double front, double back) 
        : left(left), right(right), bottom(bottom), top(top), front(front), back(back) { }

NonhierBox::~NonhierBox() { }

bool NonhierBox::raycast(const Point3D& point, const Vector3& direction, RaycastHit& hit) const {
    return raycastBox(left, right, bottom, top, front, back, point, direction, hit);
}

NonhierBox* NonhierBox::makeBoundingBox(const vector<Point3D>& points) {
    double left = numeric_limits<double>::max();
    double right = -numeric_limits<double>::max();
    double bottom = numeric_limits<double>::max();
    double top = -numeric_limits<double>::max();
    double front = numeric_limits<double>::max();
    double back = -numeric_limits<double>::max();

    for (auto i = points.cbegin(); i != points.cend(); i++) {
        left = min(left, i->x());
        right = max(right, i->x());
        bottom = min(bottom, i->y());
        top = max(top, i->y());
        front = min(front, i->z());
        back = max(back, i->z());
    }

    // make sure that the box is actually 3d so that lighting works right
    if (left == right) {
        left -= 0.0001;
        right += 0.0001;
    }
    if (bottom == top) {
        bottom -= 0.0001;
        top += 0.0001;
    }
    if (front == back) {
        front -= 0.0001;
        top += 0.0001;
    }

    return new NonhierBox(left, right, bottom, top, front, back);
}
