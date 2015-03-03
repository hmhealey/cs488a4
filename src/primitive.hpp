#ifndef CS488_PRIMITIVE_HPP
#define CS488_PRIMITIVE_HPP

#include "algebra.hpp"

#include <vector>

struct RaycastHit;

struct Primitive {
    virtual ~Primitive();

    virtual bool raycast(const Point3D& point, const Vector3& direction, RaycastHit& hit) const = 0;

    const virtual Primitive* getBounds() const;
};

struct Sphere : public Primitive {
    virtual ~Sphere();

    virtual bool raycast(const Point3D& point, const Vector3& direction, RaycastHit& hit) const;
};

struct Cube : public Primitive {
    virtual ~Cube();

    virtual bool raycast(const Point3D& point, const Vector3& direction, RaycastHit& hit) const;
};

struct NonhierSphere : public Primitive {
    const Point3D center;
    const double radius;

    NonhierSphere(const Point3D& center, double radius);
    virtual ~NonhierSphere();

    virtual bool raycast(const Point3D& point, const Vector3& direction, RaycastHit& hit) const;

    static NonhierSphere *makeBoundingSphere(const std::vector<Point3D>& points);
};

struct NonhierBox : public Primitive {
    const double left;
    const double right;
    const double bottom;
    const double top;
    const double front;
    const double back;

    NonhierBox(const Point3D& pos, double size);
    NonhierBox(double left, double right, double bottom, double top, double front, double back);
    virtual ~NonhierBox();

    virtual bool raycast(const Point3D& point, const Vector3& direction, RaycastHit& hit) const;

    static NonhierBox *makeBoundingBox(const std::vector<Point3D>& points);
};

#endif
