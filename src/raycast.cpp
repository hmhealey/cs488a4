#include "raycast.hpp"

#include <limits>

#include "polyroots.hpp"

using namespace std;

void RaycastHit::transform(const Matrix4& transform) {
    point = transform * point;
    normal = transform * normal;
}

bool raycastSphere(const Point3D& center, double radius, const Point3D& point, const Vector3& direction, RaycastHit& hit) {
    Vector3 v = point - center;

    double roots[2];
    size_t numRoots = quadraticRoots(direction.dot(direction), 2 * direction.dot(v), v.dot(v) - radius * radius, roots);

    if (numRoots > 0) {
        double t;
        if (numRoots == 1) {
            t = roots[0];
        } else {
            if (roots[0] >= 0 && roots[0] < roots[1]) {
                t = roots[0];
            } else {
                t = roots[1];
            }
        }

        if (t >= 0) {
            hit.point = point + t * direction;
            hit.normal = (hit.point - center).normalized();

            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

bool raycastBox(double left, double right, double bottom, double top, double front, double back,
                const Point3D& point, const Vector3& direction, RaycastHit& hit) {
    double t = numeric_limits<double>::infinity();
    Vector3 normal;

    // left plane
    {
        double tprime = (left - point.x()) / direction.x();
        Point3D intersection = point + tprime * direction;

        if (intersection.y() >= bottom && intersection.y() <= top && intersection.z() >= front && intersection.z() <= back) {
            if (tprime >= 0 && tprime < t) {
                t = tprime;
                normal = Vector3(-1, 0, 0);
            }
        }
    }

    // right plane
    {
        double tprime = (right - point.x()) / direction.x();
        Point3D intersection = point + tprime * direction;

        if (intersection.y() >= bottom && intersection.y() <= top && intersection.z() >= front && intersection.z() <= back) {
            if (tprime >= 0 && tprime < t) {
                t = tprime;
                normal = Vector3(1, 0, 0);
            }
        }
    }

    // bottom plane
    {
        double tprime = (bottom - point.y()) / direction.y();
        Point3D intersection = point + tprime * direction;

        if (intersection.x() >= left && intersection.x() <= right && intersection.z() >= front && intersection.z() <= back) {
            if (tprime >= 0 && tprime < t) {
                t = tprime;
                normal = Vector3(0, -1, 0);
            }
        }
    }

    // top plane
    {
        double tprime = (top - point.y()) / direction.y();
        Point3D intersection = point + tprime * direction;

        if (intersection.x() >= left && intersection.x() <= right && intersection.z() >= front && intersection.z() <= back) {
            if (tprime >= 0 && tprime < t) {
                t = tprime;
                normal = Vector3(0, 1, 0);
            }
        }
    }

    // front plane
    {
        double tprime = (front - point.z()) / direction.z();
        Point3D intersection = point + tprime * direction;

        if (intersection.x() >= left && intersection.x() <= right && intersection.y() >= bottom && intersection.y() <= top) {
            if (tprime >= 0 && tprime < t) {
                t = tprime;
                normal = Vector3(0, 0, -1);
            }
        }
    }

    // back plane
    {
        double tprime = (back - point.z()) / direction.z();
        Point3D intersection = point + tprime * direction;

        if (intersection.x() >= left && intersection.x() <= right && intersection.y() >= bottom && intersection.y() <= top) {
            if (tprime >= 0 && tprime < t) {
                t = tprime;
                normal = Vector3(0, 0, 1);
            }
        }
    }

    if (t >= 0 && t != numeric_limits<double>::infinity()) {
        // hit one of the planes
        hit.point = point + t * direction;
        hit.normal = normal;

        return true;
    } else {
        // not hit occurred
        return false;
    }
}

bool raycastTriangle(const Point3D& p0, const Point3D& p1, const Point3D& p2, const Point3D& point, const Vector3& direction, RaycastHit& hit) {
    double r1 = point.x() - p0.x();
    double r2 = point.y() - p0.y();
    double r3 = point.z() - p0.z();

    double x1 = p1.x() - p0.x();
    double x2 = p2.x() - p0.x();
    double x3 = -direction.x();

    double y1 = p1.y() - p0.y();
    double y2 = p2.y() - p0.y();
    double y3 = -direction.y();

    double z1 = p1.z() - p0.z();
    double z2 = p2.z() - p0.z();
    double z3 = -direction.z();

    // solve the system of equations using cramer's rule
    double d = Matrix3(x1, x2, x3,
                       y1, y2, y3,
                       z1, z2, z3).determinant();
    double d1 = Matrix3(r1, x2, x3,
                        r2, y2, y3,
                        r3, z2, z3).determinant();
    double d2 = Matrix3(x1, r1, x3,
                        y1, r2, y3,
                        z1, r3, z3).determinant();
    double d3 = Matrix3(x1, x2, r1,
                        y1, y2, r2,
                        z1, z2, r3).determinant();

    double beta = d1 / d;
    double gamma = d2 / d;

    if (beta >= 0 && gamma >= 0 && beta + gamma <= 1) {
        double t = d3 / d;

        if (t >= 0) {
            hit.point = point + t * direction;
            hit.normal = (p1 - p0).cross(p2 - p0).normalized();

            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}
