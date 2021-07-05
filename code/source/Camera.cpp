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
		: position(vec4(position, 1)), fov(fov), near_z(near_z), far_z(far_z), ratio(ratio)
	{

	}

	void Camera::move(float x, float y, float z)
	{
		position += vec4(x, y, z, 1.0f);
		target += vec4(x, y, z, 1.0f);
	}

	Matrix44 Camera::get_projection()
	{
		return glm::perspective(fov, ratio, near_z, far_z);
	}

	Matrix44 Camera::get_camera_matrix()
	{
		/*Matrix44 transformation(1);
		transformation = projection * translation * rotation_y * scaling;*/

		return glm::lookAt(glm::vec3(position.x, position.y, position.z), glm::vec3(target.x, target.y, target.z), glm::vec3(0, 1.0f, 0));
	}
}
