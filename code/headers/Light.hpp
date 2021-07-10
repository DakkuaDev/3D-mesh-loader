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

#include <cassert>
#include <cmath>

#include <vector>

namespace MeshLoader
{
	class Light
	{
	private:

		typedef Vector4f vec4;
		typedef Vector3f vec3;
	
		// Posición de la luz
		vec4 position;

		//Intensidad ambiental (luz indirecta) 
		vec3 Ia = vec3(1.f, 1.f, 1.f);

		// Constante de reflectividad en superficie ambiental (0.0f - 1.0f)
		float ka = 0.2f;

		// Constante de reflectividad difusa (0.4f - 0.7f)
		float kd = 0.5f;


	public:
		Light(vec3 pos);
		~Light() = default;

	public:

		/* Calcula la luz en la escena: Ambiental + Difusa */
		vec3 calculate_light(Vector3f);

	public: 

		// Propiedades
		inline vec4 get_ambient_light() { return vec4(Ia, 1); }
	};
}

#endif


