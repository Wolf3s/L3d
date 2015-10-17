
// ===============================================================================================================
// -*- C++ -*-
//
// Mesh.hpp - Represents a mesh of polygons in the system.
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

#ifndef MESH_HPP
#define MESH_HPP

#include <map>
#include <string>
#include <QtOpenGL>

#include "RefPtr.hpp"
#include "ReferenceCountable.hpp"

namespace l3d
{

// Basic polygon mesh (Reference Countable)
class Mesh
	: public ReferenceCountable
{
  public:

    // Factory method to load and create mesh objects based on the file read.
    static Mesh * Create(const std::string & fileName);

    // Free all cached meshes.
    static void Cleanup();

    // A mesh vertex
    struct Vertex
    {
        QVector3D position;
        QVector2D texCoord;
        QVector3D normal;

        Vertex(const QVector3D & pos, const QVector2D & tex, const QVector3D & norm)
            : position(pos)
            , texCoord(tex)
            , normal(norm)
        {
        }

        Vertex & operator=(const Vertex & rhs)
        {
            this->position = rhs.position;
            this->texCoord = rhs.texCoord;
            this->normal = rhs.normal;
            return *this;
        }
    };

    // Sub mesh in the main mesh object
    struct SubMesh
    {
        GLuint vb;
        GLuint ib;
        size_t numVertices;
        size_t numIndices;
        int textureIndex; // Index in the 'Mesh::textures' array (-1 for invalid)

        void Setup(const std::vector<Vertex> & vertices,
                   const std::vector<unsigned int> & indices);
    };

    // File that originated this mesh.
    std::string fileName;

    // The sub-meshes that compose this mesh.
    std::vector<SubMesh> subMeshes;

    // Texture files this mesh references.
    std::vector<std::string> textures;

  private:

    typedef std::map<std::string, Mesh *> MeshCache;
    static MeshCache meshCache; // No two meshes are loaded twice with this cache.

  protected:

    Mesh(const std::string & name)
        : fileName(name) { }

    ~Mesh();
};

typedef RefPtr<Mesh> MeshPtr;

} // namespace l3d {}

#endif // MESH_HPP
