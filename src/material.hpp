#ifndef CS488_MATERIAL_HPP
#define CS488_MATERIAL_HPP

#include "algebra.hpp"

class Material {
public:
    virtual ~Material();

protected:
    Material() { }
};

class PhongMaterial : public Material {
public:
    PhongMaterial(const Colour& kd, const Colour& ks, double shininess);
    virtual ~PhongMaterial();

private:
    Colour diffuse;
    Colour specular;

    double shininess;
};


#endif
