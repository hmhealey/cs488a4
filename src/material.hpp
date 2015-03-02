#ifndef CS488_MATERIAL_HPP
#define CS488_MATERIAL_HPP

#include "algebra.hpp"

struct Material {
protected:
    Material() { }

public:
    virtual ~Material();
};

struct PhongMaterial : public Material {
    Colour ambient;
    Colour diffuse;
    Colour specular;

    double shininess;

    PhongMaterial(const Colour& kd, const Colour& ks, double shininess);
    virtual ~PhongMaterial();
};


#endif
