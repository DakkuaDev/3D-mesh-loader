/*
* @Author: Daniel Guerra Gallardo
* @Date: 07/2021
* @Description: 3D mesh loader exercise
* daniel.guerra.gallardo99@gmail.com
*/

#pragma once

#ifndef CAMERA_HEADER
#define CAMERA_HEADER

#include "math.hpp"

namespace example
{
	class Camera
	{
	private:

		typedef Vector3f vec3;
		typedef Vector4f vec4;

		// Campo de visión de la cámara
		float fov;

		// Distancia del plano cercano de proyección
		float near_z;

		// Distancia del plano lejado de proyección
		float far_z;

		// Aspect ratio de la cámara
		float ratio;

		// Matrices
		Matrix44 identity;
		Matrix44 translation;

		Matrix44 rotation_x;
		Matrix44 rotation_y;
		Matrix44 rotation_z;

		// Posición de la cámara
		vec4 position;
		// Rotación de la cámara
		vec4 rotation;

		// Punto hacia el que mira la cámara
		//vec4 target = vec4(0.0f, 0.0f, -1.0f, 1.0f);

		//Matrix44 traslation;
		//Matrix44 rotation;


	public:

		Camera(float fov, float near_z, float faz_z, float ratio, vec3 position, vec3 rotation);
		~Camera() = default;

	public:

		void move(float x, float y, float z);
		void rotate_x(float angle);
		void rotate_y(float angle);
		void rotate_z(float angle);

		Matrix44 get_projection();
		Matrix44 get_camera_matrix();
		//inline vec4 get_position{ return position; }

	};

}


#endif

