#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

//Camera includes 

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include"ShaderClass.h"

class Camera
{
public:
	// variables for the class.
	glm::vec3 Position;
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 cameraMatrix = glm::mat4(1.0f);


	// a boolean to allow to track the first time the player has clicked on the scene
	bool firstClick = true;

	int height;
	int width;

	// the speed and sensitivity of the camera can be modified with this.
	float speed = 0.1f;
	float sensitivity = 100.0f;

	//The systems that the class can run

	Camera(int width, int height, glm::vec3 position);

	void updateMatrix(float FOVdeg, float nearPlane, float farplane);

	void Matrix(Shader& shader, const char* uniform);
	void Inputs(GLFWwindow* window);
};
#endif // !CAMERA_CLASS_H

