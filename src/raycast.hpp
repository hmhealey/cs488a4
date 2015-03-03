#ifndef __RAYCAST_HPP__
#define __RAYCAST_HPP__

#include <vector>

#include "algebra.hpp"

struct Material;

struct RaycastHit {
    // the point at which the ray hit a surface
    Point3D point;

    // the normal at that point in the surface   
    Vector3 normal;

    // the material at that point on the surface
    Material* material;

    // transforms the properties of this hit (eg point, normal) by the provided matrix
    void transform(const Matrix4& transform, const Matrix4& inverse);
};

/** Casts a ray starting at point and heading in direction at a sphere centered at center and with radius radius. If the
 *  ray hits the sphere, hit is populated and true is returned. Otherwise, hit is unaffected and false is returned. **/
bool raycastSphere(const Point3D& center, double radius, const Point3D& point, const Vector3& direction, RaycastHit& hit);

/** Casts a ray starting at point and heading in direction at an axis-aligned box made up of planes at x = left, x = right,
 *  y = bottom, y = top, z = front, and z = back. If the ray hits the box, hit is populated and true is returned. Otherwise,
 *  hit is unaffected and false is returned. **/
bool raycastBox(double left, double right, double bottom, double top, double front, double back,
                const Point3D& point, const Vector3& direction, RaycastHit& hit);

/** Casts a ray starting at point and heading in direction at a triangle with corners p0, p1, and p2. If the ray hits the
 *  triangle, hit is populated and true is returned. Otherwise, hit is unaffected and false is returned. **/
bool raycastTriangle(const Point3D& p0, const Point3D& p1, const Point3D& p2, const Point3D& point, const Vector3& direction, RaycastHit& hit);

/** Casts a ray starting at point and heading in direction at an arbitrary polygon. Assumes that the points that make up
 *  the polygon are coplanar. If the ray hits the polgon, hit is populated and true is returned. Otherwise, hit is
 *  unaffected and false is returned. **/
bool raycastPolygon(const std::vector<int>& face, const std::vector<Point3D>& points, const Point3D& point, const Vector3& direction, RaycastHit& hit);

/** Casts a ray starting at point and heading in direction at an arbitrary polygon. Assumes that the points that make up
 *  the polygon are coplanar. If the ray hits the polgon, hit is populated and true is returned. Otherwise, hit is
 *  unaffected and false is returned. **/
bool raycastPolygon(const std::vector<Point3D>& points, const Point3D& point, const Vector3& direction, RaycastHit& hit);

#endif
