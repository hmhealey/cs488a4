#include "a4.hpp"

#include <iostream>

#include "image.hpp"

using namespace std;

void render(SceneNode* root, const string& filename, int width, int height, 
            const Point3D& eye, const Vector3& view, const Vector3& up, double fov, 
            const Colour& ambient, const list<Light*>& lights) {
    cerr << "Stub: a4_render(" << root << ",\n     "
         << filename << ", " << width << ", " << height << ",\n     "
         << eye << ", " << view << ", " << up << ", " << fov << ",\n     "
         << ambient << ",\n     {";

    for (auto i = lights.cbegin(); i != lights.cend(); ++i) {
        if (i != lights.cbegin()) cerr << ", ";
        cerr << **i;
    }
    cerr << "});" << endl;
  
    // For now, just make a sample image.

    Image image(width, height, 3);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < height; x++) {
            // Red: increasing from top to bottom
            image(x, y, 0) = (double) y / height;
            // Green: increasing from left to right
            image(x, y, 1) = (double) x / width;
            // Blue: in lower-left and upper-right corners
            image(x, y, 2) = ((y < height / 2 && x < height / 2) || (y >= height / 2 && x >= height / 2)) ? 1.0 : 0.0;
        }
    }

    image.savePng(filename);
}
