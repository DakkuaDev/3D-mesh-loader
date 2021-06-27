/*
* @Author: Daniel Guerra Gallardo
* @Description: Programa de renderizado 3D de mayas poligonales
* @Date: 06/2021
*/

#ifndef VIEW_HEADER
#define VIEW_HEADER

    #include <Color_Buffer.hpp>

    #include <cstdlib>
    #include <vector>

    #include "math.hpp"
    #include "Rasterizer.hpp"

    namespace example
    {

        using  std::vector;

        using argb::Rgb888;
        using argb::Color_Buffer;

        class View
        {
        private:

            // Color
            typedef Color_Buffer< Rgb888 > Color_Buffer;

            // Vértices
            typedef Point4f               Vertex;
            typedef vector< Vertex >      Vertex_Buffer;
            typedef vector< Rgb888  >     Vertex_Colors;

            // Índices
            typedef vector< int    >      Index_Buffer;

        private:

            //static constexpr char base_file_path[] = "../../shared/assets/";
            
            Color_Buffer               color_buffer;
            Rasterizer< Color_Buffer > rasterizer;

            Vertex_Buffer     original_vertices;
            Vertex_Colors     original_colors;
            Vertex_Buffer     transformed_vertices;

            Index_Buffer      original_indices;

            vector< Point4i > display_vertices;

            unsigned width;
            unsigned height;

        public:

            View(unsigned width, unsigned height);

            void update ();
            void render ();

        private:

            bool  is_frontface (const Vertex * const projected_vertices, const int * const indices);
            float rand_clamp   () { return float(rand () & 0xff) * 0.0039215f; }

        };

    }

#endif
