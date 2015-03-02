#include <cstring>
#include <iostream>

#include "scene_lua.hpp"

using namespace std;

extern bool drawDepth;

extern bool useStochasticSampling;
extern int numSubpixels;

extern int widthOverride;
extern int heightOverride;

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

