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

namespace MeshLoader
{
	class Camera
	{
	private:

		typedef Vector3f vec3;
		typedef Vector4f vec4;

		// Campo de visi�n de la c�mara
		float fov;

		// Distancia del plano cercano de proyecci�n
		float near_z;

		// Distancia del plano lejado de proyecci�n
		float far_z;

		// Aspect ratio de la c�mara
		float ratio;

		// Matrices
		Matrix44 identity;
		Matrix44 translation;

		Matrix44 rotation_x;
		Matrix44 rotation_y;
		Matrix44 rotation_z;

		// Posici�n de la c�mara
		vec4 position;
		// Rotaci�n de la c�mara
		vec4 rotation;

	public:

		Camera(float fov, float near_z, float faz_z, float ratio, vec3 position, vec3 rotation);
		~Camera() = default;

	public:

		/* Mueve la c�mara a una nueva posici�n */
		void move(float x, float y, float z);

		/* Gira la c�mara en el eje x */
		void rotate_x(float angle);

		/* Gira la c�mara en el eje y */
		void rotate_y(float angle);

		/* Gira la c�mara en el eje z */
		void rotate_z(float angle);

	public:

		// Propiedades
		Matrix44 get_projection();
		Matrix44 get_camera_matrix();
	};
}
#endif

