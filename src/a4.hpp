#ifndef CS488_A4_HPP
#define CS488_A4_HPP

#include <string>

#include "algebra.hpp"
#include "light.hpp"
#include "scene.hpp"

void a4_render(SceneNode* root, const std::string& filename, int width, int height,
               const Point3D& eye, const Vector3& view, const Vector3& up, double fov,
               const Colour& ambient, const std::list<Light*>& lights);

#endif
