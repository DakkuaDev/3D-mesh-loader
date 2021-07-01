/*
* @Author: Daniel Guerra Gallardo
* @Description: Programa de renderizado 3D de mayas poligonales
* @Date: 06/2021
*/

#include "Mesh.hpp"

#include <cassert>
#include <cmath>
#include <cstdlib>
#include "math.hpp"

namespace MeshLoaderExercise
{

    void Mesh::init_mesh(const aiMesh* paiMesh)
    {
          
        size_t number_of_vertices = paiMesh->mNumVertices;

        //Se copian los datos de coordenadas de v�rtices:

        original_vertices.resize(number_of_vertices);

        for (size_t index = 0; index < number_of_vertices; index++)
        {
            auto& vertex = paiMesh->mVertices[index];

            original_vertices[index] = Vertex(vertex.x, -vertex.y, vertex.z, 1.f);
        }

        transformed_vertices.resize(number_of_vertices);
        display_vertices.resize(number_of_vertices);

        // Se inicializan los datos de color de los v�rtices con colores aleatorios:

        original_colors.resize(number_of_vertices);

        for (size_t index = 0; index < number_of_vertices; index++)
        {
            original_colors[index].set(rand_clamp(), rand_clamp(), rand_clamp());
        }

        // Se generan los �ndices de los tri�ngulos:

        size_t number_of_triangles = paiMesh->mNumFaces;

        original_indices.resize(number_of_triangles * 3);

        Index_Buffer::iterator indices_iterator = original_indices.begin();

        for (size_t index = 0; index < number_of_triangles; index++)
        {
            auto& face = paiMesh->mFaces[index];

            assert(face.mNumIndices == 3);              // Una face puede llegar a tener de 1 a 4 �ndices,
                                                        // pero nos interesa que solo haya tri�ngulos
            auto indices = face.mIndices;

            *indices_iterator++ = int(indices[0]);
            *indices_iterator++ = int(indices[1]);
            *indices_iterator++ = int(indices[2]);
        }
    }
    

    void Mesh::update_mesh()
    {
        // Se actualizan los par�metros de transformati�n (s�lo se modifica el �ngulo):

        static float angle = 0.f;

        angle += 0.025f;

        // Se crean las matrices de transformaci�n:
        
        Matrix44 identity(1);
        Matrix44 scaling = scale(identity, 4.f);
        Matrix44 rotation_y = rotate_around_y(identity, angle);
        Matrix44 translation = translate(identity, Vector3f{ 0.f, 0.5f, -10.f });

        Matrix44 projection = perspective(20, 1, 15, float(
            model.get()->get_scene()->get_width() / model.get()->get_scene()->get_height()
        ));


        // Creaci�n de la matriz de transformaci�n unificada:

        //Matrix44 transformation = projection * translation * rotation_y * scaling;
        Matrix44 transformation = projection * translation * scaling;

        // Se transforman todos los v�rtices usando la matriz de transformaci�n resultante:

        for (size_t index = 0, number_of_vertices = original_vertices.size(); index < number_of_vertices; index++)
        {
            // Se multiplican todos los v�rtices originales con la matriz de transformaci�n y
            // se guarda el resultado en otro vertex buffer:

            Vertex& vertex = transformed_vertices[index] = transformation * original_vertices[index];

            // La matriz de proyecci�n en perspectiva hace que el �ltimo componente del vector
            // transformado no tenga valor 1.0, por lo que hay que normalizarlo dividiendo:

            float divisor = 1.f / vertex.w;

            vertex.x *= divisor;
            vertex.y *= divisor;
            vertex.z *= divisor;
            vertex.w = 1.f;
        }
    }

    void Mesh::draw_mesh()
    {
        // Se convierten las coordenadas transformadas y proyectadas a coordenadas
        // de recorte (-1 a +1) en coordenadas de pantalla con el origen centrado.
        // La coordenada Z se escala a un valor suficientemente grande dentro del
        // rango de int (que es lo que espera fill_convex_polygon_z_buffer).

        Matrix44 identity(1);
        Matrix44 scaling = scale(identity, 
            float(model.get()->get_scene()->get_width() / 2), 
            float(model.get()->get_scene()->get_height() / 2), 
            100000000.f
        );
        Matrix44 translation = translate(identity, Vector3f{ 
            float(model.get()->get_scene()->get_width() / 2),
            float(model.get()->get_scene()->get_height() / 2),
            0.f 
        });

        Matrix44 transformation = translation * scaling;

        for (size_t index = 0, number_of_vertices = transformed_vertices.size(); index < number_of_vertices; index++)
        {
            display_vertices[index] = Point4i(transformation * transformed_vertices[index]);
        }

        // Se borra el frameb�ffer y se dibujan los tri�ngulos:

        model.get()->get_scene()->get_rasterizer().clear();

        for (int* indices = original_indices.data(), *end = indices + original_indices.size(); indices < end; indices += 3)
        {
            if (is_frontface(transformed_vertices.data(), indices))
            {
                // Se establece el color del pol�gono a partir del color de su primer v�rtice:

                model.get()->get_scene()->get_rasterizer().set_color(original_colors[*indices]);

                // Se rellena el pol�gono:

                model.get()->get_scene()->get_rasterizer().fill_convex_polygon_z_buffer(display_vertices.data(), indices, indices + 3);
            }
        }

        // Se copia el frameb�ffer oculto en el frameb�ffer de la ventana:

        model.get()->get_scene()->get_rasterizer().get_color_buffer().blit_to_window();
    }

    bool Mesh::is_frontface(const Vertex* const projected_vertices, const int* const indices)
    {
        const Vertex& v0 = projected_vertices[indices[0]];
        const Vertex& v1 = projected_vertices[indices[1]];
        const Vertex& v2 = projected_vertices[indices[2]];

        // Se asumen coordenadas proyectadas y pol�gonos definidos en sentido horario.
        // Se comprueba a qu� lado de la l�nea que pasa por v0 y v1 queda el punto v2:

        return ((v1[0] - v0[0]) * (v2[1] - v0[1]) - (v2[0] - v0[0]) * (v1[1] - v0[1]) < 0.f);
    }
}
