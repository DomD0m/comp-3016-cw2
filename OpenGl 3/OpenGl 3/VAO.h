#ifndef VAO_CLASS_H
#define VAO_CLASS_H

// includes for the VAO.

#include<glad/glad.h>
#include"VBO.h"

class VAO
{
public:
	// ID made.
	GLuint ID;
	// constructor for the VAO.
	VAO();

	// links the attributes to the VAO, such as colours and other parts.
	void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
	//binds the VAO to the correct system
	void Bind();
	// Unbinds it from the respective system
	void Unbind();
	//removes the VAO so it doesn't get used by something its not post to.
	void Delete();
};

#endif

