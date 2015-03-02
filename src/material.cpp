#include "material.hpp"

Material::~Material() { }

PhongMaterial::PhongMaterial(const Colour& diffuse, const Colour& specular, double shininess)
        : ambient(1, 1, 1), diffuse(diffuse), specular(specular), shininess(shininess) { }

PhongMaterial::~PhongMaterial() { }
