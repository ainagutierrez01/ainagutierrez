#include "camera.h"

#include "main/includes.h"
#include <iostream>

Camera::Camera()
{
	view_matrix.SetIdentity();
	SetOrthographic(-1, 1, 1, -1, -1, 1);

}

Vector3 Camera::GetLocalVector(const Vector3& v)
{
	Matrix44 iV = view_matrix;
	if (iV.Inverse() == false)
		std::cout << "Matrix Inverse error" << std::endl;
	Vector3 result = iV.RotateVector(v);
	return result;
}

Vector3 Camera::ProjectVector(Vector3 pos, bool& negZ)
{
	Vector4 pos4 = Vector4(pos.x, pos.y, pos.z, 1.0);
	Vector4 result = viewprojection_matrix * pos4;
	negZ = result.z < 0;
	if (type == ORTHOGRAPHIC)
		return result.GetVector3();
	else
		return result.GetVector3() / result.w;
}

void Camera::Rotate(float angle, const Vector3& axis)
{
	Matrix44 R;
	R.SetRotation(angle, axis);
	Vector3 new_front = R * (center - eye);
	center = eye + new_front;
	UpdateViewMatrix();
}

void Camera::Move(Vector3 delta)
{
	Vector3 localDelta = GetLocalVector(delta);
	eye = eye - localDelta;
	center = center - localDelta;
	UpdateViewMatrix();
}

void Camera::SetOrthographic(float left, float right, float top, float bottom, float near_plane, float far_plane)
{
	type = ORTHOGRAPHIC;

	this->left = left;
	this->right = right;
	this->top = top;
	this->bottom = bottom;
	this->near_plane = near_plane;
	this->far_plane = far_plane;

	UpdateProjectionMatrix();
}

void Camera::SetPerspective(float fov, float aspect, float near_plane, float far_plane)
{
	type = PERSPECTIVE;

	this->fov = fov;
	this->aspect = aspect;
	this->near_plane = near_plane;
	this->far_plane = far_plane;

	UpdateProjectionMatrix();
}

void Camera::LookAt(const Vector3& eye, const Vector3& center, const Vector3& up)
{
	this->eye = eye;
	this->center = center;
	this->up = up;

	UpdateViewMatrix();
}

void Camera::UpdateViewMatrix()
{
	// Reset Matrix (Identity)
	view_matrix.SetIdentity();

	// Comment this line to create your own projection matrix!
	SetExampleViewMatrix();

/*	Vector3 F = center - eye;
	F.Normalize();
	Vector3 S = F.Cross(up);
	S.Normalize();
	Vector3 T = S.Cross(F);

	// Remember how to fill a Matrix4x4 (check framework slides)
	// Careful with the order of matrix multiplications, and be sure to use normalized vectors!

	// Create the view matrix rotation
	view_matrix.M[0][0] = S.x; view_matrix.M[0][1] = T.x; view_matrix.M[0][2] = -F.x; view_matrix.M[0][3] = 0.0;
	view_matrix.M[1][0] = S.y; view_matrix.M[1][1] = T.y; view_matrix.M[1][2] = -F.y; view_matrix.M[1][3] = 0.0;
	view_matrix.M[2][0] = S.z; view_matrix.M[2][1] = T.z; view_matrix.M[2][2] = -F.z; view_matrix.M[2][3] = 0.0;
	view_matrix.M[3][0] = 0.0; view_matrix.M[3][1] = 0.0; view_matrix.M[3][2] = 0.0;  view_matrix.M[3][3] = 1.0;

	// Translate view matrix
	//Matrix44 translation_matrix;
	view_matrix.TranslateLocal(-eye.x, -eye.y, -eye.z);

	//view_matrix = translation_matrix * view_matrix;
	*/

	UpdateViewProjectionMatrix();
}

// Create a projection matrix
void Camera::UpdateProjectionMatrix()
{
	// Reset Matrix (Identity)
	projection_matrix.SetIdentity();

	// Comment this line to create your own projection matrix!
	SetExampleProjectionMatrix();

	// Remember how to fill a Matrix4x4 (check framework slides)

	/*if (type == PERSPECTIVE) {

		float f1 = 1.0f / tan(fov * DEG2RAD / 2.0f);
		projection_matrix.M[0][0] = f1 / aspect;
		projection_matrix.M[1][1] = f1;
		projection_matrix.M[2][2] = (far_plane + near_plane) / (near_plane - far_plane);
		projection_matrix.M[2][3] = -2.0f * ((far_plane * near_plane) / (far_plane - near_plane));
		projection_matrix.M[3][2] = -1.0f;
		projection_matrix.M[3][3] = 0.0f;

	}
	else if (type == ORTHOGRAPHIC) {

		projection_matrix.M[0][0] = 2.0f / (right - left);
		projection_matrix.M[1][1] = 2.0f / (top - bottom);
		projection_matrix.M[2][2] = -2.0f / (far_plane - near_plane);
		projection_matrix.M[0][3] = -((right + left) / (right - left));
		projection_matrix.M[1][3] = -((top + bottom) / (top - bottom));
		projection_matrix.M[2][3] = -((far_plane + near_plane) / (far_plane - near_plane));
		projection_matrix.M[3][3] = 1.0f;

	}*/

	UpdateViewProjectionMatrix();
}

void Camera::Orbit(float angle, const Vector3& axis) {
	Matrix44 O;
	O.SetRotation(angle, axis);
	Vector3 new_eye = O * (eye - center);
	eye = center + new_eye;
	UpdateViewMatrix();
}

void Camera::Zoom(float distance)
{
	Vector3 new_front = eye - center;
	eye = center + new_front * distance;
	UpdateViewMatrix();
}

void Camera::UpdateViewProjectionMatrix()
{
	viewprojection_matrix = view_matrix * projection_matrix;
}

Matrix44 Camera::GetViewProjectionMatrix()
{
	UpdateViewMatrix();
	UpdateProjectionMatrix();

	return viewprojection_matrix;
}

// The following methods have been created for testing.
// Do not modify them.

void Camera::SetExampleViewMatrix()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eye.x, eye.y, eye.z, center.x, center.y, center.z, up.x, up.y, up.z);
	glGetFloatv(GL_MODELVIEW_MATRIX, view_matrix.m);
}

void Camera::SetExampleProjectionMatrix()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (type == PERSPECTIVE)
		gluPerspective(fov, aspect, near_plane, far_plane);
	else
		glOrtho(left, right, bottom, top, near_plane, far_plane);

	glGetFloatv(GL_PROJECTION_MATRIX, projection_matrix.m);
	glMatrixMode(GL_MODELVIEW);
}