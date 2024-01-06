//only including the model.h file as it includes everything else and all what we need the main file to do is draw the models on to the scene.
#include"Model.h"

//defining the width and height of the window.
const unsigned int w = 800;
const unsigned int h = 800;

int main() {
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	//making the window for OpenGL and naming the Scene
	GLFWwindow* window = glfwCreateWindow(w, h, "forest Scene", NULL, NULL);
	if (window == NULL) {
		std::cout << "failed to create GLFW window " << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	gladLoadGL();

	glViewport(0,0,w,h);

	//creating the shader.
	Shader graphicsprog("defualt.vert", "default.frag");

	//creating the lightmodel with the positon and colour.
	glm::vec4 lightColour = glm::vec4(1.0f, 1.0f, 0.5f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	//creating the shaderprog and the uniforms for the light system.
	graphicsprog.Activate();
	glUniform4f(glGetUniformLocation(graphicsprog.ID, "lightColor"), lightColour.x, lightColour.y, lightColour.z, lightColour.w);
	glUniform3f(glGetUniformLocation(graphicsprog.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

	//model file paths.
	Model tree("models/tree4/Tree4.gltf");
	Model floor("models/Grass/grass.gltf");
	Model fir("models/firtree/firtree.gltf");
	Model fir2("models/firtree2/firtree.gltf");
	Model fir3("models/firtree3/firtree.gltf");
	Model fir4("models/firtree4/firtree.gltf");
	Model fir5("models/firtree5/firtree.gltf");
	Model fir6("models/firtree6/firtree.gltf");
	Model house("models/house/house.gltf");
	

	glEnable(GL_DEPTH_TEST);

	Camera camera(w, h, glm::vec3(0.0f, 0.0f, 2.0f));

	while (!glfwWindowShouldClose(window))
	{

		// making the colour of the background
		glClearColor(0.17f, 0.33f, 0.17f, 1.0f);
		// The back buffer and depth buffer for the scene
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// allows for the camera inputs within the window
		camera.Inputs(window);
		// puts the cameramat to vertmat.
		camera.updateMatrix(45.0f, 0.1f, 100.0f);


		//will draw all the models.
		tree.Draw(graphicsprog, camera);
		floor.Draw(graphicsprog, camera);
		fir2.Draw(graphicsprog, camera);
		fir.Draw(graphicsprog, camera);
		fir3.Draw(graphicsprog, camera);
		fir4.Draw(graphicsprog, camera);
		fir5.Draw(graphicsprog, camera);
		fir6.Draw(graphicsprog, camera);
		house.Draw(graphicsprog, camera);
		
		
		
		


		//swap the back and front buffer.
		glfwSwapBuffers(window);
		//put all the events.
		glfwPollEvents();

	}

	//removing unessecary things and killing the window.
	graphicsprog.Remove();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}