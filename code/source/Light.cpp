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
		float normalize_value = sqrt(pow(Ia.x, 2) + pow(Ia.y, 2) + pow(Ia.z, 2));;

		Ia.x /= normalize_value;
		Ia.y /= normalize_value;
		Ia.z /= normalize_value;
	}

	Vector3f Light::calculate_light(Vector3f normal)
	{

		// Iluminación Ambiental ( Iam = ka * Ia )
		vec3 Iam = vec3(ka * Ia.x, ka * Ia.y, ka * Ia.z);

		float normalize_value_a = sqrt(pow(Iam.x, 2) + pow(Iam.y, 2) + pow(Iam.z, 2));
		Iam.x /= normalize_value_a;
		Iam.y /= normalize_value_a;
		Iam.z /= normalize_value_a;

		// Iluminación Difusa ( Idiff = kd * normal * Ia )
		vec3 Idiff = vec3(kd * normal.x * Ia.x, kd * normal.y * Ia.y, kd * normal.z * Ia.z);

		float normalize_value_b = sqrt(pow(Idiff.x, 2) + pow(Idiff.y, 2) + pow(Idiff.z, 2));
		Idiff.x /= normalize_value_b;
		Idiff.y /= normalize_value_b;
		Idiff.z /= normalize_value_b;
		
		auto result_light = Iam * Idiff;

		return result_light;
	}
}
