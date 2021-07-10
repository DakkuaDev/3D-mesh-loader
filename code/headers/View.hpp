/*
* @Author: Daniel Guerra Gallardo
* @Date: 07/2021
* @Description: 3D mesh loader exercise
* daniel.guerra.gallardo99@gmail.com
*/

#ifndef VIEW_HEADER
#define VIEW_HEADER

    #include "EntityTrasform.hpp"
    #include "Camera.hpp"
    #include "Light.hpp"
    #include "ClipPolygon.hpp"

    #include <Color_Buffer.hpp>
    #include <cstdlib>
    #include "Rasterizer.hpp"
    #include "math.hpp"
    #include <vector>

    namespace MeshLoader
    {

        using  std::vector;
        using argb::Rgb888;
        using argb::Color_Buffer;

        class Camera;
        class EntityTrasform;
        class ClipPolygon;
        class View
        {
        private:

            typedef Rgb888                Color;
            typedef Color_Buffer< Color > Color_Buffer;
            typedef Point4f               Vertex;
            typedef vector< Vertex >      Vertex_Buffer;
            typedef vector<Vertex  >      Normal_Buffer;
            typedef vector< int    >      Index_Buffer;
            typedef vector< Color  >      Vertex_Colors;
            typedef vector< Point4i>      Display_Buffer;

        private:

            Camera* camera;
            ClipPolygon* clip_polygon;

            static constexpr char mesh_file_path[] = "../../shared/assets/scene_composition.obj";

            Color_Buffer               color_buffer;
            Rasterizer< Color_Buffer > rasterizer;

            // Buffers (Pixel, Index, Normal, Display)
            vector< Vertex_Buffer >     original_vertices_vector;
            vector< Index_Buffer > original_indices_vector;
            vector< Vertex_Colors > original_colors_vector;
            vector< Normal_Buffer >     original_normals_vector;
            vector< Vertex_Buffer > transformed_vertices_vector;
            vector< Display_Buffer > display_vertices_vector;

            // Entidades 
            vector< EntityTrasform > entities;

            // Mallas
            unsigned total_meshes;

            // Ancho del view
            unsigned width;

            // Alto del view
            unsigned height;

            // Bakeo de la escena
            bool bake_scene;

        public:

            View(unsigned width, unsigned height, bool bake_scene = true);

            /* Bucle de trasformaciones principal de la escena */
            void update (float delta);

            /* Bucle de renderizado principal de la escena*/
            void render ();

            /* Propiedades */
            inline Rasterizer< Color_Buffer > get_rasterizer() { return rasterizer; }
            inline Camera* get_camera()  { return camera; }
            inline unsigned get_width()  { return width;  }
            inline unsigned get_height() { return height; }

            inline bool get_bake() { return bake_scene; }
            inline void set_bake(bool is_bake) { bake_scene = is_bake; }

        private:

            /* Comprueba el Z-Buffer del polígono para ver si se dibuja o no */
            bool  is_frontface (const Vertex * const projected_vertices, const int * const indices);
            float rand_clamp   () { return float(rand () & 0xff) * 0.0039215f; }

        };

    }

#endif
