#ifndef CS488_PRIMITIVE_HPP
#define CS488_PRIMITIVE_HPP

#include "algebra.hpp"

struct RaycastHit;

class Primitive {
public:
    virtual ~Primitive();

    virtual double getIntersection(const Point3D& point, const Vector3& direction) const = 0;
    virtual bool raycast(const Point3D& point, const Vector3& direction, RaycastHit& hit) const;
};

class Sphere : public Primitive {
public:
    virtual ~Sphere();

    virtual double getIntersection(const Point3D& point, const Vector3& direction) const;
    virtual bool raycast(const Point3D& point, const Vector3& direction, RaycastHit& hit) const;
};

class Cube : public Primitive {
public:
    virtual ~Cube();

    virtual double getIntersection(const Point3D& point, const Vector3& direction) const;
    virtual bool raycast(const Point3D& point, const Vector3& direction, RaycastHit& hit) const;
};

class NonhierSphere : public Primitive {
    Point3D center;
    double radius;

public:
    NonhierSphere(const Point3D& center, double radius);
    virtual ~NonhierSphere();

    virtual double getIntersection(const Point3D& point, const Vector3& direction) const;
    virtual bool raycast(const Point3D& point, const Vector3& direction, RaycastHit& hit) const;
};

class NonhierBox : public Primitive {
    Point3D pos;
    double size;    

public:
    NonhierBox(const Point3D& pos, double size);
    virtual ~NonhierBox();

    virtual double getIntersection(const Point3D& point, const Vector3& direction) const;
    virtual bool raycast(const Point3D& point, const Vector3& direction, RaycastHit& hit) const;
};

#endif
