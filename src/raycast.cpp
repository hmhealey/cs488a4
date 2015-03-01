#include "raycast.hpp"

#include "polyroots.hpp"

bool raycastSphere(const Point3D& center, double radius, const Point3D& point, const Vector3& direction, RaycastHit& hit) {
    Vector3 v = point - center;

    double roots[2];
    size_t numRoots = quadraticRoots(direction.dot(direction), 2 * direction.dot(v), v.dot(v) - radius * radius, roots);

    if (numRoots > 0) {
        hit.point = point + roots[0] * direction;
        return true;
    } else {
        return false;
    }
}
