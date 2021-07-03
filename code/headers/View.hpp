
// Este código es de dominio público.
// angel.rodriguez@esne.edu
// 2013.12 - 2021.04

#ifndef VIEW_HEADER
#define VIEW_HEADER

    #include <Color_Buffer.hpp>
    #include <cstdlib>
    #include "math.hpp"
    #include "Rasterizer.hpp"
    #include <vector>

    namespace example
    {

        using  std::vector;
        using argb::Rgb888;
        using argb::Color_Buffer;

        class View
        {
        private:

            typedef Rgb888                Color;
            typedef Color_Buffer< Color > Color_Buffer;
            typedef Point4f               Vertex;
            typedef vector< Vertex >      Vertex_Buffer;
            typedef vector< int    >      Index_Buffer;
            typedef vector< Color  >      Vertex_Colors;
            typedef vector< Point4i>      Display_Buffer;

        private:

            static constexpr char mesh_file_path[] = "../../shared/assets/scene_composition.obj";

            Color_Buffer               color_buffer;
            Rasterizer< Color_Buffer > rasterizer;

            //Vertex_Buffer     original_vertices;
            vector< Vertex_Buffer >     original_vertices_vector;

            //Index_Buffer      original_indices;
            vector< Index_Buffer > original_indices_vector;

            //Vertex_Colors     original_colors;
            vector< Vertex_Colors > original_colors_vector;

            //Vertex_Buffer     transformed_vertices;
            vector< Vertex_Buffer > transformed_vertices_vector;

            //Display_Buffer display_vertices;
            vector< Display_Buffer > display_vertices_vector;

            unsigned width;
            unsigned height;
            unsigned total_meshes;

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
