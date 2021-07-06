/*
* @Author: Daniel Guerra Gallardo
* @Date: 07/2021
* @Description: 3D mesh loader exercise
* daniel.guerra.gallardo99@gmail.com
*/

#include "Camera.hpp"

namespace example
{
	Camera::Camera(float fov, float near_z, float far_z, float ratio, vec3 position, vec3 rotation)
		: position(vec4(position, 1)), rotation(vec4(rotation, 1)), fov(fov), near_z(near_z), far_z(far_z), ratio(ratio)
	{
		identity = Matrix44(1);
		translation = translate(identity, Vector3f{ position.x, position.y, position.z});
		rotation_x = Matrix44(1);
		rotation_y = Matrix44(1);
		rotation_z = Matrix44(1);
	}

	void Camera::move(float x, float y, float z)
	{
		position += vec4(x, y, z, 1.0f);
		//target += position;

		translation = translate(identity, Vector3f{ position.x, position.y, position.z });

	}

	void Camera::rotate_x(float angle)
	{
		rotation += vec4(angle, 0, 0, 1.0f);
		rotation_x = rotate_around_x(identity, (float)rotation.x);
	}

	void Camera::rotate_y(float angle)
	{
		rotation += vec4(0, angle, 0, 1.0f);
		rotation_y = rotate_around_y(identity, (float)rotation.y);
	}

	void Camera::rotate_z(float angle)
	{
		rotation += vec4(0, 0, angle, 1.0f);
		rotation_z = rotate_around_z(identity, (float)rotation.z);
	}

	Matrix44 Camera::get_projection()
	{
		return glm::perspective(fov, ratio, near_z, far_z);
	}

	Matrix44 Camera::get_camera_matrix()
	{
		Matrix44 transformation(1);

		transformation = translation * rotation_x * rotation_y * rotation_z;
		return transformation;
		
		//glm::lookAt(glm::vec3(position.x, position.y, position.z), glm::vec3(target.x, target.y, target.z), glm::vec3(0, 1.0f, 0));
	}
}
