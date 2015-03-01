/*****************************************
 * Harrison Healey - hmhealey - 20376857 *
 *****************************************/

#include "scene.hpp"

#include <iostream>

#include "primitive.hpp"
#include "raycast.hpp"

using namespace std;

SceneNode::SceneNode(const std::string& name) : name(name) { }

SceneNode::~SceneNode() { }

string SceneNode::getName() const {
    return name;
}

Matrix4 SceneNode::getTransform() const {
    return transform;
}

void SceneNode::setTransform(const Matrix4& transform) {
    this->transform = transform;
}

void SceneNode::add_child(SceneNode* child) {
    children.push_back(child);
}

void SceneNode::remove_child(SceneNode* child) {
    children.remove(child);
}

SceneNode* SceneNode::getByName(const string& name) {
    if (name == this->name) {
        return this;
    } else {
        for (auto i = children.cbegin(); i != children.cend(); i++) {
            SceneNode* node = (*i)->getByName(name);

            if (node != NULL) {
                return node;
            }
        }

        return NULL;
    }
}

void SceneNode::rotate(char axis, double angle) {
    switch(axis) {
    case 'x':
        transform = transform * Matrix4::makeXRotation(angle);
        break;
    case 'y':
        transform = transform * Matrix4::makeYRotation(angle);
        break;
    case 'z':
        transform = transform * Matrix4::makeZRotation(angle);
        break;
    default:
        cerr << "SceneNode::rotate - " << axis << " isn't a valid axis" << endl;
        break;
    }
}

void SceneNode::scale(const Vector3& amount) {
    transform = transform * Matrix4::makeScaling(amount[0], amount[1], amount[2]);
}

void SceneNode::translate(const Vector3& amount) {
    transform = transform * Matrix4::makeTranslation(amount[0], amount[1], amount[2]);
}

bool SceneNode::raycast(const Point3D& point, const Vector3& direction, RaycastHit& hit) const {
    return raycastChildren(point, direction, hit);
}

bool SceneNode::raycastChildren(const Point3D& point, const Vector3& direction, RaycastHit& hit) const {
    // convert the ray into our local coordinate system
    bool intersected = false;

    for (auto i = children.cbegin(); i != children.cend(); i++) {
        RaycastHit childHit;
        if ((*i)->raycast(point, direction, childHit)) {
            if (!intersected || (childHit.point - point).length() < (hit.point - point).length()) {
                hit = childHit;
                intersected = true;
            }
        }
    }

    return intersected;
}

// --------------- GeometryNode ---------------

GeometryNode::GeometryNode(const std::string& name, Primitive* primitive) : SceneNode(name), primitive(primitive) { }

GeometryNode::~GeometryNode() { }

const Material* GeometryNode::getMaterial() const {
    return material;
}

Material* GeometryNode::getMaterial() {
    return material;
}

void GeometryNode::setMaterial(Material* material) {
    this->material = material;
}

bool GeometryNode::raycast(const Point3D& point, const Vector3& direction, RaycastHit& hit) const {
    bool intersected = primitive->raycast(point, direction, hit);

    RaycastHit childHit;
    bool childIntersected = raycastChildren(point, direction, childHit);

    if (intersected && childIntersected) {
        // the ray hit both us and our children so pick the nearest intersection of the two
        if ((childHit.point - point).length() < (hit.point - point).length()) {
            hit = childHit;
        }

        return true;
    } else if (intersected) {
        // the ray hit us, but not our children
        return true;
    } else if (childIntersected) {
        // the ray didn't hit us, but hit our child
        hit = childHit;
        return true;
    } else {
        // the ray missed us and our children
        return false;
    }
}
