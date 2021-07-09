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

namespace example
{
	//class View;
	class ClipPolygon
	{

	private:

		//View* view;

	public:

		ClipPolygon() = default;
		//ClipPolygon(View& view) : view(&view) {};;
		~ClipPolygon() = default;

	public:

		int clipping_polygon();

	private:
		int clip_view_rules(Point4i* vertices, int* first_index, int* last_index, Point4i* output, float a, float b, float c);
		bool inside(float a, float b, float c, float vertexX, float vertexY);

	};

}


#endif

