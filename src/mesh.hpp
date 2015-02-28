#ifndef CS488_MESH_HPP
#define CS488_MESH_HPP

#include <iosfwd>
#include <vector>

#include "algebra.hpp"
#include "primitive.hpp"

typedef std::vector<int> Face;

// A polygonal mesh.
class Mesh : public Primitive {
    std::vector<Point3D> verts;
    std::vector<Face> faces;

public:
    Mesh(const std::vector<Point3D>& verts, const std::vector<Face>& faces);

    friend std::ostream& operator<<(std::ostream& out, const Mesh& mesh);
};

#endif
