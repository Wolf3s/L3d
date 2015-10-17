
// ===============================================================================================================
// -*- C++ -*-
//
// SceneObject.hpp - Represents an object in the scene/world. Might be a light, mesh, etc.
//
// Copyright (c) 2012 Guilherme R. Lampert
// guilherme.ronaldo.lampert@gmail.com
//
// This code is licenced under the MIT license.
//
// This software is provided "as is" without express or implied
// warranties. You may freely copy and compile this source into
// applications you distribute provided that the copyright text
// above is included in the resulting source code.
//
// ===============================================================================================================

#ifndef SCENE_OBJECT_HPP
#define SCENE_OBJECT_HPP

#include <vector>
#include <QVector2D>
#include <QVector3D>
#include <QQuaternion>

#include "TexMat.hpp"
#include "Mesh.hpp"

namespace l3d
{

// Rotation, translation, scale
struct Transform
{
    Transform() // Construct with no scale and no rotation at origin (0,0,0)
    : scale(1, 1, 1),
      rotation(0, 0, 0),
      translation(0, 0, 0)
    {
    }

    Transform(const Transform & rhs)
        : scale(rhs.scale)
        , rotation(rhs.rotation)
        , translation(rhs.translation)
    {
    }

    Transform(const QVector3D & s, const QVector3D & r, const QVector3D & t)
        : scale(s)
        , rotation(r)
        , translation(t)
    {
    }

    Transform & operator=(const Transform & rhs)
    {
        this->scale = rhs.scale;
        this->rotation = rhs.rotation;
        this->translation = rhs.translation;
        return *this;
    }

    QVector3D scale;
    QVector3D rotation;
    QVector3D translation;
};

// The scene object representation
class SceneObject
{
    friend class Scene;

  public:

    // Prototype method to duplicate this object.
    SceneObject * Clone() const;

    bool SetTexture(const std::string & fileName);
    std::string GetTexture(int index = 0) const;

    bool SetMesh(const std::string & fileName);
    std::string GetMesh() const;

    std::string objectName;
    MeshPtr mesh;
    Transform xform;
    std::vector<Material> materials;

  private:

    SceneObject(const std::string & name);
    SceneObject(const SceneObject & rhs);
    SceneObject(const std::string & name, const MeshPtr & m, const Transform & xf);
    ~SceneObject() { }
};

} // namespace l3d {}

#endif // SCENE_OBJECT_HPP
