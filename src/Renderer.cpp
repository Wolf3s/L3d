
// ===============================================================================================================
// -*- C++ -*-
//
// Renderer.cpp - Wrapper to an OpenGL renderer.
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

#include "Renderer.hpp"
#include "Shaders.hpp"
#include "GLWidget.hpp"

#include <stdexcept>

l3d::Renderer::Renderer()
    : lightPosition(0.0f, 5.0f, 5.0f, 1.0f)
    , ambientLight(1.0f, 0.5f, 0.5f, 1.0f)
    , diffuseLight(1.0f, 0.5f, 0.5f, 1.0f)
    , specularLight(1.0f, 1.0f, 1.0f, 1.0f)
    , shininess(5.0f)
    , defaultTexture(0)
{
    SetupShaders();
    SetRenderMode(RM_TEXTURE_SHADED); // Default render mode

    // Set some OpenGL states
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);

    glLineWidth(1.0f);
    glEnable(GL_LINE_SMOOTH);

    defaultTexture = Texture::Create("chess.png");
}

void l3d::Renderer::SetRenderMode(l3d::RenderMode renderMode)
{
    switch (renderMode)
    {
    case RM_WIREFRAME:
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDisable(GL_CULL_FACE);
        break;

    case RM_TEXTURE_SHADED:
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glEnable(GL_CULL_FACE);
        break;

    default:
        assert(false);
        break;
    }

    this->renderMode = renderMode;
}

void l3d::Renderer::RenderScene(const l3d::Scene * scene)
{
    Scene::SceneObjectMap::const_iterator i = scene->objects.begin();
    Scene::SceneObjectMap::const_iterator last = scene->objects.end();

    selectionBuffer.clear();

    while (i != last)
    {
        RenderSceneObject((*i).second);
        ++i;
    }
}

void l3d::Renderer::RenderSceneObject(const l3d::SceneObject * object)
{
    const Mesh * mesh = object->mesh.Get();

    if (mesh)
    {
        // Scene object is renderable (have a mesh associated)

        // Set transform
        QMatrix4x4 modelMatrix;
        modelMatrix.translate(object->xform.translation);

        // Build rotation quaternion (the rotation vector contains the rotation degrees for x,y,z)
        const QQuaternion rotationQuat =
            QQuaternion::fromAxisAndAngle(1, 0, 0, object->xform.rotation.x()) *
            QQuaternion::fromAxisAndAngle(0, 1, 0, object->xform.rotation.y()) *
            QQuaternion::fromAxisAndAngle(0, 0, 1, object->xform.rotation.z());

        modelMatrix.rotate(rotationQuat);
        modelMatrix.scale(object->xform.scale);

        const QMatrix4x4 MVPMatrix = projectionMatrix * viewMatrix * modelMatrix;
        const QMatrix4x4 invMVP = MVPMatrix.inverted();
        const QMatrix4x4 normalMatrix = invMVP.transposed();

        // Set some shader uniforms:
        defaultShader.bind();
        defaultShader.setUniformValue("MVPMatrix", MVPMatrix);
        defaultShader.setUniformValue("normalMatrix", normalMatrix);
        defaultShader.setUniformValue("lightPosition", lightPosition);
        defaultShader.setUniformValue("ambientProduct", ambientLight);
        defaultShader.setUniformValue("diffuseProduct", diffuseLight);
        defaultShader.setUniformValue("specularProduct", specularLight);
        defaultShader.setUniformValue("shininess", shininess);

        // Apply material
        ApplyMaterial(&object->materials[0]); //FIXME: Right now only material[0] is applied.

        // Render
        RenderMesh(mesh);

        selectionBuffer.push_back(object);
    }
}

void l3d::Renderer::RenderMesh(const l3d::Mesh * mesh)
{
    unsigned int offset = 0;
    const size_t numSubMeshes = mesh->subMeshes.size();

    for (size_t i = 0; i < numSubMeshes; ++i)
    {
        qglContext->GL->glBindBuffer(GL_ARRAY_BUFFER, mesh->subMeshes[i].vb);
        qglContext->GL->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->subMeshes[i].ib);

        defaultShader.enableAttributeArray(vertexLocation);
        qglContext->GL->glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, sizeof(l3d::Mesh::Vertex), (const void *)offset);

        // Offset for texture coordinate
        offset += sizeof(QVector3D);

        defaultShader.enableAttributeArray(texcoordLocation);
        qglContext->GL->glVertexAttribPointer(texcoordLocation, 2, GL_FLOAT, GL_FALSE, sizeof(l3d::Mesh::Vertex), (const void *)offset);

        // Offset for normal coordinate
        offset += sizeof(QVector2D);

        defaultShader.enableAttributeArray(normalLocation);
        qglContext->GL->glVertexAttribPointer(normalLocation, 3, GL_FLOAT, GL_FALSE, sizeof(l3d::Mesh::Vertex), (const void *)offset);

        glDrawElements(GL_TRIANGLES, mesh->subMeshes[i].numIndices, GL_UNSIGNED_INT, 0);
    }
}

void l3d::Renderer::ApplyMaterial(const l3d::Material * mat)
{
    if (!mat->texture.IsNull())
    {
        SetTexture(mat->texture->textureId, mat->textureFilter);
    }
    else
    {
        SetTexture(defaultTexture->textureId, TF_MEDIUM);
    }

    defaultShader.setUniformValue("objectColor",
                                  QVector4D(mat->color.redF(), mat->color.greenF(), mat->color.blueF(), 1.0f));
}

const l3d::SceneObject * l3d::Renderer::Pick(int x, int y)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    const size_t n = selectionBuffer.size();

    for (unsigned int i = 0; i < n; ++i)
    {
        ColorOnlyRendering(selectionBuffer[i], i + 1);
    }

    GLubyte pixel[4] = { 0 };
    glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, (void *)pixel);

    unsigned int id = (0 << 24) | (pixel[0] << 16) | (pixel[1] << 8) | pixel[2];
    id--;

    const SceneObject * obj;

    if (id < n)
    {
        obj = selectionBuffer[id];
    }
    else
    {
        obj = 0;
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    return obj;
}

void l3d::Renderer::ColorOnlyRendering(const l3d::SceneObject * object, QRgb c)
{
    const Mesh * mesh = object->mesh.Get();

    if (mesh)
    {
        // Scene object is renderable (have a mesh associated)

        // Set transform
        QMatrix4x4 modelMatrix;
        modelMatrix.translate(object->xform.translation);

        // Build rotation quaternion (the rotation vector contains the rotation degrees for x,y,z)
        QQuaternion rotationQuat =
            QQuaternion::fromAxisAndAngle(1, 0, 0, object->xform.rotation.x()) *
            QQuaternion::fromAxisAndAngle(0, 1, 0, object->xform.rotation.y()) *
            QQuaternion::fromAxisAndAngle(0, 0, 1, object->xform.rotation.z());

        modelMatrix.rotate(rotationQuat);
        modelMatrix.scale(object->xform.scale);

        colorOnlyShader.bind();
        colorOnlyShader.setUniformValue("modelView", viewMatrix * modelMatrix);
        colorOnlyShader.setUniformValue("projection", projectionMatrix);

        glDisable(GL_DITHER);

        QColor color(c); // Use the id as a color
        colorOnlyShader.setUniformValue("objectColor",
                                        QVector4D(color.redF(), color.greenF(), color.blueF(), color.alphaF()));

        const size_t numSubMeshes = mesh->subMeshes.size();
        for (size_t i = 0; i < numSubMeshes; ++i)
        {
            qglContext->GL->glBindBuffer(GL_ARRAY_BUFFER, mesh->subMeshes[i].vb);
            qglContext->GL->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->subMeshes[i].ib);

            int position = colorOnlyShader.attributeLocation("inPosition");
            colorOnlyShader.enableAttributeArray(position);
            qglContext->GL->glVertexAttribPointer(position, 3, GL_FLOAT, GL_FALSE, sizeof(l3d::Mesh::Vertex), (const void *)0);

            glDrawElements(GL_TRIANGLES, mesh->subMeshes[i].numIndices, GL_UNSIGNED_INT, 0);
        }

        glEnable(GL_DITHER);
    }
}

void l3d::Renderer::SetupShaders()
{
    // Overriding system locale until shaders are compiled
    setlocale(LC_NUMERIC, "C");

    if (!defaultShader.addShaderFromSourceCode(QGLShader::Vertex, defaultVertShader))
    {
        throw std::runtime_error("Failed to compile Vertex Shader! Fatal error.");
    }

    if (!defaultShader.addShaderFromSourceCode(QGLShader::Fragment, defaultFragShader))
    {
        throw std::runtime_error("Failed to compile Fragment Shader! Fatal error.");
    }

    if (!defaultShader.link())
    {
        throw std::runtime_error("Failed to link shader program! Fatal error.");
    }

    if (!colorOnlyShader.addShaderFromSourceCode(QGLShader::Vertex, colorOnlyVertShader))
    {
        throw std::runtime_error("Failed to compile Vertex Shader! Fatal error.");
    }

    if (!colorOnlyShader.addShaderFromSourceCode(QGLShader::Fragment, colorOnlyFragShader))
    {
        throw std::runtime_error("Failed to compile Fragment Shader! Fatal error.");
    }

    if (!colorOnlyShader.link())
    {
        throw std::runtime_error("Failed to link shader program! Fatal error.");
    }

    // Restore system locale
    setlocale(LC_ALL, "");

    // Cache this values for efficiency
    vertexLocation   = defaultShader.attributeLocation("inPosition");
    texcoordLocation = defaultShader.attributeLocation("inTextCoord");
    normalLocation   = defaultShader.attributeLocation("inNormal");
}

void l3d::Renderer::SetTexture(GLuint texId, l3d::TextureFilter texFilter)
{
    static const GLint texFilter2GLMagFilter[] = {
        // TF_LOW
        GL_NEAREST,
        // TF_MEDIUM
        GL_LINEAR,
        // TF_HIGH
        GL_LINEAR
    };

    static const GLint texFilter2GLMinFilter[] = {
        // TF_LOW
        GL_NEAREST,
        // TF_MEDIUM
        GL_NEAREST_MIPMAP_NEAREST,
        // TF_HIGH
        GL_LINEAR_MIPMAP_LINEAR
    };

    defaultShader.setUniformValue("texture", 0);

    qglContext->GL->glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texFilter2GLMinFilter[texFilter]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texFilter2GLMagFilter[texFilter]);
}
