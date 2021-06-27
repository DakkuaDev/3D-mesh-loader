/*
* @Author: Daniel Guerra Gallardo
* @Description: Programa de renderizado 3D de mayas poligonales
* @Date: 06/2021
*/

#include "Mesh.hpp"

#include <assimp/scene.h>

namespace MeshLoaderExercise
{

	//Mesh::Mesh(View* _view, int _id, vector< Vertex> vertices, vector< int > indices)
	//	:
	//	view(_view),
    //  mesh_id (_id),
	//	color_buffer(view->get_width(), view->get_height()),
	//	rasterizer(color_buffer)
	//{
	//	// Se inicializan los valores de los buffers de la maya
	//	//original_vertices.resize(vertices.size());

	//	//////transformed_vertices.resize(vertices.size());
	//	//display_vertices.resize(vertices.size());

	//	//original_colors.resize(vertices.size());

	//	//original_indices.resize(indices.size());

	//	// Se iniciliza la maya
	//	setup_mesh();

	//}

    Mesh::Mesh(View& _view, int _id)
        :
        view(&_view),
        mesh_id(_id),
        color_buffer(view->get_width(), view->get_height()),
        rasterizer(color_buffer)
    {
        setup_mesh();
    }

	void Mesh::setup_mesh()
	{
        const aiScene* scene;

        // Se obtiene la malla
        auto mesh = scene->mMeshes[mesh_id];

        size_t number_of_vertices = mesh->mNumVertices;

        // Se copian los datos de coordenadas de vértices:

        original_vertices.resize(number_of_vertices);

        for (size_t index = 0; index < number_of_vertices; index++)
        {
            auto& vertex = mesh->mVertices[index];

            original_vertices[index] = Vertex(vertex.x, -vertex.y, vertex.z, 1.f);
        }

        transformed_vertices.resize(number_of_vertices);
        display_vertices.resize(number_of_vertices);

        // Se inicializan los datos de color de los vértices con colores aleatorios:

        original_colors.resize(number_of_vertices);

        for (size_t index = 0; index < number_of_vertices; index++)
        {
            original_colors[index].set(rand_clamp(), rand_clamp(), rand_clamp());
            //original_colors[index].set(186, 186, 186);
        }

        // Se generan los índices de los triángulos:

        size_t number_of_triangles = mesh->mNumFaces;

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
	}

    void Mesh::draw()
    {
        // Se convierten las coordenadas transformadas y proyectadas a coordenadas
        // de recorte (-1 a +1) en coordenadas de pantalla con el origen centrado.
        // La coordenada Z se escala a un valor suficientemente grande dentro del
        // rango de int (que es lo que espera fill_convex_polygon_z_buffer).

        Matrix44 identity(1);
        Matrix44 scaling = scale(identity, float(view->get_width() / 2), float(view->get_height() / 2), 100000000.f);
        Matrix44 translation = translate(identity, Vector3f{ float(view->get_width() / 2), float(view->get_height() / 2), 0.f });
        Matrix44 transformation = translation * scaling;

        for (size_t index = 0, number_of_vertices = transformed_vertices.size(); index < number_of_vertices; index++)
        {
            display_vertices[index] = Point4i(transformation * transformed_vertices[index]);
        }

        // Se borra el framebúffer y se dibujan los triángulos:

        rasterizer.clear();

        for (int* indices = original_indices.data(), *end = indices + original_indices.size(); indices < end; indices += 3)
        {
            if (is_frontface(transformed_vertices.data(), indices))
            {
                // Se establece el color del polígono a partir del color de su primer vértice:

                rasterizer.set_color(original_colors[*indices]);

                // Se rellena el polígono:

                rasterizer.fill_convex_polygon_z_buffer(display_vertices.data(), indices, indices + 3);
            }
        }

        // Se copia el framebúffer oculto en el framebúffer de la ventana:

        color_buffer.blit_to_window();
    }

    bool Mesh::is_frontface(const Vertex* const projected_vertices, const int* const indices)
    {
        const Vertex& v0 = projected_vertices[indices[0]];
        const Vertex& v1 = projected_vertices[indices[1]];
        const Vertex& v2 = projected_vertices[indices[2]];

        // Se asumen coordenadas proyectadas y polígonos definidos en sentido horario.
        // Se comprueba a qué lado de la línea que pasa por v0 y v1 queda el punto v2:

        return ((v1[0] - v0[0]) * (v2[1] - v0[1]) - (v2[0] - v0[0]) * (v1[1] - v0[1]) < 0.f);
    }
}
