#ifndef MESH_CLASS_H
#define MESH_CLASS_H

// include for the Mesh class
#include<string>

#include"VAO.h"
#include"EBO.h"
#include"Camera.h"
#include"Texture.h"

class Mesh
{
public:
	//Variables for the Mesh class
	std::vector <Vertex> vert;
	std::vector <GLuint> ind;
	std::vector <Texture> text;
	glm::vec3 trans = glm::vec3(0.0f, 0.0f, 0.0f);

	//setting up VAO
	VAO VAO;

	// Makes the Mesh
	Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, std::vector <Texture>& textures);

	// Allows To draw the Mesh on to the Scene, using the GLM matrices to make up the GLTF file.
	void Draw
		//void TransDraw scrapped ideas for how to draw the models as was thinking of a way to use non GLTF file changing and instead using OPENGL to change the matrices in the files.
		//void RotatDraw
		//void ScaDraw
	(
		//grabbing the shaders and camera and the positions, rotation, scale of the model to make the mesh with.
		Shader& shader,
		Camera& camera,
		glm::mat4 matrix = glm::mat4(1.0f),
		glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
		glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f)
	);

};
#endif
