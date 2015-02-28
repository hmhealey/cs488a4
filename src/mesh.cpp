#include "mesh.hpp"

#include <iostream>

using namespace std;

Mesh::Mesh(const vector<Point3D>& verts, const vector<Face>& faces) : verts(verts), faces(faces) { }

ostream& operator<<(ostream& out, const Mesh& mesh) {
    cerr << "mesh({";
    for (auto i = mesh.verts.cbegin(); i != mesh.verts.cend(); ++i) {
        if (i != mesh.verts.cbegin()) cerr << ",\n      ";
        cerr << *i;
    }
    cerr << "},\n\n     {";
  
    for (auto i = mesh.faces.cbegin(); i != mesh.faces.cend(); ++i) {
        if (i != mesh.faces.cbegin()) cerr << ",\n      ";
        cerr << "[";
        for (auto j = i->cbegin(); j != i->cend(); ++j) {
            if (j != i->cbegin()) cerr << ", ";
            cerr << *j;
        }
        cerr << "]";
    }
    cerr << "});" << endl;
    return out;
}
