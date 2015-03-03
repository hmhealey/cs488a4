#include <cstring>
#include <iostream>

#include "scene_lua.hpp"

using namespace std;

extern bool drawDepth;

extern bool useStochasticSampling;
extern int numSubpixels;

extern int widthOverride;
extern int heightOverride;

extern bool useBoundingSpheres;
extern bool drawBounds;

int main(int argc, char** argv) {
    string filename = "scene.lua";

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-d") == 0) {
            drawDepth = true;
        } else if (strcmp(argv[i], "-ss") == 0) {
            if (i < argc - 1) {
                numSubpixels = atoi(argv[i + 1]);
                i += 1;
            } else {
                cerr << "Expected sample resolution after -ss" << endl;
                return 1;
            }
        } else if (strcmp(argv[i], "-st") == 0) {
            useStochasticSampling = true;

            if (i < argc - 1) {
                numSubpixels = atoi(argv[i + 1]);
                i += 1;
            } else {
                cerr << "Expected sample resolution after -st" << endl;
                return 1;
            }
        } else if (strcmp(argv[i], "-w") == 0) {
            if (i < argc - 1) {
                widthOverride = atoi(argv[i + 1]);
                i += 1;
            } else {
                cerr << "Expected width after -w" << endl;
            }
        } else if (strcmp(argv[i], "-h") == 0) {
            if (i < argc - 1) {
                heightOverride = atoi(argv[i + 1]);
                i += 1;
            } else {
                cerr << "Expected height after -h" << endl;
            }
        } else if (strcmp(argv[i], "-b") == 0 || strcmp(argv[i], "-db") == 0) {
            if (strcmp(argv[i], "-db") == 0) {
                drawBounds = true;
            }

            if (i < argc - 1) {
                if (strcmp(argv[i + 1], "sphere") == 0) {
                    useBoundingSpheres = true;
                    i += 1;
                } else if (strcmp(argv[i + 1], "box") == 0) {
                    // this is the default currently, but in case it's ever not, still set this
                    useBoundingSpheres = false;
                    i += 1;
                }
            }
        } else {
            filename = argv[i];
        }
    }

    if (!run_lua(filename)) {
        cerr << "Could not open " << filename << endl;
        return 1;
    }

    return 0;
}

