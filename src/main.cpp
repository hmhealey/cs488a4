#include <iostream>

#include "scene_lua.hpp"

using namespace std;

int main(int argc, char** argv) {
    string filename = "scene.lua";
    if (argc >= 2) {
        filename = argv[1];
    }

    if (!run_lua(filename)) {
        cerr << "Could not open " << filename << endl;
        return 1;
    }

    return 0;
}

