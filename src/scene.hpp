/*****************************************
 * Harrison Healey - hmhealey - 20376857 *
 *****************************************/

#ifndef SCENE_HPP
#define SCENE_HPP

#include <list>

#include "algebra.hpp"
#include "material.hpp"

class JointNode;
class Primitive;
class Shader;

class SceneNode {
protected:
    std::string name;

    std::list<SceneNode*> children;

    Matrix4 transform;

public:
    SceneNode(const std::string& name);
    virtual ~SceneNode();

    std::string getName() const;

    virtual Matrix4 getTransform() const;
    void setTransform(const Matrix4& transform);

    void add_child(SceneNode* child);
    void remove_child(SceneNode* child);

    SceneNode* getByName(const std::string& name);

    void rotate(char axis, double angle);
    void scale(const Vector3& amount);
    void translate(const Vector3& amount);
};

class GeometryNode : public SceneNode {
    Primitive* primitive;
    Material* material;

public:
    GeometryNode(const std::string& name, Primitive* primitive);
    virtual ~GeometryNode();

    const Material* getMaterial() const;
    Material* getMaterial();
    void setMaterial(Material* material);
};

#endif
