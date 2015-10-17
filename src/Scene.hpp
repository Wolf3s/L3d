
// ===============================================================================================================
// -*- C++ -*-
//
// Scene.hpp - The editor scene/world object.
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

#ifndef SCENE_HPP
#define SCENE_HPP

#include <map>
#include <string>

#include "SceneObject.hpp"

namespace l3d
{
class Camera;

// The scene of the L3D editor.
// Supports saving and loading from file.
class Scene
{
    friend class Renderer;

  public:

    // Write this scene to a text file.
    // Can also save the camera position if provided.
    bool Save(const std::string & fileName, const Camera * camera);

    // Load a scene from a file. Also loads camera position if parameter not null.
    // Warning: Current scene is discarded.
    bool Load(const std::string & fileName, Camera * camera);

    // Creates an empty object at the center (0,0,0) of the scene,
    // with a default mesh associated to it.
    SceneObject * NewObject(const std::string & objectName = NextName());

    // Creates a new scene object with a mesh, loaded from a file.
    // If the 'objectName' parameter is an empty string, the file name
    // of the 3D mesh will be used as the object name (without the file extension of course).
    SceneObject * NewObjectFromMeshFile(const std::string & fileName,
                                        const Transform & xform = Transform(),
                                        const std::string & objectName = "");

    // Remove the given object from the scene
    void RemoveObject(const SceneObject * object);

    // Generates the next sequential object name.
    static std::string NextName();

    ~Scene() { Clear(); }

  private:

    // Delete all scene objects.
    void Clear();

    // All scene objects are indexed by their name.
    typedef std::map<std::string, SceneObject *> SceneObjectMap;
    SceneObjectMap objects;

    // This counter is used to generate sequential names for new objects
    static unsigned int objectCount;
};

} // namespace l3d {}

#endif // SCENE_HPP
