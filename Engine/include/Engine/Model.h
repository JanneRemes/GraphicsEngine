
#ifndef MODEL_H
#define MODEL_H

#include <Engine/Asset.h>
#include <Engine/Shader.h>
#include <Engine/VertexBuffer.h>
#include <Engine/IndexBuffer.h>
#include <string>
#include <vector>

class Mesh;
class Material;
class MaterialFile;

class Model : public Asset
{
public:
	~Model();
	void draw(Shader& shader, AssetManager& assets);
	bool fromFile(const std::string& filepath);
private:
	Material* findMaterial(const std::string& name) const;
	void clear();

	VertexBuffer m_VertexBuffer;
	IndexBuffer m_IndexBuffer;
	std::vector<Mesh*> m_Meshes;
	std::vector<MaterialFile*> m_MaterialFiles;
};

#endif
