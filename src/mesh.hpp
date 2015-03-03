#ifndef CS488_MESH_HPP
#define CS488_MESH_HPP

#include <iosfwd>
#include <vector>

#include "algebra.hpp"
#include "primitive.hpp"

struct RaycastHit;

typedef std::vector<int> Face;

// A polygonal mesh.
class Mesh : public Primitive {
protected:
    std::vector<Point3D> verts;
    std::vector<Face> faces;

    mutable Primitive* bounds = NULL;

public:
    Mesh(const std::vector<Point3D>& verts, const std::vector<Face>& faces);
    virtual ~Mesh();

    bool raycast(const Point3D& point, const Vector3& direction, RaycastHit& hit) const;

    virtual const Primitive* getBounds() const;

    friend std::ostream& operator<<(std::ostream& out, const Mesh& mesh);
};

#endif
