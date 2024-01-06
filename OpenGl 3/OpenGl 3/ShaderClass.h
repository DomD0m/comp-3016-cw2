#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H


// the includes of the Shader Class.
#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

std::string get_file_contents(const char* filename);

class Shader
{
public:
	// referencing the ID of the shader program so it can be used.
	GLuint ID;
	//making the shader program by putting together both the vert and frag files.
	Shader(const char* vertFile, const char* fragFile);

	// activates the shader program.
	void Activate();
	// Removes the shader from the system
	void Remove();
private:
	void compileErrors(unsigned int shader, const char* type);
};
#endif
