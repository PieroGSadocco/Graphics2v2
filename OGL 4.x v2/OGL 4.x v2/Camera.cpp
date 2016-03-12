#include "Camera.h"

Camera::Camera(float _movSpeed, float _rotSpeed)
{
	movSpeed = _movSpeed;
	rotSpeed = _rotSpeed;
}

Camera::~Camera()
{

}

// Raw Local Rotation
void Camera::RotateLocal(float angleRadians, const glm::vec3& axis) 
{
	glm::quat q = glm::angleAxis(angleRadians, axis);
	RotateGlobal(q);
}

// Raw Global Rotation
void Camera::RotateGlobal(const glm::quat& rotation)
{
	orientation = rotation * orientation;
}

// Local Rotations
void Camera::RotateLocalX() 
{
	RotateLocal(rotSpeed, glm::vec3(1.0f, 0.0f, 0.0f));
}
void Camera::RotateLocalY() 
{
	RotateLocal(rotSpeed, glm::vec3(0.0f, 1.0f, 0.0f));
}
void Camera::RotateLocalZ() 
{
	RotateLocal(rotSpeed, glm::vec3(0.0f, 0.0f, 1.0f));
}
void Camera::RotateLocalX(float _angle)
{
	RotateLocal(_angle, glm::vec3(1.0f, 0.0f, 0.0f));
}
void Camera::RotateLocalY(float _angle)
{
	RotateLocal(_angle, glm::vec3(0.0f, 1.0f, 0.0f));
}
void Camera::RotateLocalZ(float _angle)
{
	RotateLocal(_angle, glm::vec3(0.0f, 0.0f, 1.0f));
}

// Global Rotations
void Camera::RotateGlobalX() 
{
	glm::quat q = glm::angleAxis(rotSpeed, orientation * glm::vec3(1.0f, 0.0f, 0.0f));
	RotateGlobal(q);
}
void Camera::RotateGlobalY() 
{
	glm::quat q = glm::angleAxis(rotSpeed, orientation * glm::vec3(0.0f, 1.0f, 0.0f));
	RotateGlobal(q);
}
void Camera::RotateGlobalZ() 
{
	glm::quat q = glm::angleAxis(rotSpeed, orientation * glm::vec3(0.0f, 0.0f, 1.0f));
	RotateGlobal(q);
}
void Camera::RotateGlobalX(float _angle) 
{
	glm::quat q = glm::angleAxis(_angle, orientation * glm::vec3(1.0f, 0.0f, 0.0f));
	RotateGlobal(q);
}
void Camera::RotateGlobalY(float _angle) 
{
	glm::quat q = glm::angleAxis(_angle, orientation * glm::vec3(0.0f, 1.0f, 0.0f));
	RotateGlobal(q);
}
void Camera::RotateGlobalZ(float _angle) 
{
	glm::quat q = glm::angleAxis(_angle, orientation * glm::vec3(0.0f, 0.0f, 1.0f));
	RotateGlobal(q);
}

// Get Global Axis
glm::vec3 Camera::GetLocalForwardAxis()
{
	return glm::conjugate(orientation) * glm::vec3(0.0f, 0.0f, -1.0f);
}
glm::vec3 Camera::GetLocalBackwardAxis()
{
	return glm::conjugate(orientation) * glm::vec3(0.0f, 0.0f, +1.0f);
}
glm::vec3 Camera::GetLocalRightAxis()
{
	return glm::conjugate(orientation) * glm::vec3(+1.0, 0.0f, 0.0f);
}
glm::vec3 Camera::GetLocalLeftAxis()
{
	return glm::conjugate(orientation) * glm::vec3(-1.0, 0.0f, 0.0f);
}
glm::vec3 Camera::GetLocalUpAxis()
{
	return glm::conjugate(orientation) * glm::vec3(0.0f, 1.0f, 0.0f);
}
glm::vec3 Camera::GetLocalDownAxis()
{
	return glm::conjugate(orientation) * glm::vec3(0.0f, -1.0f, 0.0f);
}

// Move Localy
void Camera::MoveForwardLocal()
{
	position += GetLocalForwardAxis() * movSpeed;
}
void Camera::MoveBackwardLocal()
{
	position += GetLocalBackwardAxis() * movSpeed;
}
void Camera::MoveRightLocal()
{
	position += GetLocalRightAxis() * movSpeed;
}
void Camera::MoveLeftLocal()
{
	position += GetLocalLeftAxis() * movSpeed;
}
void Camera::MoveUpLocal()
{
	position += GetLocalUpAxis() * movSpeed;
}
void Camera::MoveDownLocal()
{
	position += GetLocalDownAxis() * movSpeed;
}

void Camera::MoveForwardLocal(float _angle)
{
	position += GetLocalForwardAxis() * _angle;
}
void Camera::MoveBackwardLocal(float _angle)
{
	position += GetLocalBackwardAxis() * _angle;
}
void Camera::MoveRightLocal(float _angle)
{
	position += GetLocalRightAxis() * _angle;
}
void Camera::MoveLeftLocal(float _angle)
{
	position += GetLocalLeftAxis() * _angle;
}
void Camera::MoveUpLocal(float _angle)
{
	position += GetLocalUpAxis() * _angle;
}
void Camera::MoveDownLocal(float _angle)
{
	position += GetLocalDownAxis() * _angle;
}

// Move Globaly
void Camera::MoveForwardGlobal()
{
	position += glm::vec3(0.0f, 0.0f, -1.0f) * movSpeed;
}
void Camera::MoveBackwardGlobal()
{
	position += glm::vec3(0.0f, 0.0f, +1.0f) * movSpeed;
}
void Camera::MoveRightGlobal()
{
	position += glm::vec3(+1.0, 0.0f, 0.0f) * movSpeed;
}
void Camera::MoveLeftGlobal()
{
	position += glm::vec3(-1.0, 0.0f, 0.0f) * movSpeed;
}
void Camera::MoveUpGlobal()
{
	position += glm::vec3(0.0f, +1.0f, 0.0f) * movSpeed;
}
void Camera::MoveDownGlobal()
{
	position += glm::vec3(0.0f, -1.0f, 0.0f) * movSpeed;
}

void Camera::MoveForwardGlobal(float _angle)
{
	position += glm::vec3(0.0f, 0.0f, -1.0f) * _angle;
}
void Camera::MoveBackwardGlobal(float _angle)
{
	position += glm::vec3(0.0f, 0.0f, +1.0f) * _angle;
}
void Camera::MoveRightGlobal(float _angle)
{
	position += glm::vec3(+1.0, 0.0f, 0.0f) * _angle;
}
void Camera::MoveLeftGlobal(float _angle)
{
	position += glm::vec3(-1.0, 0.0f, 0.0f) * _angle;
}
void Camera::MoveUpGlobal(float _angle)
{
	position += glm::vec3(0.0f, +1.0f, 0.0f) * _angle;
}
void Camera::MoveDownGlobal(float _angle)
{
	position += glm::vec3(0.0f, -1.0f, 0.0f) * _angle;
}

// Get Matrix
glm::mat4 Camera::getViewMatrix() 
{
	glm::mat4 viewMatrix = glm::mat4_cast(orientation);
	viewMatrix = glm::translate(viewMatrix, -position);
	return viewMatrix;
}

glm::vec3 Camera::GetRadians()
{
	return glm::eulerAngles(orientation);
}



glm::vec3 Camera::GetEuler()
{
	glm::vec3 euler = glm::eulerAngles(orientation);
	euler.x = euler.x / 3.141592f * 180;
	euler.y *= euler.y / 3.141592f * 180;
	euler.z *= euler.z / 3.141592f * 180;
	return euler;
}

#include <Windows.h>
#include <math.h>
glm::vec3 Camera::GetOrientationVector()
{
	glm::vec3 radian = GetRadians();
	glm::vec3 vector;
	vector.x = sin(radian.y);
	vector.y = -sin(radian.x)*cos(radian.y);
	vector.z = -(cos(radian.x)*cos(radian.y));;
	if (GetAsyncKeyState(VK_END))
		int ii = 0;
	return vector;
}

