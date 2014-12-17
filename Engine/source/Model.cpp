
#include <Engine/Model.h>
#include <Engine/MaterialFile.h>
#include <Engine/Material.h>
#include <Engine/Mesh.h>
#include <Engine/Math.h>
#include <Engine/AssetManager.h>
#include <Engine/Texture.h>
#include <fstream>
#include <sstream>
#include <cstdint>

#pragma warning(disable:4996)	// Disable warnings for 'sscanf'

Model::~Model()
{
	clear();
}

void Model::draw(Shader& shader, AssetManager& assets)
{
	m_VertexBuffer.bind();
	m_IndexBuffer.bind();

	std::vector<Vertex> vertexData;
	Vertex vertex;
	vertex.Normal = { 0, 0, 0 };
	vertex.Color = { 1, 1, 1, 1 };

	for (auto& mesh : m_Meshes)
	{
		for (size_t i = 0; i < mesh->indices.size(); i++)
		{
			vertex.Position = mesh->vertices[i];
			//vertex.Normal = mesh->normals[i];
			vertex.UV.x = mesh->texCoords[i].x;
			vertex.UV.y = mesh->texCoords[i].y;
			vertexData.emplace_back(vertex);
		}

		m_VertexBuffer.setData(vertexData);
		m_IndexBuffer.setData(mesh->indices);
		shader.bind();

		Texture* texture = assets.load<Texture>(mesh->material->map_kd);

		if (texture)
		{
			texture->bind();
			gl::GetAllErrors();
			gl::DrawElements(gl::TRIANGLES, mesh->indices.size(), gl::UNSIGNED_INT, 0);
			texture->unbind();
		}
		else
		{
			gl::DrawElements(gl::TRIANGLES, mesh->indices.size(), gl::UNSIGNED_INT, 0);
		}
	}

	m_VertexBuffer.unbind();
	m_IndexBuffer.unbind();
}

bool Model::fromFile(const std::string& filepath)
{
	const size_t lastSlash = math::min(filepath.find_last_of('/'), filepath.find_last_of('\\'));
	const std::string directory = (lastSlash != std::string::npos ? filepath.substr(0, lastSlash + 1) : "");

	std::ifstream in(filepath);

	if (!in)
		return false;

	clear();

	std::stringstream ss;
	std::string line, prefix;

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec3> texCoords;

	Mesh* currentMesh = nullptr;

	while (!in.eof())
	{
		std::getline(in, line);

		if (in.bad())
			return false;

		ss.clear();
		ss.str(line);
		ss >> prefix;

		if (prefix == "mtllib")
		{
			std::string filename;
			ss >> filename;

			MaterialFile* newMaterialFile = new MaterialFile;

			if (newMaterialFile->loadFromFile(directory + filename))
			{
				m_MaterialFiles.push_back(newMaterialFile);
			}
			else
			{
				delete newMaterialFile;
			}
		}

		if (prefix == "v")
		{
			vertices.emplace_back();
			ss >> vertices.back().x >> std::ws;
			ss >> vertices.back().y >> std::ws;
			ss >> vertices.back().z >> std::ws;
			continue;
		}

		if (prefix == "vn")
		{
			normals.emplace_back();
			ss >> normals.back().x >> std::ws;
			ss >> normals.back().y >> std::ws;
			ss >> normals.back().z >> std::ws;
			continue;
		}

		if (prefix == "vt")
		{
			texCoords.emplace_back();
			ss >> texCoords.back().x >> std::ws;
			ss >> texCoords.back().y >> std::ws;
			ss >> texCoords.back().z >> std::ws;
			continue;
		}

		if (prefix == "g")
		{
			currentMesh = new Mesh;
			ss >> currentMesh->name >> std::ws;
			m_Meshes.push_back(currentMesh);
			continue;
		}

		if (!currentMesh)
			continue;

		if (prefix == "usemtl")
		{
			std::string name;
			ss >> name >> std::ws;
			currentMesh->material = findMaterial(name);
			continue;
		}

		if (prefix == "f")
		{
			std::string indexString;
			uint32_t vIndices = 0;
			uint32_t nIndices = 0;
			uint32_t tIndices = 0;

			for (size_t i = 0; i < 3; i++)
			{
				ss >> indexString >> std::ws;
				sscanf(indexString.data(), "%d/%d/%d", &vIndices, &tIndices, &nIndices);

				currentMesh->vertices.emplace_back();
				currentMesh->vertices.back() = vertices[vIndices - 1];

				currentMesh->normals.emplace_back();
				currentMesh->normals.back() = normals[nIndices - 1];

				currentMesh->texCoords.emplace_back();
				currentMesh->texCoords.back() = texCoords[tIndices - 1];

				currentMesh->indices.emplace_back();
				currentMesh->indices.back() = vIndices - 1;
			}

			continue;
		}
	}

	for (auto& mesh : m_Meshes)
	{
		mesh->vertices.shrink_to_fit();
		mesh->normals.shrink_to_fit();
		mesh->texCoords.shrink_to_fit();
		mesh->indices.shrink_to_fit();
	}

	return true;
}

Material* Model::findMaterial(const std::string& name) const
{
	Material* material = nullptr;

	for (auto& materialFile : m_MaterialFiles)
	{
		material = materialFile->findMaterial(name);
	
		if (material)
			return material;
	}

	return nullptr;
}

void Model::clear()
{
	for (auto& e : m_Meshes)
		delete e;
	m_Meshes.clear();

	for (auto& e : m_MaterialFiles)
		delete e;
	m_MaterialFiles.clear();
}
