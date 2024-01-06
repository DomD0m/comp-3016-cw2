#include"shaderClass.h"

//allows to read a text file and get its contents.
std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

// building the shader program from the vert file and frag file.
Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	//reading both the shader files.
	std::string vertCode = get_file_contents(vertexFile);
	std::string fragCode = get_file_contents(fragmentFile);

	//converting the sources into strings.
	const char* vertSource = vertCode.c_str();
	const char* fragSource = fragCode.c_str();

	//creating the vert shader and compiling it.
	GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
	
	glShaderSource(vertShader, 1, &vertSource, NULL);
	
	glCompileShader(vertShader);
	compileErrors(vertShader, "VERTEX");

	//creating the frag shader and compiling it.
	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	
	glShaderSource(fragShader, 1, &fragSource, NULL);
	
	glCompileShader(fragShader);
	compileErrors(fragShader, "FRAGMENT");


	//puts both the vert shader and frag shader together to make the shader prog.
	ID = glCreateProgram();
	
	glAttachShader(ID, vertShader);
	glAttachShader(ID, fragShader);
	
	glLinkProgram(ID);
	compileErrors(ID, "PROGRAM");

	//removes the uneeded shaders at the end.
	glDeleteShader(vertShader);
	glDeleteShader(fragShader);

}

//activates the shaders for the program.
void Shader::Activate()
{
	glUseProgram(ID);
}

//Removes the shader program so no issues arise later
void Shader::Remove()
{
	glDeleteProgram(ID);
}

//error handling for the shader program and if anything was properly done this will catch the error.
void Shader::compileErrors(unsigned int shader, const char* type)
{
	GLint hasCompiled;
	char infolog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infolog);
			std::cout << "SHader_compilation_ERROR for:" << type << "\n" << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infolog);
			std::cout << "SHader_compilation_ERROR for:" << type << "\n" << std::endl;
		}
	}
}
