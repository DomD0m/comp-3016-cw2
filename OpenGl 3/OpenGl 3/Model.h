#ifndef MODEL_CLASS_H
#define MODEL_CLASS_H

// includes for the model class.
#include<json/json.h>
#include"Mesh.h"

using json = nlohmann::json;


class Model
{
public:
	// loading the model file
	Model(const char* file);

	void Draw(Shader& shader, Camera& camera);

private:
	//Variables for the Model.
	const char* file;
	std::vector<unsigned char> data;
	json JSON;

	// All the meshes and transformations
	std::vector<Mesh> meshes;
	std::vector<glm::vec3> translationsMeshes;
	std::vector<glm::quat> rotationsMeshes;
	std::vector<glm::vec3> scalesMeshes;
	std::vector<glm::mat4> matricesMeshes;

	// Prevents textures from being loaded twice
	std::vector<std::string> LTN;
	std::vector<Texture> LT;

	// Loads a single mesh by its index
	void loadMesh(unsigned int indMesh);

	// Traverses a node recursively, so it essentially traverses all connected nodes
	void traverseNode(unsigned int nextNode, glm::mat4 matrix = glm::mat4(1.0f));

	// Gets the binary data from a file
	std::vector<unsigned char> getData();
	// Interprets the binary data into floats, indices, and textures
	std::vector<float> getFloats(json accessor);
	std::vector<GLuint> getIndices(json accessor);
	std::vector<Texture> getTextures();

	// Assembles all the floats into vertices
	std::vector<Vertex> assembleVertices
	(
		std::vector<glm::vec3> pos,
		std::vector<glm::vec3> nor,
		std::vector<glm::vec2> tex
	);

	// Helps with the assembly from above by grouping floats
	std::vector<glm::vec2> groupFloatsVec2(std::vector<float> fVec);
	std::vector<glm::vec3> groupFloatsVec3(std::vector<float> fVec);
	std::vector<glm::vec4> groupFloatsVec4(std::vector<float> fVec);
};
#endif