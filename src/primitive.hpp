#ifndef CS488_PRIMITIVE_HPP
#define CS488_PRIMITIVE_HPP

#include "algebra.hpp"

class Primitive {
public:
    virtual ~Primitive();
};

class Sphere : public Primitive {
public:
    virtual ~Sphere();
};

class Cube : public Primitive {
public:
    virtual ~Cube();
};

class NonhierSphere : public Primitive {
    Point3D pos;
    double radius;

public:
    NonhierSphere(const Point3D& pos, double radius);
    virtual ~NonhierSphere();
};

class NonhierBox : public Primitive {
    Point3D pos;
    double size;

public:
    NonhierBox(const Point3D& pos, double size);
    virtual ~NonhierBox();
};

#endif
