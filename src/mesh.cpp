#include "mesh.hpp"

#include <iostream>
#include <limits>

#include "raycast.hpp"

using namespace std;

Mesh::Mesh(const vector<Point3D>& verts, const vector<Face>& faces) : verts(verts), faces(faces) { }

bool Mesh::raycast(const Point3D& point, const Vector3& direction, RaycastHit& hit) const {
    bool intersected = false;

    for (auto i = faces.cbegin(); i != faces.cend(); i++) {
        // faces are assumed to be planar, convex, and can have any number of vertices
        const Face& face = *i;

        RaycastHit faceHit;
        if (raycastPolygon(face, verts, point, direction, faceHit)) {
            if (!intersected || (faceHit.point - point).length() < (hit.point - point).length()) {
                hit = faceHit;
                intersected = true;
            }
        }
    }

    return intersected;
}

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
