
// ===============================================================================================================
// -*- C++ -*-
//
// Renderer.hpp - Wrapper to an OpenGL renderer.
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

#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "Scene.hpp"
#include "SceneObject.hpp"
#include "TexMat.hpp"

#include <vector>

namespace l3d
{

// Rendering mode flags
enum RenderMode
{
    RM_WIREFRAME,     // Wirefame rendering
    RM_TEXTURE_SHADED // Fully textured/colored and shaded
};

// Wrapper around a 3D graphics API.
// In this case OpenGL.
class Renderer
{
  public:

    Renderer();

    QMatrix4x4 projectionMatrix, viewMatrix;

    // Light parameters
    QVector4D lightPosition, ambientLight, diffuseLight, specularLight;
    float shininess;

    void SetRenderMode(RenderMode renderMode);
    RenderMode GetRenderMode() const { return renderMode; }

    void RenderScene(const Scene * scene);
    void RenderSceneObject(const SceneObject * object);
    void RenderMesh(const Mesh * mesh);
    void ApplyMaterial(const Material * mat);
    const SceneObject * Pick(int x, int y);

    // Rendering method used by the selection/picking rendering pass,
    // as well as for object outline drawing.
    void ColorOnlyRendering(const SceneObject * object, QRgb c);

  private:

    void SetupShaders();
    void SetTexture(GLuint texId, TextureFilter texFilter);

    TexturePtr defaultTexture; // Texture applied on untextured meshes.
    QGLShaderProgram defaultShader;
    QGLShaderProgram colorOnlyShader;
    RenderMode renderMode;

    // Shader variable 'pointers'
    int vertexLocation, texcoordLocation, normalLocation;
    std::vector<const SceneObject *> selectionBuffer;
};

} // namespace l3d {}

#endif // RENDERER_HPP
