
// ===============================================================================================================
// -*- C++ -*-
//
// Camera.hpp - A first person style 3D camera.
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

#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <QVector3D>

namespace l3d
{

// Camera -- A "Quake like" first person 3D camera.
class Camera
{
  public:

    Camera();
    Camera(const QVector3D & rightVec, const QVector3D & upVec,
           const QVector3D & forwardVec, const QVector3D & eyeVec);

    // Resets to a "starting" position.
    void Reset(const QVector3D & rightVec, const QVector3D & upVec,
               const QVector3D & forwardVec, const QVector3D & eyeVec);

    // Pitches camera by "angle" (in radians).
    void Pitch(float angle);

    // Rotates around world Y-axis by the given angle (in radians).
    void Rotate(float angle);

    // Valid directions to move the camera in:
    enum MoveDir
    {
        FORWARD, // Move forward relative to the camera's space
        BACK,    // Move backward relative to the camera's space
        LEFT,    // Move left relative to the camera's space
        RIGHT    // Move right relative to the camera's space
    };

    // Moves the camera by the given direction, using the provided movement amount.
    // The last three parameters indicate in which axis to move. If it is equal to 1, move in that axis, if it is zero don't move.
    void Move(MoveDir dir, float amount, float x, float y, float z);

    // This function returns what the camera is looking at. Our eye is ALWAYS the origin
    // of camera's coordinate system and we are ALWAYS looking straight down the "forward" axis
    // so to calculate the target it's just a matter of adding the eye plus the forward.
    QVector3D GetTarget() const
    {
        return QVector3D(
        eye.x() + forward.x(),
        eye.y() + forward.y(),
        eye.z() + forward.z());
    }

    QVector3D right;   // The normalized axis that points to the "right"
    QVector3D up;      // The normalized axis that points "up"
    QVector3D forward; // The normalized axis that points "forward"
    QVector3D eye;     // The position of the camera (i.e. the camera's eye and the origin of the camera's coordinate system)

  private:

    /*	Initial Camera Axes:
			(up)
			+Y   +Z (forward)
			|   /
			|  /
			| /
			+ ------ +X (right)
		*/

    // This allows us to rotate "vec" around an arbitrary "axis" by the "angle" in radians.
    static void RotateAroundAxis(QVector3D & result, const QVector3D & vec, const QVector3D & axis, float angle);
};

} // namespace l3d {}

#endif // CAMERA_HPP
