#ifndef CAMERA_H
#define CAMERA_H

#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"

#include "GL\glew.h"
#include "GL\wglew.h"

class Camera
{
public:
	Camera(float _movSpeed = 0.01f, float _rotSpeed = 0.01f);
	~Camera();

	float movSpeed;
	float rotSpeed;

	void Bind(GLint _shaderMatrixUniform)
	{
		glUniform3f(_shaderMatrixUniform, position.x, position.y, position.z);
	};

	// Raw Local Rotation
	void RotateLocal(float angleRadians, const glm::vec3& axis);

	// Raw Global Rotation
	void RotateGlobal(const glm::quat& rotation);

	// Local Rotation
	void RotateLocalX();
	void RotateLocalY();
	void RotateLocalZ();
	void RotateLocalX(float _angle);
	void RotateLocalY(float _angle);
	void RotateLocalZ(float _angle);

	// Global Rotation
	void RotateGlobalX();
	void RotateGlobalY();
	void RotateGlobalZ();
	void RotateGlobalX(float _angle);
	void RotateGlobalY(float _angle);
	void RotateGlobalZ(float _angle);

	// Get Global Axis
	glm::vec3 GetLocalForwardAxis();
	glm::vec3 GetLocalBackwardAxis();
	glm::vec3 GetLocalLeftAxis();
	glm::vec3 GetLocalRightAxis();
	glm::vec3 GetLocalUpAxis();
	glm::vec3 GetLocalDownAxis();

	// Move Localy
	void MoveForwardLocal();
	void MoveBackwardLocal();
	void MoveRightLocal();
	void MoveLeftLocal();
	void MoveUpLocal();
	void MoveDownLocal();
	void MoveForwardLocal(float _angle);
	void MoveBackwardLocal(float _angle);
	void MoveRightLocal(float _angle);
	void MoveLeftLocal(float _angle);
	void MoveUpLocal(float _angle);
	void MoveDownLocal(float _angle);
	
	// Move Globaly
	void MoveForwardGlobal();
	void MoveBackwardGlobal();
	void MoveRightGlobal();
	void MoveLeftGlobal();
	void MoveUpGlobal();
	void MoveDownGlobal();
	void MoveForwardGlobal(float _angle);
	void MoveBackwardGlobal(float _angle);
	void MoveRightGlobal(float _angle);
	void MoveLeftGlobal(float _angle);
	void MoveUpGlobal(float _angle);
	void MoveDownGlobal(float _angle);

	// Get Matrix
	glm::mat4 getViewMatrix();
	glm::vec3 GetRadians();
	glm::vec3 GetEuler();
	glm::vec3 GetOrientationVector();

	glm::vec3 position;
	glm::quat orientation;
private:
};

#endif