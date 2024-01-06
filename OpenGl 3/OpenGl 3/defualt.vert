#version 330 core

//finding out postions
layout (location = 0) in vec3 aPos;
//normalising
layout (location = 1) in vec3 aNormal;
//the colours
layout (location = 2) in vec3 aColor;
//the coordinates
layout (location = 3) in vec2 aTex;


//sends to frag shader position
out vec3 crntPos;
// sends to frag shader the normal.
out vec3 Normal;
// sends to frag shader the colour
out vec3 color;
//sends to frag shader the texture coordinates
out vec2 texCoord;



//the uniforms for the vert.
uniform mat4 camMatrix;


// the unifrom for the model matrices.
uniform mat4 model;
uniform mat4 translation;
uniform mat4 rotation;
uniform mat4 scale;


void main()
{
	// calc the position
	crntPos = vec3(model * translation * -rotation * scale * vec4(aPos, 1.0f));
	// find the normal and assign it 
	Normal = aNormal;
	// assignes the colours
	color = aColor;
	// assigns the texture coords to properly wrap the model.
	texCoord = mat2(0.0, -1.0, 1.0, 0.0) * aTex;
	
	//outputs all of it.
	gl_Position = camMatrix * vec4(crntPos, 1.0);
}