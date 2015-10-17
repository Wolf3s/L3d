
// ===============================================================================================================
// -*- C++ -*-
//
// Mesh.cpp - Represents a mesh of polygons in the system.
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

#include "Mesh.hpp"
#include "GLWidget.hpp"

#include <cassert>
#include <stdexcept>       // For std::runtime_error
#include <assimp.hpp>      // C++ importer interface
#include <aiScene.h>       // Output data structure
#include <aiPostProcess.h> // Post processing flags

static const char * GLErr2String(GLenum err)
{
    switch (err)
    {
    case GL_NO_ERROR:
        return "GL_NO_ERROR";
    case GL_INVALID_ENUM:
        return "GL_INVALID_ENUM";
    case GL_INVALID_VALUE:
        return "GL_INVALID_VALUE";
    case GL_INVALID_OPERATION:
        return "GL_INVALID_OPERATION";
    case GL_STACK_OVERFLOW:
        return "GL_STACK_OVERFLOW";
    case GL_STACK_UNDERFLOW:
        return "GL_STACK_UNDERFLOW";
    case GL_OUT_OF_MEMORY:
        return "GL_OUT_OF_MEMORY";
    default:
        return "Unknown error";
    }
}

static std::string ExtractFilePath(const std::string & fileName)
{
    std::string::size_type lastSlash = fileName.find_last_of('/');
    if (lastSlash == std::string::npos)
    {
        lastSlash = fileName.find_last_of('\\');
    }

    std::string path = ((lastSlash != std::string::npos) ? fileName.substr(0, lastSlash + 1) : "");
    return path;
}

// Fetch the texture list for this mesh. The list can be used latter on to load the individual textures
static void assimp_FetchTextureList(const aiScene * scene, const std::string & fileName, l3d::Mesh * mesh)
{
    // Extract the file path from the file name
    std::string dir = ExtractFilePath(fileName);

    for (unsigned int i = 0; i < scene->mNumMaterials; ++i)
    {
        const aiMaterial * pMaterial = scene->mMaterials[i];
        mesh->textures[i] = "";

        if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0)
        {
            aiString path;

            if (pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
            {
                std::string fullPath = dir + path.data;
                mesh->textures[i] = fullPath;
            }
        }
    }
}

// Convert an Assimp mesh to a more simple l3d::Mesh object for use in the application
static void assimp_MeshSetup(size_t index, const aiMesh * assimpMesh, l3d::Mesh * mesh)
{
    mesh->subMeshes[index].textureIndex = assimpMesh->mMaterialIndex;

    unsigned int i;
    std::vector<l3d::Mesh::Vertex> vertices;
    std::vector<unsigned int> indices;
    const aiVector3D zero3D(0.0f, 0.0f, 0.0f);

    for (i = 0; i < assimpMesh->mNumVertices; ++i)
    {
        const aiVector3D * pPos = &(assimpMesh->mVertices[i]);
        const aiVector3D * pNormal = &(assimpMesh->mNormals[i]);
        const aiVector3D * pTexCoord = assimpMesh->HasTextureCoords(0) ? &(assimpMesh->mTextureCoords[0][i]) : &zero3D;

        l3d::Mesh::Vertex v(QVector3D(pPos->x, pPos->y, pPos->z),
                            QVector2D(pTexCoord->x, pTexCoord->y),
                            QVector3D(pNormal->x, pNormal->y, pNormal->z));

        vertices.push_back(v);
    }

    for (i = 0; i < assimpMesh->mNumFaces; ++i)
    {
        const aiFace & face = assimpMesh->mFaces[i];
        assert(face.mNumIndices == 3);
        indices.push_back(face.mIndices[0]);
        indices.push_back(face.mIndices[1]);
        indices.push_back(face.mIndices[2]);
    }

    mesh->subMeshes[index].Setup(vertices, indices);
}

// Load using the Assimp mesh library
static void assimp_LoadMeshFromFile(const std::string & fileName, l3d::Mesh * mesh)
{
    Assimp::Importer importer;

    // The importer keeps ownership of the scene, so no need to delete it
    // ourselves, it will destroy it once it looses scope.
    const aiScene * scene = importer.ReadFile(fileName.c_str(),
                                             (aiProcess_Triangulate | aiProcess_GenSmoothNormals));

    if (scene)
    {
        mesh->subMeshes.resize(scene->mNumMeshes);
        mesh->textures.resize(scene->mNumMaterials);

        // Initialize the meshes in the scene one by one
        for (size_t i = 0; i < mesh->subMeshes.size(); ++i)
        {
            const aiMesh * assimpMesh = scene->mMeshes[i];
            assimp_MeshSetup(i, assimpMesh, mesh);
        }

        // Setup the texture list for this mesh
        assimp_FetchTextureList(scene, fileName, mesh);
    }
    else
    {
        char errorMessage[1024] = { 0 };
        sprintf(errorMessage, "Error loading mesh file \"%s\" \nError Desc: %s\n",
                fileName.c_str(), importer.GetErrorString());

        throw std::runtime_error(errorMessage);
    }
}

// Global mesh cache
l3d::Mesh::MeshCache l3d::Mesh::meshCache;

l3d::Mesh * l3d::Mesh::Create(const std::string & fileName)
{
    MeshCache::const_iterator mesh = meshCache.find(fileName);

    if (mesh == meshCache.end())
    {
        // New mesh not yet loaded
        MeshPtr m = new Mesh(fileName);
        assimp_LoadMeshFromFile(fileName, m.Get());
        meshCache.insert(MeshCache::value_type(fileName, m.Get()));
        m->AddRef();
        return m.GiveupOwnership();
    }
    else
    {
        // Already loaded, add reference and return it
        (*mesh).second->AddRef();
        return (*mesh).second;
    }
}

void l3d::Mesh::Cleanup()
{
    MeshCache::iterator i = meshCache.begin();
    MeshCache::iterator last = meshCache.end();

    while (i != last)
    {
        (*i).second->Release();
        ++i;
    }

    meshCache.clear();
}

void l3d::Mesh::SubMesh::Setup(const std::vector<l3d::Mesh::Vertex> & vertices, const std::vector<unsigned int> & indices)
{
    textureIndex = -1;
    numVertices = vertices.size();
    numIndices = indices.size();

    // Generate OpenGL buffers:

    // This call will clear the error flag.
    // It is needed to avoid reading old "residual" errors.
    GLenum glErr = glGetError();
    char errorMessage[1024] = { 0 };

    qglContext->GL->glGenBuffers(1, &vb); // Vertex buffer
    qglContext->GL->glBindBuffer(GL_ARRAY_BUFFER, vb);
    qglContext->GL->glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * numVertices, &vertices[0], GL_STATIC_DRAW);
    glErr = glGetError();

    if (glErr != GL_NO_ERROR)
    {
        sprintf(errorMessage, "Failed to generate an OpenGL Vertex Buffer! GL_ERROR = %s\n", GLErr2String(glErr));
        throw std::runtime_error(errorMessage);
    }

    qglContext->GL->glGenBuffers(1, &ib); // Index buffer
    qglContext->GL->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
    qglContext->GL->glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * numIndices, &indices[0], GL_STATIC_DRAW);
    glErr = glGetError();

    if (glErr != GL_NO_ERROR)
    {
        sprintf(errorMessage, "Failed to generate an OpenGL Index Buffer! GL_ERROR = %s\n", GLErr2String(glErr));
        throw std::runtime_error(errorMessage);
    }
}

l3d::Mesh::~Mesh()
{
    const size_t numSubMeshes = subMeshes.size();
    for (size_t i = 0; i < numSubMeshes; ++i)
    {
        qglContext->GL->glDeleteBuffers(1, &subMeshes[i].vb);
        qglContext->GL->glDeleteBuffers(1, &subMeshes[i].ib);
    }

    subMeshes.clear();
    textures.clear();
}
