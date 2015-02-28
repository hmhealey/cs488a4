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
        for (int x = 0; x < width; x++) {
            Colour background = getBackground(x, y, width, height);
            
            image(x, y, 0) = background.r();
            image(x, y, 1) = background.g();
            image(x, y, 2) = background.b();
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
