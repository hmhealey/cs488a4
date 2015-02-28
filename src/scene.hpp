/*****************************************
 * Harrison Healey - hmhealey - 20376857 *
 *****************************************/

#ifndef SCENE_HPP
#define SCENE_HPP

#include <list>

#include "Algebra.hpp"
#include "Material.hpp"

class JointNode;
class Primitive;
class Shader;

class SceneNode {
public:
    enum NodeType {
        Node,
        Joint,
        Geometry
    };
protected:
    std::string name;

    std::list<SceneNode*> children;

    bool selected = false;

    Matrix4 transform;

public:
    SceneNode(const std::string& name);
    virtual ~SceneNode();

    std::string getName() const;

    bool isSelected() const;
    void setSelected(bool selected);

    virtual Matrix4 getTransform() const;
    void setTransform(const Matrix4& transform);

    void add_child(SceneNode* child);
    void remove_child(SceneNode* child);

    SceneNode* getByName(const std::string& name);

    void rotate(char axis, double angle);
    void scale(const Vector3& amount);
    void translate(const Vector3& amount);

    virtual NodeType getType() const;
};

class JointNode : public SceneNode {
protected:
    struct JointRange {
        double min;
        double initial;
        double max;
    };

    JointRange xRange;
    JointRange yRange;

    double xRotation = 0;
    double yRotation = 0;

public:
    JointNode(const std::string& name);
    virtual ~JointNode();

    virtual Matrix4 getTransform() const;

    virtual SceneNode::NodeType getType() const;

    double getXRotation() const;
    double setXRotation(double xRotation);

    double getYRotation() const;
    double setYRotation(double yRotation);

    void setXRange(double min, double initial, double max);
    void setYRange(double min, double initial, double max);
};

class GeometryNode : public SceneNode {
    Primitive* primitive;
    Material* material;

public:
    GeometryNode(const std::string& name, Primitive* primitive);
    virtual ~GeometryNode();

    virtual SceneNode::NodeType getType() const;

    const Material* getMaterial() const;
    Material* getMaterial();
    void setMaterial(Material* material);
};

#endif
