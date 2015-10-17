
QT += core gui
QT += opengl

TARGET = l3d
TEMPLATE = app

INCLUDEPATH += assimp-2.0.863/include

unix:LIBS += -L../assimp-2.0.863/lib/linux -lassimp
win32:LIBS += -L../assimp-2.0.863/lib/win32 -lassimp
mac:LIBS += -L../assimp-2.0.863/lib/macosx -lassimp

FORMS += src/EditorWidget.ui

SOURCES += \
src/Main.cpp \
src/EditorWidget.cpp \
src/GLWidget.cpp \
src/Mesh.cpp \
src/TexMat.cpp \
src/SceneObject.cpp \
src/Scene.cpp \
src/Renderer.cpp \
src/Camera.cpp

HEADERS += \
src/EditorWidget.hpp \
src/GLWidget.hpp \
src/Mesh.hpp \
src/TexMat.hpp \
src/ReferenceCountable.hpp \
src/RefPtr.hpp \
src/SceneObject.hpp \
src/Scene.hpp \
src/Renderer.hpp \
src/Shaders.hpp \
src/Camera.hpp
