#ifndef EBO_CLASS_H
#define EBO_CLASS_h

// the includes for the EBO.
#include<glad/glad.h>
#include<vector>

// setting up the EBO class
class EBO {
public:
	GLuint ID;
	EBO(std::vector<GLuint>& indices);

	void Bind();
	void Unbind();
	void Delete();
};


#endif // !EBO_CLASS_H#pragma once
