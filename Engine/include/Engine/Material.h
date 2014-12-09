
#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/glm.hpp>
#include <string>

struct Material final
{
public:
	Material();
	bool fromFile(const std::string& filepath);

	union
	{
		// .mtl file equivalents
		struct
		{
			std::string newmtl;
			std::string map_Kd;

			float Ns;     // specular exponent (i.e. the shininess).
			float Ni;     // index of reflection

			float d;      // dissolve
			float Tr;     // transparency
			glm::vec3 Tf; // transmission filter

			int	illum;	  // illumination model
			glm::vec3 Ka; // ambient color
			glm::vec3 Kd; // diffuse color
			glm::vec3 Ks; // specular color
			glm::vec3 Ke; // emissive color
		};

		// Verbose aliases
		struct
		{
			std::string Name;
			std::string DiffureTexturePath;

			float SpecularExponent;       // specular exponent (i.e. the shininess).
			float IndexOfReflection;      // index of reflection

			float Dissolve;				  // dissolve
			float Transparency;			  // transparency
			glm::vec3 TransmissionFilter; // transmission filter

			int	IlluminationModel;	      // illumination model
			glm::vec3 AmbientColor;       // ambient color
			glm::vec3 DiffuseColor;       // diffuse color
			glm::vec3 SpecularColor;      // specular color
			glm::vec3 EmissiveColor;      // emissive color
		};
	};
};

#endif // Include guard
