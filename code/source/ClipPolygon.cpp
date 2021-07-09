#include "ClipPolygon.hpp"

#include <cmath>
#include <math.hpp>

namespace example
{

	int ClipPolygon::clipping_polygon()
	{

        // NOT WORK

        //Point4i clipped_vertices[10];
        //int     clipped_indices[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        //int clipped_vertex_count;

        //Point4i aux_vertices_1[10];
        //Point4i aux_vertices_2[10];
        //int aux_indices[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        //int window_width = view->get_width();

        //clipped_vertex_count = clip_view_rules(aux_vertices_2, aux_indices, aux_indices + clipped_vertex_count + 3, aux_vertices_2, 1, 0, window_width);
        //clipped_vertex_count = clip_view_rules(aux_vertices_1, aux_indices, aux_indices + clipped_vertex_count, aux_vertices_2, 1, 0, window_width);
        //clipped_vertex_count = clip_view_rules(aux_vertices_2, aux_indices, aux_indices + clipped_vertex_count, aux_vertices_1, 1, 0, window_width);
        //clipped_vertex_count = clip_view_rules(aux_vertices_1, aux_indices, aux_indices + clipped_vertex_count, clipped_vertices, 1, 0, window_width);


        //if (clipped_vertex_count > 2)
        //{
        //    view->get_rasterizer().fill_convex_polygon(clipped_vertices, clipped_indices, clipped_indices + clipped_vertex_count);
        //}

        //return clipped_vertex_count;

        return 0;
	}

    int ClipPolygon::clip_view_rules(Point4i* vertices, int* first_index, int* last_index, Point4i* output, float a, float b, float c)
    {
        int total_count_vertex = last_index - first_index;
        int new_total_count = 0;

        for (int* i = first_index; i < last_index; i++)
        {

            Point4i cp1 = vertices[*i];
            int k = *(i + 1);

            if (i >= last_index - 1)
                k = *first_index;

            Point4i cp2 = vertices[k];

            float wx = cp2.x - cp1.x;
            float wy = cp2.y - cp1.y;
            float wz = cp2.z - cp1.z;

            float t = (-a * cp1.x - b * cp1.y - c) / (a * wx + b * wy);

            // Intersección
            int new_vertex[4] = { cp1.x + wx * t , cp1.y + wy * t  , cp1.z + wz * t, 1 };
            Point4i inters = { new_vertex[0], new_vertex[1], new_vertex[2], new_vertex[3] };

            // Caso 1: Ambos vértices están dentro
            if (inside(a, b, c, cp1.x, cp1.y) && inside(a, b, c, cp2.x, cp2.y)) {
                output[new_total_count++] = cp2;
            }

            // Caso 2: El primer vértice está fuera mientras que el segundo está adentro
            else if (!inside(a, b, c, cp1.x, cp1.y) && inside(a, b, c, cp2.x, cp2.y))
            {
                output[new_total_count++] = inters;
                output[new_total_count++] = cp2;
            }

            // Caso 3: El primer vértice está dentro mientras que el segundo está fuera
            else if (inside(a, b, c, cp1.x, cp1.y) && !inside(a, b, c, cp2.x, cp2.y))
                output[new_total_count++] = inters;

            // Caso 4: Ambos vértices están fuera
            else if (!inside(a, b, c, cp1.x, cp1.y) && !inside(a, b, c, cp2.x, cp2.y)) {}

        }
        return new_total_count;
    }

    bool ClipPolygon::inside(float a, float b, float c, float vertexX, float vertexY)
    {
        return ((a * vertexX + b * vertexY + c) >= 0);
    }
}
