#include "mesh.hpp"

#include <iostream>
#include <limits>

using namespace std;

Mesh::Mesh(const vector<Point3D>& verts, const vector<Face>& faces) : verts(verts), faces(faces) { }

double Mesh::getIntersection(const Point3D& point, const Vector3& direction) const {
    for (auto i = faces.cbegin(); i != faces.cend(); i++) {
        const Face& face = *i;
        Vector3 normal = (verts[face[1]] - verts[face[0]]).cross(verts[face[2]] - verts[face[0]]);

        double numerator = -normal.dot(point - verts[face[0]]);
        double denominator = normal.dot(direction);

        if (denominator != 0) {
            // line intersects with the plane
            return numerator / denominator;
        } else {
            if (numerator == 0) {
                // line is coincident with the plane
                cerr << "Mesh::getIntersection - line (point=" << point << " direction=" << direction << ") is coincident with the plane" << endl;
            }
        }
    }

    return numeric_limits<double>::infinity();
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
