/*
* @Author: Daniel Guerra Gallardo
* @Date: 07/2021
* @Description: 3D mesh loader exercise
* daniel.guerra.gallardo99@gmail.com
*/

#include <cassert>
#include <cmath>
#include "math.hpp"
#include "View.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace example
{

    View::View(unsigned width, unsigned height)
    :
        width       (width ),
        height      (height),
        color_buffer(width, height),
        rasterizer  (color_buffer )
    {
        // Incializo la cámara de la escena
        camera = new Camera(90, 1, 15, float(width) / height, Vector3f(0, 0, 0), Vector3f(0, 0, 0));
        //Matrix44 projection = perspective(20, 1, 15, float(width) / height);

        Assimp::Importer importer;

        auto scene = importer.ReadFile
        (
            mesh_file_path,
            aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType
        );

        total_meshes = scene->mNumMeshes;

        // Si scene es un puntero nulo significa que el archivo no se pudo cargar con éxito:

        if (scene && scene->mNumMeshes > 0)
        {
            for (int i = 0; i < total_meshes; i++)
            {
                // Para este ejemplo se coge la primera malla solamente:

                auto mesh = scene->mMeshes[i];

                // Creo una nueva entidad de la maya para poderla trasformar por separado
                EntityTrasform entity("entity" + std::to_string(i));
                entities.push_back(entity);

                size_t number_of_vertices = mesh->mNumVertices;

                // Se copian los datos de coordenadas de vértices:
  
                Vertex_Buffer     original_vertices;
                original_vertices.resize(number_of_vertices);

                for (size_t index = 0; index < number_of_vertices; index++)
                {
                    auto& vertex = mesh->mVertices[index];

                    original_vertices[index] = Vertex(vertex.x, -vertex.y, vertex.z, 1.f);
                }
                original_vertices_vector.push_back(original_vertices);

                Vertex_Buffer     transformed_vertices;
                transformed_vertices.resize(number_of_vertices);
                transformed_vertices_vector.push_back(transformed_vertices);

                Display_Buffer display_vertices;
                display_vertices.resize(number_of_vertices);
                display_vertices_vector.push_back(display_vertices);

                // Se inicializan los datos de color de los vértices con colores aleatorios:

                Vertex_Colors     original_colors;
                original_colors.resize(number_of_vertices);

                for (size_t index = 0; index < number_of_vertices; index++)
                {
                    original_colors[index].set(rand_clamp(), rand_clamp(), rand_clamp());
                }
                original_colors_vector.push_back(original_colors);

                // Se generan los índices de los triángulos:

                size_t number_of_triangles = mesh->mNumFaces;

                Index_Buffer      original_indices;
                original_indices.resize(number_of_triangles * 3);

                Index_Buffer::iterator indices_iterator = original_indices.begin();

                for (size_t index = 0; index < number_of_triangles; index++)
                {
                    auto& face = mesh->mFaces[index];

                    assert(face.mNumIndices == 3);              // Una face puede llegar a tener de 1 a 4 índices,
                                                                // pero nos interesa que solo haya triángulos
                    auto indices = face.mIndices;

                    *indices_iterator++ = int(indices[0]);
                    *indices_iterator++ = int(indices[1]);
                    *indices_iterator++ = int(indices[2]);
                }
                original_indices_vector.push_back(original_indices);
            }

            // Uso un grafo de escena ( Isla (parent) -> Casa (child) )
            entities.at(1).set_parent(entities.at(0));
        }
    }

    void View::update ()
    {

        for (int i = 0; i < total_meshes; i++)
        {

            // 1. Se actualizan los parámetros de transformatión (sólo se modifica el ángulo):

            static float angle = 0.f;
            angle += 0.0025f;

            // 2. Se trasforma la entidad
            entities.at(i).scale_entity(0.05f);
            entities.at(i).rotate_entity_y(angle);
            entities.at(i).traslate_entity(0.f, 3.f, -3.f);


            // Creación de la matriz de transformación unificada:
            //Matrix44 projection = perspective(20, 1, 15, float(width) / height);
            Matrix44 projection = camera->get_projection();
            Matrix44 transformation = camera->get_camera_matrix() * entities.at(i).update_trasform(projection);

            // TODO: Añadir la cámara correctamente. Cambiar la clase a matrices y pasarla la proyección de vista(?
            //Matrix44 transformation = 
                //camera->get_projection() * camera->get_camera_matrix() *  entities.at(i).update_trasform(projection);

            // 3. Se transforman todos los vértices usando la matriz de transformación resultante:

            for (size_t index = 0, number_of_vertices = original_vertices_vector[i].size(); index < number_of_vertices; index++)
            {
                // Se multiplican todos los vértices originales con la matriz de transformación y
                // se guarda el resultado en otro vertex buffer:
                Vertex & vertex = transformed_vertices_vector[i][index] = transformation * original_vertices_vector[i][index];

                // La matriz de proyección en perspectiva hace que el último componente del vector
                // transformado no tenga valor 1.0, por lo que hay que normalizarlo dividiendo:

                float divisor = 1.f / vertex.w;

                vertex.x *= divisor;
                vertex.y *= divisor;
                vertex.z *= divisor;
                vertex.w  = 1.f;
            }
        }
    }

    void View::render ()
    {
        // Se convierten las coordenadas transformadas y proyectadas a coordenadas
        // de recorte (-1 a +1) en coordenadas de pantalla con el origen centrado.
        // La coordenada Z se escala a un valor suficientemente grande dentro del
        // rango de int (que es lo que espera fill_convex_polygon_z_buffer).

        rasterizer.clear ();

        for (int i = 0; i < total_meshes; i++)
        {

            Matrix44 identity(1);
            Matrix44 scaling        = scale (identity, float(width / 2), float(height / 2), 100000000.f);
            Matrix44 translation    = translate (identity, Vector3f{ float(width / 2), float(height / 2), 0.f });
            Matrix44 transformation = translation * scaling;

            for (size_t index = 0, number_of_vertices = transformed_vertices_vector[i].size (); index < number_of_vertices; index++)
            {
                display_vertices_vector[i][index] = Point4i( transformation * transformed_vertices_vector[i][index] );
            }

            // Se borra el framebúffer y se dibujan los triángulos:


            for (int * indices = original_indices_vector[i].data (), * end = indices + original_indices_vector[i].size (); indices < end; indices += 3)
            {
                if (is_frontface (transformed_vertices_vector[i].data (), indices))
                {
                    // Se establece el color del polígono a partir del color de su primer vértice:

                    rasterizer.set_color (original_colors_vector[i][*indices]);

                    // Se rellena el polígono:

                    rasterizer.fill_convex_polygon_z_buffer (display_vertices_vector[i].data (), indices, indices + 3);
                }
            }

            // Se copia el framebúffer oculto en el framebúffer de la ventana:

            color_buffer.blit_to_window ();

        }
    }

    bool View::is_frontface (const Vertex * const projected_vertices, const int * const indices)
    {
        const Vertex & v0 = projected_vertices[indices[0]];
        const Vertex & v1 = projected_vertices[indices[1]];
        const Vertex & v2 = projected_vertices[indices[2]];

        // Se asumen coordenadas proyectadas y polígonos definidos en sentido horario.
        // Se comprueba a qué lado de la línea que pasa por v0 y v1 queda el punto v2:

        return ((v1[0] - v0[0]) * (v2[1] - v0[1]) - (v2[0] - v0[0]) * (v1[1] - v0[1]) < 0.f);
    }

}
