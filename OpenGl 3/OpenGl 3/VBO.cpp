#include"VBO.h"


// create a VBO object correctly
VBO::VBO(std::vector<Vertex>& vertices)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
}


//bind the VBO to the correct system
void VBO::Bind() {
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}
//unbinding it from the system
void VBO::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
// deleing the vbo from the system.
void VBO::Delete()
{
	glDeleteBuffers(1, &ID);
}