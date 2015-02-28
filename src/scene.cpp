/*****************************************
 * Harrison Healey - hmhealey - 20376857 *
 *****************************************/

#include "Scene.hpp"

#include <iostream>

#include "Algebra.hpp"
#include "Primitive.hpp"

using namespace std;

SceneNode::SceneNode(const std::string& name) : name(name) { }

SceneNode::~SceneNode() { }

string SceneNode::getName() const {
    return name;
}

bool SceneNode::isSelected() const {
    return selected;
}

void SceneNode::setSelected(bool selected) {
    this->selected = selected;
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

SceneNode::NodeType SceneNode::getType() const {
    return SceneNode::Node;
}

JointNode::JointNode(const std::string& name) : SceneNode(name) { }

JointNode::~JointNode() { }

Matrix4 JointNode::getTransform() const {
    return transform * Matrix4::makeYRotation(yRotation) * Matrix4::makeXRotation(xRotation);
}

SceneNode::NodeType JointNode::getType() const {
    return SceneNode::Joint;
}

double JointNode::getXRotation() const {
    return xRotation;
}

double JointNode::setXRotation(double xRotation) {
    return this->xRotation = min(max(xRotation, xRange.min), xRange.max);
}

double JointNode::getYRotation() const {
    return yRotation;
}

double JointNode::setYRotation(double yRotation) {
    return this->yRotation = min(max(yRotation, yRange.min), yRange.max);
}

void JointNode::setXRange(double min, double initial, double max) {
    xRange.min = min;
    xRange.initial = initial;
    xRange.max = max;
}

void JointNode::setYRange(double min, double initial, double max) {
    yRange.min = min;
    yRange.initial = initial;
    yRange.max = max;
}

GeometryNode::GeometryNode(const std::string& name, Primitive* primitive) : SceneNode(name), primitive(primitive) { }

GeometryNode::~GeometryNode() { }

SceneNode::NodeType GeometryNode::getType() const {
    return SceneNode::Geometry;
}

const Material* GeometryNode::getMaterial() const {
    return material;
}

Material* GeometryNode::getMaterial() {
    return material;
}

void GeometryNode::setMaterial(Material* material) {
    this->material = material;
}
 
