
// ===============================================================================================================
// -*- C++ -*-
//
// TexMat.cpp - Texture and Material classes.
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

#include "TexMat.hpp"
#include "GLWidget.hpp"

#include <stdexcept> // For std::runtime_error

// Global texture cache
l3d::Texture::TextureCache l3d::Texture::textureCache;

l3d::Texture * l3d::Texture::Create(const std::string & fileName)
{
    TextureCache::const_iterator texture = textureCache.find(fileName);

    if (texture == textureCache.end())
    {
        // New texture not yet loaded
        QImage img;

        if (!img.load(fileName.c_str()))
        {
            char errorMessage[1024] = { 0 };
            sprintf(errorMessage, "Failed to load image: \"%s\"\n", fileName.c_str());
            throw std::runtime_error(errorMessage);
        }

        Texture * t = new Texture(qglContext->bindTexture(img), fileName);
        textureCache.insert(TextureCache::value_type(fileName, t));
        t->AddRef();
        return t;
    }
    else
    {
        // Already loaded, add reference and return it
        (*texture).second->AddRef();
        return (*texture).second;
    }
}

void l3d::Texture::Cleanup()
{
    TextureCache::iterator i = textureCache.begin();
    TextureCache::iterator last = textureCache.end();

    while (i != last)
    {
        (*i).second->Release();
        ++i;
    }

    textureCache.clear();
}

l3d::Texture::~Texture()
{
    qglContext->deleteTexture(textureId);
}
