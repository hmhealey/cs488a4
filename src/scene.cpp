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
    inverseTransform = transform.inverse();
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

    inverseTransform = transform.inverse();
}

void SceneNode::scale(const Vector3& amount) {
    transform = transform * Matrix4::makeScaling(amount[0], amount[1], amount[2]);
    inverseTransform = transform.inverse();
}

void SceneNode::translate(const Vector3& amount) {
    transform = transform * Matrix4::makeTranslation(amount[0], amount[1], amount[2]);
    inverseTransform = transform.inverse();
}

bool SceneNode::raycast(const Point3D& point, const Vector3& direction) const {
    RaycastHit hit;
    return raycast(point, direction, hit);
}

bool SceneNode::raycast(const Point3D& point, const Vector3& direction, RaycastHit& hit) const {
    bool hitChild = raycastChildren(inverseTransform * point, inverseTransform * direction, hit);

    // transform back to world coordinates before we return
    if (hitChild) hit.transform(transform, inverseTransform);

    return hitChild;
}

bool SceneNode::raycastChildren(const Point3D& point, const Vector3& direction, RaycastHit& hit) const {
    // this assumes that rays have already been transformed into our local modeling coordinates
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
    const Point3D& transformedPoint = inverseTransform * point;
    const Vector3& transformedDirection = inverseTransform * direction;

    bool intersected = primitive->raycast(transformedPoint, transformedDirection, hit);

    if (intersected) {
        // the primitive doesn't know about the material so we add it on
        hit.material = material;
    }

    RaycastHit childHit;
    bool childIntersected = raycastChildren(transformedPoint, transformedDirection, childHit);

    if (intersected || childIntersected) {
        if (intersected && childIntersected) {
            // the ray hit both us and our children so pick the nearest intersection of the two
            if ((childHit.point - point).length() < (hit.point - point).length()) {
                hit = childHit;
            }
        } else if (childIntersected) {
            // the ray hit our children, but not us
            hit = childHit;
        }

        hit.transform(transform, inverseTransform);

        return true;
    } else {
        // the ray missed us and our children
        return false;
    }
}
