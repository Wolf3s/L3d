
// ===============================================================================================================
// -*- C++ -*-
//
// TexMat.hpp - Texture and Material classes.
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

#ifndef TEX_MAT_HPP
#define TEX_MAT_HPP

#include <map>
#include <string>
#include <QColor>
#include <QtOpenGL>

#include "RefPtr.hpp"
#include "ReferenceCountable.hpp"

namespace l3d
{

enum TextureFilter
{
    TF_LOW,    // Lowest quality filter, fastest.
    TF_MEDIUM, // Medium quality texture filter.
    TF_HIGH    // Best filter available, slowest speed.
};

// Basic reference counted texture object.
class Texture
    : public ReferenceCountable
{
  public:

    // Factory method to load and create mesh objects based on the file read.
    static Texture * Create(const std::string & fileName);

    // Free all cached textures. Usually called before exiting.
    static void Cleanup();

    // Texture handle for OpenGL
    GLuint textureId;

    // File that originated this texture
    std::string fileName;

  private:

    Texture(GLuint texId, const std::string & file)
        : textureId(texId)
        , fileName(file)
    {
    }

    typedef std::map<std::string, Texture *> TextureCache;
    static TextureCache textureCache; // Cached textures to avoid duplicity

  protected:

    ~Texture();
};

typedef RefPtr<Texture> TexturePtr;

// Material to be applied to a mesh.
class Material
{
  public:

    Material() // Default color, no texture
    : color(255, 255, 255, 255),
      texture(0),
      textureFilter(TF_LOW)
    {
    }

    Material(const QColor & c, const TexturePtr & tex, TextureFilter texFilter)
        : color(c)
        , texture(tex)
        , textureFilter(texFilter)
    {
    }

    Material & operator=(const Material & rhs)
    {
        this->color = rhs.color;
        this->texture = rhs.texture;
        this->textureFilter = rhs.textureFilter;
        return *this;
    }

  public:

    QColor color;
    TexturePtr texture;
    TextureFilter textureFilter;
};

} // namespace l3d {}

#endif // TEX_MAT_HPP
