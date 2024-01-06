#ifndef VBO_CLASS_H
#define VBO_CLASS_H

// The includes for the VBO class.
#include<glm/glm.hpp>
#include<glad/glad.h>
#include<vector>

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 color;
	glm::vec2 texUV;
};

class VBO
{
public:
	// making an ID for the class
	GLuint ID;
	// makes a VBO object.
	VBO(std::vector<Vertex>& vertices);

	//General Controls.
	void Bind();
	
	void Unbind();
	
	void Delete();
};

#endif