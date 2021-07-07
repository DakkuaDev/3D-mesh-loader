/*
* @Author: Daniel Guerra Gallardo
* @Date: 07/2021
* @Description: 3D mesh loader exercise
* daniel.guerra.gallardo99@gmail.com
*/

#include "Light.hpp"

#include <cmath>
#include <ctgmath>

namespace example
{
	Light::Light(vec3 position) : position (vec4(position, 1))
	{
		//Normalice light 
		float normalize_value = sqrt(position.x) + pow(position.y, 2) + pow(position.z, 2);

		position.x /= normalize_value;
		position.y /= normalize_value;
		position.z /= normalize_value;
	}

	Vector3f Light::calculate_light(float angle)
	{

		// Iluminación Ambiental
		vec3 Iam = vec3(ka * Ia.x, ka * Ia.y, ka * Ia.z);

		// Iluminación Difusa
		vec3 Idiff = vec3(kd * cos(angle) * Ia.x, kd * cos(angle) * Ia.y, kd * cos(angle) * Ia.z);
		
		auto result_light = Iam + Idiff;
		return result_light;
	}
}
