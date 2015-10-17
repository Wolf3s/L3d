
// ===============================================================================================================
// -*- C++ -*-
//
// SceneObject.cpp - Represents an object in the scene/world. Might be a light, mesh, etc.
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

#include "SceneObject.hpp"

#include <stdexcept>
#include <cassert>

l3d::SceneObject::SceneObject(const std::string & name)
    : objectName(name)
    , mesh(0)
{
}

l3d::SceneObject::SceneObject(const SceneObject & rhs)
    : mesh(rhs.mesh)
    , xform(rhs.xform)
    , materials(rhs.materials)
{
}

l3d::SceneObject::SceneObject(const std::string & name, const MeshPtr & m, const Transform & xf)
    : objectName(name)
    , mesh(m)
    , xform(xf)
{
    assert(!mesh.IsNull());
    materials.resize(mesh->textures.size());
    for (size_t i = 0; i < mesh->textures.size(); ++i)
    {
        try
        {
            materials[i] = Material(QColor(255, 255, 255, 255),
                                    ((mesh->textures[i] != "") ? Texture::Create(mesh->textures[i]) : 0), TF_MEDIUM);
        }
        catch (std::exception & e)
        {
            materials[i] = Material();
            QMessageBox::critical(0, "Unable to load texture...", e.what());
        }
    }
}

l3d::SceneObject * l3d::SceneObject::Clone() const
{
    return new SceneObject(*this);
}

bool l3d::SceneObject::SetTexture(const std::string & fileName)
{
    try
    {
        if (materials.empty())
        {
            materials.push_back(Material());
        }

        materials[0].texture = Texture::Create(fileName);
        return true;
    }
    catch (std::exception & e)
    {
        QMessageBox::critical(0, "Unable to load texture...", e.what());
        return false;
    }
}

std::string l3d::SceneObject::GetTexture(int index) const
{
    if (materials.empty() || materials[index].texture.IsNull())
    {
        return "";
    }
    return materials[index].texture->fileName;
}

bool l3d::SceneObject::SetMesh(const std::string & fileName)
{
    try
    {
        mesh = Mesh::Create(fileName);

        materials.clear();
        materials.resize(mesh->textures.size());

        for (size_t i = 0; i < mesh->textures.size(); ++i)
        {
            try
            {
                materials[i] = Material(QColor(255, 255, 255, 255),
                                        Texture::Create(mesh->textures[i]), TF_MEDIUM);
            }
            catch (std::exception & e)
            {
                materials[i] = Material();
                QMessageBox::critical(0, "Unable to load texture...", e.what());
            }
        }

        return true;
    }
    catch (std::exception & e)
    {
        QMessageBox::critical(0, "Unable to load mesh...", e.what());
        return false;
    }
}

std::string l3d::SceneObject::GetMesh() const
{
    return (!mesh.IsNull() ? mesh->fileName : "");
}
