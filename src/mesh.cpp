#include "mesh.hpp"

#include <iostream>
#include <limits>

using namespace std;

Mesh::Mesh(const vector<Point3D>& verts, const vector<Face>& faces) : verts(verts), faces(faces) { }

double Mesh::getIntersection(const Point3D& point, const Vector3& direction) const {
    double t = numeric_limits<double>::infinity();

    for (auto i = faces.cbegin(); i != faces.cend(); i++) {
        // points that make up the face
        Point3D p0 = verts[(*i)[0]];
        Point3D p1 = verts[(*i)[1]];
        Point3D p2 = verts[(*i)[2]];

        // [r1] = [x1 x2 x3] beta
        // [r2] = [y1 y2 y3] gamma
        // [r3] = [z1 z2 z3] t

        double r1 = point.x() - p0.x();
        double r2 = point.y() - p0.y();
        double r3 = point.z() - p0.z();

        double x1 = p1.x() - p0.x();
        double x2 = p2.x() - p0.x();
        double x3 = -direction.x();

        double y1 = p1.y() - p0.y();
        double y2 = p2.y() - p0.y();
        double y3 = -direction.y();

        double z1 = p1.z() - p0.z();
        double z2 = p2.z() - p0.z();
        double z3 = -direction.z();

        // solve the system of equations using cramer's rule
        double d = Matrix3(x1, x2, x3,
                           y1, y2, y3,
                           z1, z2, z3).determinant();
        double d1 = Matrix3(r1, x2, x3,
                            r2, y2, y3,
                            r3, z2, z3).determinant();
        double d2 = Matrix3(x1, r1, x3,
                            y1, r2, y3,
                            z1, r3, z3).determinant();
        double d3 = Matrix3(x1, x2, r1,
                            y1, y2, r2,
                            z1, z2, r3).determinant();

        double beta = d1 / d;
        double gamma = d2 / d;
        double tprime = d3 / d; // called tprime here to avoid conflicting with our nearest t that we have saved

        if (beta >= 0 && gamma >= 0 && beta + gamma <= 1 && tprime < t) {
            // store the smallest t that we have so far so we can return that
            t = tprime;
        }
    }

    return t;

    /*for (auto i = faces.cbegin(); i != faces.cend(); i++) {
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
    }*/

    //return numeric_limits<double>::infinity();
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
