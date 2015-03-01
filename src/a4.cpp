#include "a4.hpp"

#include <algorithm>
#include <iostream>

#include "algebra.hpp"
#include "image.hpp"
#include "primitive.hpp"

using namespace std;

void render(SceneNode* root, const string& filename, int width, int height, 
            const Point3D& eye, const Vector3& view, const Vector3& up, double fov, 
            const Colour& ambient, const list<Light*>& lights) {
    Image image(width, height, 3);

    // depth of near plane
    double d = 0.1;

    // size of the near plane
    double h = 2 * d * tan(fov);
    double w = h * (width / height);

    // change 0..1 coordinate space to -width/2..width/2
    Matrix4 t1 = Matrix4::makeTranslation(-width / 2.0, -height / 2.0, d);

    // stretch screen to fit plane while maintaining aspect ratio
    Matrix4 s2 = Matrix4::makeScaling(-h / height, w / width, 1);

    Vector3 wv = view.normalized();
    Vector3 uv = (up.cross(wv)).normalized();
    Vector3 vv = wv.cross(uv);

    // rotate view coordinates onto world
    Matrix4 r3(uv.x(), vv.x(), wv.x(), 0,
               uv.y(), vv.y(), wv.y(), 0,
               uv.z(), vv.z(), wv.z(), 0,
               0, 0, 0, 1);

    // move to eye point
    Matrix4 t4 = Matrix4::makeTranslation(eye.x(), eye.y(), eye.z());

    Matrix4 m = t4 * r3 * s2 * t1;

    double dist[height][width];
    double maxDist = -1;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Point3D pk(x, y, 0);
            Point3D pw = m * pk;

            Point3D intersection;

            Colour colour;
            if (root->raycast(pw, (pw - eye).normalized(), intersection)) {
                dist[y][x] = (intersection - eye).length();
                maxDist = max(maxDist, dist[y][x]);
            } else {
                dist[y][x] = -1;
            }
        }
    }

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Colour colour;
            if (dist[y][x] != -1) {
                colour = Colour(dist[y][x] / maxDist);
            } else {
                colour = getBackground(x, y, width, height);
            }
            
            image(x, y, 0) = colour.r();
            image(x, y, 1) = colour.g();
            image(x, y, 2) = colour.b();
        }
    }

    image.savePng(filename);
}

Colour getBackground(int x, int y, int width, int height) {
    // red increasing from top to bottom
    double red = (double) y / height;

    // green increasing from left to right
    double green = (double) x / width;

    // blue in the lower left and upper right corners
    double blue = ((y < height / 2 && x < width / 2) || (y >= height / 2 && x >= width / 2)) ? 1.0 : 0.0;

    return Colour(red, green, blue);
}
