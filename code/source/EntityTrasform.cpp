/*
* @Author: Daniel Guerra Gallardo
* @Date: 07/2021
* @Description: 3D mesh loader exercise
* daniel.guerra.gallardo99@gmail.com
*/

#include "EntityTrasform.hpp"


namespace MeshLoader
{
	EntityTrasform::EntityTrasform(string id) : identity(1), id(id)
		
	{
		scaling = scale(identity, 1);
		rotation_y = rotate_around_y(identity, 0);
		translation = translate(identity, Vector3f{ 0.f, 0.f, 0.f });
	}

	void EntityTrasform::traslate_entity(float x, float y, float z)
	{
		translation = translate(identity, Vector3f{ x, y, z });
	}

	void EntityTrasform::rotate_entity_x(float angle)
	{
		rotation_x = rotate_around_x(identity, angle);
	}

	void EntityTrasform::rotate_entity_y(float angle)
	{
		rotation_y = rotate_around_y(identity, angle);
	}

	void EntityTrasform::rotate_entity_z(float angle)
	{
		rotation_z = rotate_around_z(identity, angle);
	}

	void EntityTrasform::scale_entity(float scale_factor)
	{
		scaling = scale(identity, scale_factor);
	}


	Matrix44 EntityTrasform::update_trasform(Matrix44 projection)
	{
		Matrix44 transformation(1);
		

		// Grafo de escena (Parent -> Child)
		if (parent)
		{
			transformation = parent->update_trasform(projection) * projection * translation * rotation_y * scaling;
		}
		else
		{
			transformation = projection * translation * rotation_y * scaling;
		}

		return transformation;
	}

}


