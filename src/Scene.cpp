
// ===============================================================================================================
// -*- C++ -*-
//
// Scene.cpp - The editor scene/world object.
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

#include "Scene.hpp"
#include "Camera.hpp"

#include <stdexcept>

// Extracts a file name from a path, stripping the extension.
static std::string ExtractFileName(const std::string & pathOrName)
{
    std::string::size_type lastSlash = pathOrName.find_last_of('/');
    if (lastSlash == std::string::npos)
    {
        lastSlash = pathOrName.find_last_of('\\');
    }

    std::string nameWithExt = ((lastSlash != std::string::npos) ?
          pathOrName.substr(lastSlash + 1, pathOrName.length()) :
          pathOrName);

    std::string::size_type dot = nameWithExt.find_last_of('.');
    std::string nameWithoutExt = ((dot != std::string::npos) ? nameWithExt.substr(0, dot) : nameWithExt);

    return nameWithoutExt;
}

static char * RemoveQuotes(char * s)
{
    // Removes the quotes (") from the beginning and end of a string.
    const size_t len = strlen(s);

    if (len > 0)
    {
        for (size_t i = 0; i < len; ++i)
        {
            s[i] = s[i + 1];
        }
        s[len - 2] = '\0';
    }

    return s;
}

// ========================================================

unsigned int l3d::Scene::objectCount = 0;

std::string l3d::Scene::NextName()
{
    char buf[128] = { 0 };
    sprintf(buf, "SceneObject_%u", objectCount++);
    return buf;
}

l3d::SceneObject * l3d::Scene::NewObject(const std::string & objectName)
{
    return NewObjectFromMeshFile("cube.obj", Transform(), objectName);
}

l3d::SceneObject * l3d::Scene::NewObjectFromMeshFile(const std::string & fileName,
                                                     const Transform & xform,
                                                     const std::string & objectName)
{
    SceneObject * o = 0;
    try
    {
        std::string name = (objectName == "") ? ExtractFileName(fileName) : objectName;
        o = new SceneObject(name, Mesh::Create(fileName), xform);
        objects.insert(SceneObjectMap::value_type(name, o));
    }
    catch (std::exception & e)
    {
        QMessageBox::critical(0, "Unable to load mesh...", e.what());
        delete o;
        o = 0;
    }
    return o;
}

void l3d::Scene::RemoveObject(const SceneObject * object)
{
    SceneObjectMap::iterator it = objects.find(object->objectName);
    if (it != objects.end())
    {
        objects.erase(it);
    }
}

void l3d::Scene::Clear()
{
    Scene::SceneObjectMap::const_iterator i = objects.begin();
    Scene::SceneObjectMap::const_iterator last = objects.end();

    // Write every scene object to the file
    while (i != last)
    {
        delete (*i).second;
        ++i;
    }

    objects.clear();
}

bool l3d::Scene::Save(const std::string & fileName, const Camera * camera)
{
    FILE * file = fopen(fileName.c_str(), "wt");
    if (!file)
    {
        return false;
    }

    fprintf(file, "[L3D Scene File]\n\n");

    if (camera)
    {
        fprintf(file, "Camera: {\n");
        fprintf(file, "\tRight: %f %f %f\n", camera->right.x(), camera->right.y(), camera->right.z());
        fprintf(file, "\tUp: %f %f %f\n", camera->up.x(), camera->up.y(), camera->up.z());
        fprintf(file, "\tForward: %f %f %f\n", camera->forward.x(), camera->forward.y(), camera->forward.z());
        fprintf(file, "\tEye: %f %f %f\n", camera->eye.x(), camera->eye.y(), camera->eye.z());
        fprintf(file, "};\n\n");
    }

    Scene::SceneObjectMap::const_iterator it = objects.begin();
    Scene::SceneObjectMap::const_iterator last = objects.end();

    // Write every scene object to the file
    while (it != last)
    {
        const SceneObject * obj = (*it).second;

        fprintf(file, "SceneObject: {\n");
        fprintf(file, "\tName: \"%s\"\n", obj->objectName.c_str());
        fprintf(file, "\tMesh: \"%s\"\n", (!obj->mesh.IsNull() ? obj->mesh->fileName.c_str() : ""));
        fprintf(file, "\tScale: %f %f %f\n", obj->xform.scale.x(), obj->xform.scale.y(), obj->xform.scale.z());
        fprintf(file, "\tRotation: %f %f %f\n", obj->xform.rotation.x(), obj->xform.rotation.y(), obj->xform.rotation.z());
        fprintf(file, "\tTranslation: %f %f %f\n", obj->xform.translation.x(), obj->xform.translation.y(), obj->xform.translation.z());

        // Print all the materials
        for (size_t i = 0; i < obj->materials.size(); ++i)
        {
            const Material & mat = obj->materials[i];

            fprintf(file, "\tMaterial: { \n");
            fprintf(file, "\t\tColor: %d %d %d\n", mat.color.red(), mat.color.green(), mat.color.blue());
            fprintf(file, "\t\tTexture: \"%s\"\n", (!mat.texture.IsNull() ? mat.texture->fileName.c_str() : ""));
            fprintf(file, "\t\tTexFilter: %s\n", (mat.textureFilter == TF_LOW) ? "LOW" : (mat.textureFilter == TF_MEDIUM) ? "MEDIUM" : "HIGH");
            fprintf(file, "\t};\n");
        }

        fprintf(file, "};\n");

        ++it;
    }

    fclose(file);
    return true;
}

bool l3d::Scene::Load(const std::string & fileName, Camera * camera)
{
    FILE * file = fopen(fileName.c_str(), "rt");
    if (!file)
    {
        return false;
    }

    // Current scene is discarded
    Clear();

    char buffer[1024] = { 0 };
    char objName[512], fName[512];

    float x, y, z;
    Transform xform;
    int r, g, b;
    TextureFilter textureFilter;

    fgets(buffer, sizeof(buffer), file);

    if (strncmp(buffer, "[L3D Scene File]", 16) != 0)
    {
        // Not a scene file
        fclose(file);
        return false;
    }

    // Scan file till the end
    while (fgets(buffer, sizeof(buffer), file))
    {
        if (strncmp(buffer, "Camera", 6) == 0)
        {
            // Read camera position if requested
            if (camera)
            {
                fgets(buffer, sizeof(buffer), file);
                sscanf(buffer, "\tRight: %f %f %f", &x, &y, &z);
                camera->right.setX(x);
                camera->right.setY(y);
                camera->right.setZ(z);

                fgets(buffer, sizeof(buffer), file);
                sscanf(buffer, "\tUp: %f %f %f", &x, &y, &z);
                camera->up.setX(x);
                camera->up.setY(y);
                camera->up.setZ(z);
                fgets(buffer, sizeof(buffer), file);

                sscanf(buffer, "\tForward: %f %f %f", &x, &y, &z);
                camera->forward.setX(x);
                camera->forward.setY(y);
                camera->forward.setZ(z);

                fgets(buffer, sizeof(buffer), file);
                sscanf(buffer, "\tEye: %f %f %f", &x, &y, &z);
                camera->eye.setX(x);
                camera->eye.setY(y);
                camera->eye.setZ(z);
            }
        }
        else if (strncmp(buffer, "SceneObject", 11) == 0)
        {
            // New object

            // Get name:
            fgets(buffer, sizeof(buffer), file);
            sscanf(buffer, "\tName: %s", objName);
            RemoveQuotes(objName);

            // Get mesh file:
            fgets(buffer, sizeof(buffer), file);
            sscanf(buffer, "\tMesh: %s", fName);
            RemoveQuotes(fName);

            // Get scale component:
            fgets(buffer, sizeof(buffer), file);
            sscanf(buffer, "\tScale: %f %f %f", &x, &y, &z);
            xform.scale.setX(x);
            xform.scale.setY(y);
            xform.scale.setZ(z);

            // Get rotation component:
            fgets(buffer, sizeof(buffer), file);
            sscanf(buffer, "\tRotation: %f %f %f", &x, &y, &z);
            xform.rotation.setX(x);
            xform.rotation.setY(y);
            xform.rotation.setZ(z);

            // Get translation component:
            fgets(buffer, sizeof(buffer), file);
            sscanf(buffer, "\tTranslation: %f %f %f", &x, &y, &z);
            xform.translation.setX(x);
            xform.translation.setY(y);
            xform.translation.setZ(z);

            SceneObject * obj = NewObjectFromMeshFile(fName, xform, objName);

            // Read the materials:
            fgets(buffer, sizeof(buffer), file);
            if (strncmp(buffer, "\tMaterial", 9) == 0)
            {
                // Has a material
                fgets(buffer, sizeof(buffer), file);
                sscanf(buffer, "\t\tColor: %d %d %d", &r, &g, &b);

                fgets(buffer, sizeof(buffer), file);
                sscanf(buffer, "\t\tTexture: %s", fName);
                RemoveQuotes(fName);

                char texFilterStr[100];
                fgets(buffer, sizeof(buffer), file);
                sscanf(buffer, "\t\tTexFilter: %s", texFilterStr);

                if (strcmp(texFilterStr, "LOW") == 0)
                {
                    textureFilter = TF_LOW;
                }
                else if (strcmp(texFilterStr, "MEDIUM") == 0)
                {
                    textureFilter = TF_MEDIUM;
                }
                else if (strcmp(texFilterStr, "HIGH") == 0)
                {
                    textureFilter = TF_HIGH;
                }
                else
                {
                    assert(0);
                }

                obj->materials[0].color.setRgb(r, g, b);

                if (obj->materials[0].texture.IsNull() || (obj->materials[0].texture->fileName != fName))
                {
                    if (*fName != '\0')
                    {
                        try
                        {
                            obj->materials[0].texture = Texture::Create(fName);
                        }
                        catch (std::exception & e)
                        {
                            QMessageBox::critical(0, "Unable to load texture...", e.what());
                        }
                    }
                }

                obj->materials[0].textureFilter = textureFilter;
            }
        }
    }

    fclose(file);
    return true;
}
