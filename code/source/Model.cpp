#include "Model.hpp"

using namespace Assimp;

namespace MeshLoaderExercise
{
	void Model::draw_model()
	{
		for (unsigned int i = 0; i < meshes.size(); i++)
			meshes[i].update_mesh();
	}
	void Model::load_model(string path)
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			//printf("Error parsing '%s': '%s'\n", path.c_str(), Importer.GetErrorString());
			return;
		}

		directory = path.substr(0, path.find_last_of('/'));

		process_node(scene->mRootNode, scene);
	}
	void Model::process_node(aiNode* node, const aiScene* scene)
	{
		// process all the node's meshes (if any)
		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			meshes.push_back(process_mesh(mesh, scene));
		}
		// then do the same for each of its children
		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			process_node(node->mChildren[i], scene);
		}
	}
	Mesh Model::process_mesh(aiMesh* mesh, const aiScene* scene)
	{

		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			// process vertex positions, normals and texture coordinates
			meshes[i].init_mesh(mesh);
		}

		return Mesh(*this);
	}
}
