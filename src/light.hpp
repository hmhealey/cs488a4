#ifndef CS488_LIGHT_HPP
#define CS488_LIGHT_HPP

#include <iosfwd>

#include "algebra.hpp"

struct Light {
    Light();
  
    Colour colour;
    Point3D position;
    double falloff[3];
};

std::ostream& operator<<(std::ostream& out, const Light& l);

#endif
