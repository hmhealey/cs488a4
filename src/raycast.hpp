#ifndef __RAYCAST_HPP__
#define __RAYCAST_HPP__

#include "algebra.hpp"

struct RaycastHit {
    Point3D point;
};

bool raycastSphere(const Point3D& center, double radius, const Point3D& point, const Vector3& direction, RaycastHit& hit);

#endif
