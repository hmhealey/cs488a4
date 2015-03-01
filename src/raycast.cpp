#include "raycast.hpp"

#include <limits>

#include "polyroots.hpp"

using namespace std;

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

bool raycastBox(double left, double right, double bottom, double top, double front, double back,
                const Point3D& point, const Vector3& direction, RaycastHit& hit) {
    double t = numeric_limits<double>::infinity();

    // left plane
    {
        double tprime = (left - point.x()) / direction.x();
        Point3D intersection = point + tprime * direction;

        if (intersection.y() >= bottom && intersection.y() <= top && intersection.z() >= front && intersection.z() <= back) {
            t = min(t, tprime);
        }
    }

    // right plane
    {
        double tprime = (right - point.x()) / direction.x();
        Point3D intersection = point + tprime * direction;

        if (intersection.y() >= bottom && intersection.y() <= top && intersection.z() >= front && intersection.z() <= back) {
            t = min(t, tprime);
        }
    }

    // bottom plane
    {
        double tprime = (bottom - point.y()) / direction.y();
        Point3D intersection = point + tprime * direction;

        if (intersection.x() >= left && intersection.x() <= right && intersection.z() >= front && intersection.z() <= back) {
            t = min(t, tprime);
        }
    }

    // top plane
    {
        double tprime = (top - point.y()) / direction.y();
        Point3D intersection = point + tprime * direction;

        if (intersection.x() >= left && intersection.x() <= right && intersection.z() >= front && intersection.z() <= back) {
            t = min(t, tprime);
        }
    }

    // front plane
    {
        double tprime = (front - point.z()) / direction.z();
        Point3D intersection = point + tprime * direction;

        if (intersection.x() >= left && intersection.x() <= right && intersection.y() >= bottom && intersection.y() <= top) {
            t = min(t, tprime);
        }
    }

    // back plane
    {
        double tprime = (back - point.z()) / direction.z();
        Point3D intersection = point + tprime * direction;

        if (intersection.x() >= left && intersection.x() <= right && intersection.y() >= bottom && intersection.y() <= top) {
            t = min(t, tprime);
        }
    }

    if (t != numeric_limits<double>::infinity()) {
        // hit one of the planes
        hit.point = point + t * direction;
        return true;
    } else {
        // not hit occurred
        return false;
    }
}
