
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

#include "GLWidget.hpp"
#include "EditorWidget.hpp"
#include "Renderer.hpp"
#include "Scene.hpp"

const int l3d::GLWidget::SceneRepaintIntervalMs = 30;
const float l3d::GLWidget::CameraMovementSpeed = 5.0f * (1.0f / 30.0f);
const float l3d::GLWidget::CameraRotationSpeed = 1.0f * (1.0f / 30.0f);

l3d::GLWidget::GLWidget(QWidget * parent)
    : QGLWidget(parent)
    , cameraPitchAmt(0.0f)
    , timer(new QBasicTimer)
    , camera()
    , renderer(0)
    , scene(0)
    , selectedObj(0)
{
    memset(keys, 0, sizeof(keys));
}

l3d::GLWidget::~GLWidget()
{
    delete timer;
    delete scene;
    delete renderer;

    Mesh::Cleanup();
    Texture::Cleanup();

    delete GL;
}

void l3d::GLWidget::mousePressEvent(QMouseEvent * e)
{
    Q_UNUSED(e);
    setFocus();

    if (QApplication::keyboardModifiers() & Qt::ShiftModifier)
    {
        setCursor(Qt::BlankCursor);
    }
    else
    {
        QPoint pt = QCursor::pos();
        int cursorX = pt.x() - editorWindow->getInspectorXOffset();
        int cursorY = pt.y();
        const SceneObject * obj = renderer->Pick(cursorX, this->height() - cursorY - 1);

        if (obj != selectedObj)
        {
            // Selection changed
            selectedObj = const_cast<SceneObject *>(obj);
            editorWindow->resetUI();
        }
    }
}

void l3d::GLWidget::mouseReleaseEvent(QMouseEvent * e)
{
    Q_UNUSED(e);

    if (QApplication::keyboardModifiers() & Qt::ShiftModifier)
    {
        setCursor(Qt::ArrowCursor);
    }
}

void l3d::GLWidget::mouseMoveEvent(QMouseEvent * e)
{
    Q_UNUSED(e);

    // Only move the camera if SHIFT is down
    if (!(QApplication::keyboardModifiers() & Qt::ShiftModifier))
    {
        return;
    }

    static const float MaxAngle = 89.5f; // Max degrees of rotation
    static const float Deg2Rad = (3.14159265359f / 180.0f);

    // Get the middle of the screen
    QSize widgetSize = editorWindow->size();
    const int midScrX = widgetSize.width() >> 1;
    const int midScrY = widgetSize.height() >> 1;

    float amt;
    QPoint pt = QCursor::pos();

    // Rotate left/right
    amt = static_cast<float>(midScrX - pt.x()) * CameraRotationSpeed;
    float rAngle = amt * Deg2Rad; // Store angle in radians
    camera.Rotate(rAngle);

    // Calculate amount to rotate up/down
    amt = static_cast<float>(midScrY - pt.y()) * CameraRotationSpeed;

    // Clamp pitch amount
    if ((cameraPitchAmt + amt) <= -MaxAngle)
    {
        amt = -MaxAngle - cameraPitchAmt;
        cameraPitchAmt = -MaxAngle;
    }
    else if ((cameraPitchAmt + amt) >= MaxAngle)
    {
        amt = MaxAngle - cameraPitchAmt;
        cameraPitchAmt = MaxAngle;
    }
    else
    {
        cameraPitchAmt += amt;
    }

    // Pitch camera
    camera.Pitch(amt * Deg2Rad);

    // Set our cursor back to the middle of the screen to avoid problems
    QCursor::setPos(midScrX, midScrY);

    updateGL();
}

void l3d::GLWidget::keyPressEvent(QKeyEvent * e)
{
    switch (e->key())
    {
    case Qt::Key_W:
        keys[KEY_W] = 1;
        break;
    case Qt::Key_Up:
        keys[KEY_UP] = 1;
        break;
    case Qt::Key_S:
        keys[KEY_S] = 1;
        break;
    case Qt::Key_Down:
        keys[KEY_DOWN] = 1;
        break;
    case Qt::Key_D:
        keys[KEY_D] = 1;
        break;
    case Qt::Key_Right:
        keys[KEY_RIGHT] = 1;
        break;
    case Qt::Key_A:
        keys[KEY_A] = 1;
        break;
    case Qt::Key_Left:
        keys[KEY_LEFT] = 1;
        break;
    default:
        break;
    }

    if ((e->key() == Qt::Key_Delete) && selectedObj)
    {
        scene->RemoveObject(selectedObj);
        selectedObj = 0;
        editorWindow->resetUI();
    }
}

void l3d::GLWidget::keyReleaseEvent(QKeyEvent * e)
{
    switch (e->key())
    {
    case Qt::Key_W:
        keys[KEY_W] = 0;
        break;
    case Qt::Key_Up:
        keys[KEY_UP] = 0;
        break;
    case Qt::Key_S:
        keys[KEY_S] = 0;
        break;
    case Qt::Key_Down:
        keys[KEY_DOWN] = 0;
        break;
    case Qt::Key_D:
        keys[KEY_D] = 0;
        break;
    case Qt::Key_Right:
        keys[KEY_RIGHT] = 0;
        break;
    case Qt::Key_A:
        keys[KEY_A] = 0;
        break;
    case Qt::Key_Left:
        keys[KEY_LEFT] = 0;
        break;
    default:
        break;
    }
}

void l3d::GLWidget::timerEvent(QTimerEvent * e)
{
    Q_UNUSED(e);
    updateGL();
}

void l3d::GLWidget::initializeGL()
{
    qglClearColor(Qt::gray);

    GL = new QGLFunctions(QGLContext::currentContext());
    renderer = new Renderer;
    scene = new Scene;

    // Try to load the default initial scene
    if (!scene->Load("initial.l3d", &camera))
    {
        QMessageBox::critical(0, "Error", "Failed to load the default scene \"initial.l3d\" ...");
    }

    timer->start(SceneRepaintIntervalMs, this);
}

void l3d::GLWidget::resizeGL(int w, int h)
{
    // Set OpenGL viewport to cover whole widget
    glViewport(0, 0, w, h);

    qreal aspect = (qreal)w / ((qreal)h ? h : 1);
    const qreal zNear = 0.5, zFar = 1000.0, fov = 60.0;

    // Reset projection
    renderer->projectionMatrix.setToIdentity();
    // Set perspective projection
    renderer->projectionMatrix.perspective(fov, aspect, zNear, zFar);
}

void l3d::GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Check the keyboard input to update the camera:
    if (keys[KEY_W] || keys[KEY_UP])
    {
        camera.Move(Camera::FORWARD, CameraMovementSpeed, 1.0f, 1.0f, 1.0f);
    }
    if (keys[KEY_S] || keys[KEY_DOWN])
    {
        camera.Move(Camera::BACK, CameraMovementSpeed, 1.0f, 1.0f, 1.0f);
    }
    if (keys[KEY_D] || keys[KEY_RIGHT])
    {
        camera.Move(Camera::RIGHT, CameraMovementSpeed, 1.0f, 1.0f, 1.0f);
    }
    if (keys[KEY_A] || keys[KEY_LEFT])
    {
        camera.Move(Camera::LEFT, CameraMovementSpeed, 1.0f, 1.0f, 1.0f);
    }

    renderer->viewMatrix.setToIdentity();
    renderer->viewMatrix.lookAt(camera.eye, camera.GetTarget(), camera.up);
    renderer->RenderScene(scene);

    // Draw a wireframe outline on the selected object
    if (selectedObj)
    {
        RenderMode oldRenderMode = renderer->GetRenderMode();
        renderer->SetRenderMode(RM_WIREFRAME);
        QColor c;
        c.setRgbF(0.2f, 0.8f, 0.35f);
        renderer->ColorOnlyRendering(selectedObj, c.rgb());
        renderer->SetRenderMode(oldRenderMode);
    }
}

namespace l3d
{
GLWidget * qglContext = 0;
}
