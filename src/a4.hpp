#ifndef CS488_A4_HPP
#define CS488_A4_HPP

#include <string>

#include "algebra.hpp"
#include "light.hpp"
#include "scene.hpp"

void render(SceneNode* root, const std::string& filename, int width, int height,
            const Point3D& eye, Vector3 view, Vector3 up, double fov,
            const Colour& ambient, const std::list<Light*>& lights);

Colour getBackground(double x, double y, int width, int height);

#endif
