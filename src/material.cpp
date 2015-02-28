#include "material.hpp"

Material::~Material() { }

PhongMaterial::PhongMaterial(const Colour& diffuse, const Colour& specular, double shininess)
        : diffuse(diffuse), specular(specular), shininess(shininess) { }

PhongMaterial::~PhongMaterial() { }
