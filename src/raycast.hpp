#ifndef __RAYCAST_HPP__
#define __RAYCAST_HPP__

#include "algebra.hpp"

struct RaycastHit {
    Point3D point;
};

/** Casts a ray starting at point and heading in direction at a sphere centered at center and with radius radius. If the
 *  ray hits the sphere, hit is populated and true is returned. Otherwise, hit is unaffected and false is returned. **/
bool raycastSphere(const Point3D& center, double radius, const Point3D& point, const Vector3& direction, RaycastHit& hit);

/** Casts a ray starting at point and heading in direction at an axis-aligned box made up of planes at x = left, x = right,
 *  y = bottom, y = top, z = front, and z = back. If the ray hits the box, hit is populated and true is returned. OTherwise,
 *  hit is unaffected and false is returned. **/
bool raycastBox(double left, double right, double bottom, double top, double front, double back,
                const Point3D& point, const Vector3& direction, RaycastHit& hit);

#endif
