
// ===============================================================================================================
// -*- C++ -*-
//
// GLWidget.hpp - Qt->OpenGL context "widget".
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

#ifndef GLWIDGET_HPP
#define GLWIDGET_HPP

#include <QtOpenGL/QGLWidget>
#include <QtOpenGL/QGLShaderProgram>

#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QtGui>

#include "Camera.hpp"
#include "SceneObject.hpp"

namespace l3d
{
class Renderer;
class Scene;

class GLWidget
	: public QGLWidget
{
    Q_OBJECT

  public:

    QGLFunctions * GL;
    SceneObject * selectedObj; // Current object selected in the inspector
    Renderer * renderer;
    Scene * scene;
    Camera camera;

    explicit GLWidget(QWidget * parent = 0);
    virtual ~GLWidget();

  protected:

    void mousePressEvent(QMouseEvent * e);
    void mouseReleaseEvent(QMouseEvent * e);
    void mouseMoveEvent(QMouseEvent * e);

    void keyPressEvent(QKeyEvent * e);
    void keyReleaseEvent(QKeyEvent * e);

    void timerEvent(QTimerEvent * e);

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

  private:

    // The scene is repainted every time this number of milliseconds
    // is elapsed, or, when an event that modify its contents occur.
    static const int SceneRepaintIntervalMs;

    // Movement and rotation speeds for the camera, tweaked by hand.
    static const float CameraMovementSpeed;
    static const float CameraRotationSpeed;
    float cameraPitchAmt;

    enum ImportantKeys
    {
        KEY_W,
        KEY_A,
        KEY_S,
        KEY_D,
        KEY_UP,
        KEY_DOWN,
        KEY_LEFT,
        KEY_RIGHT,
        KEY_COUNT
    };

    int keys[KEY_COUNT];
    QBasicTimer * timer;
};

// Qt -> OpenGL context
extern GLWidget * qglContext;

} // namespace l3d {}

#endif // GLWIDGET_HPP
