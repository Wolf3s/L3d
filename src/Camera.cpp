
// ===============================================================================================================
// -*- C++ -*-
//
// Camera.cpp - A first person style 3D camera.
//
// Copyright (c) 2021 Guilherme R. Lampert
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

#include "Camera.hpp"
#include <cmath>

l3d::Camera::Camera()
    : right(1.0f, 0.0f, 0.0f)
    , up(0.0f, 1.0f, 0.0f)
    , forward(0.0f, 0.0f, 1.0f)
    , eye(0.0f, 0.0f, -5.0f)
{
    // Initialize to a default position (0, 0, -5)
}

l3d::Camera::Camera(const QVector3D & rightVec, const QVector3D & upVec,
                    const QVector3D & forwardVec, const QVector3D & eyeVec)
    : right(rightVec)
    , up(upVec)
    , forward(forwardVec)
    , eye(eyeVec)
{
}

void l3d::Camera::Reset(const QVector3D & rightVec, const QVector3D & upVec,
                        const QVector3D & forwardVec, const QVector3D & eyeVec)
{
    right = rightVec;
    up = upVec;
    forward = forwardVec;
    eye = eyeVec;
}

void l3d::Camera::Pitch(float angle)
{
    // Calculate new forward:
    RotateAroundAxis(forward, forward, right, angle);

    // Calculate new camera up vector:
    up = QVector3D::crossProduct(forward, right);
}

void l3d::Camera::Rotate(float angle)
{
    float xxx, zzz;
    float sinAng = sinf(angle);
    float cosAng = cosf(angle);

    // Save off forward components for computation
    xxx = forward.x();
    zzz = forward.z();

    // Rotate forward vector
    forward.setX(xxx * cosAng + zzz * sinAng);
    forward.setZ(xxx * -sinAng + zzz * cosAng);

    // Save off up components for computation
    xxx = up.x();
    zzz = up.z();

    // Rotate up vector
    up.setX(xxx * cosAng + zzz * sinAng);
    up.setZ(xxx * -sinAng + zzz * cosAng);

    // Save off right components for computation
    xxx = right.x();
    zzz = right.z();

    // Rotate right vector
    right.setX(xxx * cosAng + zzz * sinAng);
    right.setZ(xxx * -sinAng + zzz * cosAng);
}

void l3d::Camera::Move(MoveDir dir, float amount, float x, float y, float z)
{
    switch (dir)
    {
    case Camera::FORWARD: // Move along the camera's forward vector:
        eye.setX(eye.x() + (forward.x() * amount) * x);
        eye.setY(eye.y() + (forward.y() * amount) * y);
        eye.setZ(eye.z() + (forward.z() * amount) * z);
        break;

    case Camera::BACK: // Move along the camera's negative forward vector:
        eye.setX(eye.x() - (forward.x() * amount) * x);
        eye.setY(eye.y() - (forward.y() * amount) * y);
        eye.setZ(eye.z() - (forward.z() * amount) * z);
        break;

    case Camera::LEFT: // Move along the camera's negative right vector:
        eye.setX(eye.x() + (right.x() * amount) * x);
        eye.setY(eye.y() + (right.y() * amount) * y);
        eye.setZ(eye.z() + (right.z() * amount) * z);
        break;

    case Camera::RIGHT: // Move along the camera's right vector:
        eye.setX(eye.x() - (right.x() * amount) * x);
        eye.setY(eye.y() - (right.y() * amount) * y);
        eye.setZ(eye.z() - (right.z() * amount) * z);
        break;

    default: // Invalid argument!
        break;
    }

    /*const QVector3D xyz(x, y, z);
	switch (dir)
	{
	case Camera::FORWARD: // Move along the camera's forward vector:
		eye += (forward * amount) * xyz;
		break;

	case Camera::BACK: // Move along the camera's negative forward vector:
		eye -= (forward * amount) * xyz;
		break;

	case Camera::LEFT : // Move along the camera's negative right vector:
		eye += (right * amount) * xyz;
		break;

	case Camera::RIGHT: // Move along the camera's right vector:
		eye -= (right * amount) * xyz;
		break;

	default: // Invalid argument!
		break;
	}*/
}

void l3d::Camera::RotateAroundAxis(QVector3D & result, const QVector3D & vec,
                                   const QVector3D & axis, float angle)
{
    float sinAng = sinf(angle);
    float cosAng = cosf(angle);

    const float oneMinusCosAng = (1.0f - cosAng);
    const float aX = axis.x();
    const float aY = axis.y();
    const float aZ = axis.z();

    // Calculate X component:
    float xxx = (aX * aX * oneMinusCosAng + cosAng) * vec.x() +
                (aX * aY * oneMinusCosAng + aZ * sinAng) * vec.y() +
                (aX * aZ * oneMinusCosAng - aY * sinAng) * vec.z();

    // Calculate Y component:
    float yyy = (aX * aY * oneMinusCosAng - aZ * sinAng) * vec.x() +
                (aY * aY * oneMinusCosAng + cosAng) * vec.y() +
                (aY * aZ * oneMinusCosAng + aX * sinAng) * vec.z();

    // Calculate Z component:
    float zzz = (aX * aZ * oneMinusCosAng + aY * sinAng) * vec.x() +
                (aY * aZ * oneMinusCosAng - aX * sinAng) * vec.y() +
                (aZ * aZ * oneMinusCosAng + cosAng) * vec.z();

    result.setX(xxx);
    result.setY(yyy);
    result.setZ(zzz);
}
