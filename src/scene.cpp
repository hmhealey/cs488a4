/*****************************************
 * Harrison Healey - hmhealey - 20376857 *
 *****************************************/

#include "scene.hpp"

#include <iostream>
#include <limits>

#include "algebra.hpp"
#include "primitive.hpp"

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

bool SceneNode::raycast(const Point3D& point, const Vector3& direction, Point3D& intersection) const {
    return raycastChildren(point, direction, intersection);
}

bool SceneNode::raycastChildren(const Point3D& point, const Vector3& direction, Point3D& intersection) const {
    for (auto i = children.cbegin(); i != children.cend(); i++) {
        if ((*i)->raycast(point, direction, intersection)) {
            return true;
        }
    }

    return false;
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

bool GeometryNode::raycast(const Point3D& point, const Vector3& direction, Point3D& intersection) const {
    double t = primitive->getIntersection(point, direction);

    if (t >= 0 && t != numeric_limits<double>::infinity()) {
        intersection = point + t * direction;
        return true;
    } else {
        return raycastChildren(point, direction, intersection);
    }
}
