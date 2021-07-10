/*
* @Author: Daniel Guerra Gallardo
* @Date: 07/2021
* @Description: 3D mesh loader exercise
* daniel.guerra.gallardo99@gmail.com
*/

#pragma once

#include "View.hpp"

#ifndef CLIP_POLYGON_HEADER
#define CLIP_POLYGON_HEADER

namespace MeshLoader
{
	class ClipPolygon
	{

	public:

		ClipPolygon() = default;
		~ClipPolygon() = default;

	public:

		/* Se realiza un recorte geometríco de la geometría mostrada en el view*/
		int clipping_polygon();

	private:

		/* Reglas que se deben cumplir para considerar el recorte */
		int clip_view_rules(Point4i* vertices, int* first_index, int* last_index, Point4i* output, float a, float b, float c);

		/* Comprueba si el nuevo vértice de la geometría se situa dentro o fuera del viewport */
		bool inside(float a, float b, float c, float vertexX, float vertexY);

	};

}


#endif

