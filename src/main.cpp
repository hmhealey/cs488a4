#include <cstring>
#include <iostream>

#include "scene_lua.hpp"

using namespace std;

extern bool drawDepth;

extern bool useStochasticSampling;
extern double stochasticSamplingRange;

int main(int argc, char** argv) {
    string filename = "scene.lua";

    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-d") == 0) {
            drawDepth = true;
        } else if (strcmp(argv[i], "-s") == 0) {
            useStochasticSampling = true;
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

