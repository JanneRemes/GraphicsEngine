
#ifndef MODEL_H
#define MODEL_H

#include <wgl_core_2_1/wgl.h>
#include <glm/glm.hpp>
#include <fstream>
#include <vector>
#include <Engine/Mesh.h>
#include <Engine/Material.h>

class Model
{
public:
	bool fromFile(const std::string& filepath);

private:
	std::vector<Mesh> m_Meshes;
};

#endif // Include guard
