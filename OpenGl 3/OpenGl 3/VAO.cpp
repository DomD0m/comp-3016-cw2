#include"VAO.h"

// generate the VAO ID
VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}

// links the VAO attributes
void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
	VBO.Bind();
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	VBO.Unbind();
}

// binding the Vao
void VAO::Bind()
{
	glBindVertexArray(ID);
}

//unbinding so its not reuse accidentally.
void VAO::Unbind()
{
	glBindVertexArray(0);
}

//removing it from the system.
void VAO::Delete()
{
	glDeleteVertexArrays(1, &ID);
}