#include <cstring>
#include <iostream>

#include "scene_lua.hpp"

using namespace std;

extern bool drawDepth;

extern bool useStochasticSampling;
extern int numSubpixels;

int main(int argc, char** argv) {
    string filename = "scene.lua";

    for (int i = 0; i < argc; i++) {
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

