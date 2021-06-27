/*
* @Author: Daniel Guerra Gallardo
* @Description: Programa de renderizado 3D de mayas poligonales
* @Date: 06/2021
*/

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

        private:
            //D:\Dev\VisualStudio\3d-mesh-loader\shared\assets
            //static constexpr char base_file_path[] = "../../shared/assets/";

            //const aiScene* scene;
            
            Color_Buffer               color_buffer;
            Rasterizer< Color_Buffer > rasterizer;

            Vertex_Buffer     original_vertices ;
            Index_Buffer      original_indices ;
            Vertex_Colors     original_colors ;
            Vertex_Buffer     transformed_vertices ;
            vector< Point4i > display_vertices ;

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
