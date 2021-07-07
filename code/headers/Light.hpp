/*
* @Author: Daniel Guerra Gallardo
* @Date: 07/2021
* @Description: 3D mesh loader exercise
* daniel.guerra.gallardo99@gmail.com
*/

#pragma once

#ifndef LIGHT_HEADER
#define LIGHT_HEADER

#include "math.hpp"

namespace example
{
	class Light
	{
	private:

		typedef Vector4f vec4;
		typedef Vector3f vec3;
	
		// Posición de la luz
		vec4 position;

		//Intensidad ambiental (luz indirecta) 
		vec3 Ia = vec3(0.75f, 0.75f, 0.75f);

		// Constante de reflectividad en superficie ambiental (0.0f - 1.0f)
		float ka = 0.2f;

		// Constante de reflectividad difusa (0.4f - 0.7f)
		float kd = 0.5f;


	public:
		Light(vec3 pos);
		~Light() = default;

	public:
		vec3 calculate_light(float angle);

	public: 
		inline vec4 get_position() { return position; }
	};
}

#endif


