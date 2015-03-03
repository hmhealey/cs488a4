#include "mesh.hpp"

#include <iostream>
#include <limits>

#include "raycast.hpp"

using namespace std;

bool useBoundingSpheres = false;
bool drawBounds = false;

Mesh::Mesh(const vector<Point3D>& verts, const vector<Face>& faces) : verts(verts), faces(faces) { }

Mesh::~Mesh() {
    if (bounds != NULL) {
        delete bounds;
    }
}

bool Mesh::raycast(const Point3D& point, const Vector3& direction, RaycastHit& hit) const {
    // call getBounds to ensure that bounds is constructed
    const Primitive* bounds = getBounds();

    /*cerr << "Mesh: " << *this << endl;
    cerr << "Bounds: center=" << ((NonhierSphere*) bounds)->center << " radius=" << ((NonhierSphere*) bounds)->radius << endl;*/

    RaycastHit boundsHit; // ha, this says bound shit
    if (bounds->raycast(point, direction, boundsHit)) {
        // the ray hit our bounding sphere
        if (!drawBounds) {
            // we still need to intersect against the actual mesh
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
        } else {
            // we only have to do intersection on the bounding sphere, which we've done already
            hit = boundsHit;

            return true;
        }
    } else {
        // the ray missed our bounding sphere
        return false;
    }
}

const Primitive* Mesh::getBounds() const {
    if (bounds == NULL) {
        // construct a bounding volume since one it doesn't exist yet
        if (!useBoundingSpheres) {
            bounds = NonhierBox::makeBoundingBox(verts);
        } else {
            bounds = NonhierSphere::makeBoundingSphere(verts);
        }
    }

    return bounds;
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
