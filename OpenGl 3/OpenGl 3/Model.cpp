#include"Model.h"

Model::Model(const char* modelfile)
{
	// create a Json Object to use for the Model.
	std::string text = get_file_contents(modelfile);
	JSON = json::parse(text);

	// binary data 
	Model::file = modelfile;
	data = getData();

	//the Nodes
	traverseNode(0);
}

void Model::Draw(Shader& shader, Camera& camera)
{
	//Find the meshes and draw each one.
	for (unsigned int i = 0; i < meshes.size(); i++)
	{
		meshes[i].Mesh::Draw(shader, camera, matricesMeshes[i]);
	}
}

void Model::loadMesh(unsigned int indMesh)
{
	// Getting the accessor indices for the mesh.
	unsigned int posAccInd = JSON["meshes"][indMesh]["primitives"][0]["attributes"]["POSITION"];
	unsigned int normalAccInd = JSON["meshes"][indMesh]["primitives"][0]["attributes"]["NORMAL"];
	unsigned int texAccInd = JSON["meshes"][indMesh]["primitives"][0]["attributes"]["TEXCOORD_0"];
	unsigned int indAccInd = JSON["meshes"][indMesh]["primitives"][0]["indices"];

	// using the indices accessor to get the vertices for the Model.
	std::vector<float> posVec = getFloats(JSON["accessors"][posAccInd]);
	std::vector<glm::vec3> pos = groupFloatsVec3(posVec);
	std::vector<float> normalVec = getFloats(JSON["accessors"][normalAccInd]);
	std::vector<glm::vec3> norm = groupFloatsVec3(normalVec);
	std::vector<float> texVec = getFloats(JSON["accessors"][texAccInd]);
	std::vector<glm::vec2> tex = groupFloatsVec2(texVec);

	// Combining both vertices and indices and the textures to put it all together to get mesh.
	std::vector<Vertex> vertices = assembleVertices(pos, norm, tex);
	std::vector<GLuint> indices = getIndices(JSON["accessors"][indAccInd]);
	std::vector<Texture> textures = getTextures();

	// Putting all the pieces together to get the mesh and wrapping the texture correctly.
	meshes.push_back(Mesh(vertices, indices, textures));
}


//The Node system the way to read the GLTF files for the models and see how they work.
void Model::traverseNode(unsigned int nextNode, glm::mat4 matrix)
{
	//first Node.
	json node = JSON["nodes"][nextNode];

	// finding the translation
	glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f);
	if (node.find("translation") != node.end())
	{
		float transValues[3];
		for (unsigned int i = 0; i < node["translation"].size(); i++)
			transValues[i] = (node["translation"][i]);
		translation = glm::make_vec3(transValues);
	}
	// finding the rotation
	glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
	if (node.find("rotation") != node.end())
	{
		float rotValues[4] =
		{
			node["rotation"][3],
			node["rotation"][0],
			node["rotation"][1],
			node["rotation"][2]
		};
		rotation = glm::make_quat(rotValues);
	}
	// finding the scale
	glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
	if (node.find("scale") != node.end())
	{
		float scaleValues[3];
		for (unsigned int i = 0; i < node["scale"].size(); i++)
			scaleValues[i] = (node["scale"][i]);
		scale = glm::make_vec3(scaleValues);
	}
	// finding the matrix
	glm::mat4 matNode = glm::mat4(1.0f);
	if (node.find("matrix") != node.end())
	{
		float matValues[16];
		for (unsigned int i = 0; i < node["matrix"].size(); i++)
			matValues[i] = (node["matrix"][i]);
		matNode = glm::make_mat4(matValues);
	}

	// getting the variables for the matrices.
	glm::mat4 trans = glm::mat4(1.0f);
	glm::mat4 rot = glm::mat4(1.0f);
	glm::mat4 sca = glm::mat4(1.0f);


	trans = glm::translate(trans, translation);
	rot = glm::mat4_cast(rotation);
	sca = glm::scale(sca, scale);

	// putting all the matrices together.
	glm::mat4 matNextNode = matrix * matNode * trans * rot * sca;

	//Finding if a node has a mesh and if yes loading it.
	if (node.find("mesh") != node.end())
	{
		translationsMeshes.push_back(translation);
		rotationsMeshes.push_back(rotation);
		scalesMeshes.push_back(scale);
		matricesMeshes.push_back(matNextNode);

		loadMesh(node["mesh"]);
	}

	//Finding Child Nodes.
	if (node.find("children") != node.end())
	{
		for (unsigned int i = 0; i < node["children"].size(); i++)
			traverseNode(node["children"][i], matNextNode);
	}
}

std::vector<unsigned char> Model::getData()
{
	// Create a place to store the raw text, and get the uri of the .bin file
	std::string bytesText;
	std::string uri = JSON["buffers"][0]["uri"];

	// Store raw text data into bytesText
	std::string fileStr = std::string(file);
	std::string fileDirectory = fileStr.substr(0, fileStr.find_last_of('/') + 1);
	bytesText = get_file_contents((fileDirectory + uri).c_str());

	// Transform the raw text data into bytes and put them in a vector
	std::vector<unsigned char> data(bytesText.begin(), bytesText.end());
	return data;
}

//setting up the floats of the Model.
std::vector<float> Model::getFloats(json accessor)
{
	std::vector<float> fVec;

	// Getting the properties from the accessor using JSON
	unsigned int buffViewIndF = accessor.value("bufferView", 1);
	unsigned int countF = accessor["count"];
	unsigned int accByteOffsetF = accessor.value("byteOffset", 0);
	std::string typeF = accessor["type"];

	// Getting the properties from the bufferView using JSON.
	json bufferViewF = JSON["bufferViews"][buffViewIndF];
	unsigned int byteOffsetF = bufferViewF["byteOffset"];

	// Finding what Type and from that giving it the correct NPV.
	unsigned int numPerVertices;
	if (typeF == "SCALAR") numPerVertices = 1;
	else if (typeF == "VEC2") numPerVertices = 2;
	else if (typeF == "VEC3") numPerVertices = 3;
	else if (typeF == "VEC4") numPerVertices = 4;
	else throw std::invalid_argument("Type is invalid (not SCALAR, VEC2, VEC3, or VEC4)");

	// Finding all the Bytes within the Data.
	unsigned int BOD = byteOffsetF + accByteOffsetF;
	unsigned int LOD = countF * 4 * numPerVertices;
	for (unsigned int i = BOD; i < BOD + LOD; i)
	{
		unsigned char bytes[] = { data[i++], data[i++], data[i++], data[i++] };
		float value;
		std::memcpy(&value, bytes, sizeof(float));
		fVec.push_back(value);
	}

	return fVec;
}


// setting up the indices of the model.
std::vector<GLuint> Model::getIndices(json accessor)
{
	std::vector<GLuint> indices;

	// Getting the properties from the accessor using JSON
	unsigned int buffViewInd = accessor.value("bufferView", 0);
	unsigned int countI = accessor["count"];
	unsigned int accByteOffsetI = accessor.value("byteOffset", 0);
	unsigned int componentTypeI = accessor["componentType"];

	// Getting the properties from the bufferView using JSON.
	json bufferViewI = JSON["bufferViews"][buffViewInd];
	unsigned int byteOffsetI = bufferViewI["byteOffset"];

	// Get indices of each of their respective types for the models being an int, unsigned short or just a short.
	unsigned int BOD = byteOffsetI + accByteOffsetI;
	if (componentTypeI == 5125)
	{
		for (unsigned int i = BOD; i < byteOffsetI + accByteOffsetI + countI * 4; i)
		{
			unsigned char bytes[] = { data[i++], data[i++], data[i++], data[i++] };
			unsigned int value;
			std::memcpy(&value, bytes, sizeof(unsigned int));
			indices.push_back((GLuint)value);
		}
	}
	else if (componentTypeI == 5123)
	{
		for (unsigned int i = BOD; i < byteOffsetI + accByteOffsetI + countI * 2; i)
		{
			unsigned char bytes[] = { data[i++], data[i++] };
			unsigned short value;
			std::memcpy(&value, bytes, sizeof(unsigned short));
			indices.push_back((GLuint)value);
		}
	}
	else if (componentTypeI == 5122)
	{
		for (unsigned int i = BOD; i < byteOffsetI + accByteOffsetI + countI * 2; i)
		{
			unsigned char bytes[] = { data[i++], data[i++] };
			short value;
			std::memcpy(&value, bytes, sizeof(short));
			indices.push_back((GLuint)value);
		}
	}

	return indices;
}

std::vector<Texture> Model::getTextures()
{
	std::vector<Texture> textures;

	std::string FS = std::string(file);
	std::string FD = FS.substr(0, FS.find_last_of('/') + 1);

	// Fnding all the Textures.
	for (unsigned int i = 0; i < JSON["images"].size(); i++)
	{
		//Finds the URI of the gltf to make sure its the right textures.
		std::string texPath = JSON["images"][i]["uri"];

		// Check if the texture has already been loaded
		bool TS = false;
		for (unsigned int j = 0; j < LTN.size(); j++)
		{
			if (LTN[j] == texPath)
			{
				textures.push_back(LT[j]);
				TS = true;
				break;
			}
		}

		// Skipping loading the texture twice with this.
		if (!TS)
		{
			// Loading the basic colour of a model, making sure to rename any basic colour to BaseColor, the american spelling because a lot of models seems to have this set up already.
			if (texPath.find("baseColor") != std::string::npos)
			{
				Texture base = Texture((FD + texPath).c_str(), "diffuse", LT.size());
				textures.push_back(base);
				LT.push_back(base);
				LTN.push_back(texPath);
			}
			//Loading Additional Textures of the Model to if, it has specular light textures.
			else if (texPath.find("SpecColor") != std::string::npos)
			{
				Texture spec = Texture((FD + texPath).c_str(), "specular", LT.size());
				textures.push_back(spec);
				LT.push_back(spec);
				LTN.push_back(texPath);
			}
		}
	}

	return textures;
}
// putting all the vertices together.
std::vector<Vertex> Model::assembleVertices
(
	std::vector<glm::vec3> pos,
	std::vector<glm::vec3> norm,
	std::vector<glm::vec2> tex
)
{
	std::vector<Vertex> vertices;
	for (int i = 0; i < pos.size(); i++)
	{
		vertices.push_back
		(
			Vertex
			{
				pos[i],
				norm[i],
				glm::vec3(1.0f, 1.0f, 1.0f),
				tex[i]
			}
		);
	}
	return vertices;
}

std::vector<glm::vec2> Model::groupFloatsVec2(std::vector<float> fVec)
{
	std::vector<glm::vec2> vectors;
	for (int i = 0; i < fVec.size(); i)
	{
		vectors.push_back(glm::vec2(fVec[i++], fVec[i++]));
	}
	return vectors;
}
std::vector<glm::vec3> Model::groupFloatsVec3(std::vector<float> fVec)
{
	std::vector<glm::vec3> vectors;
	for (int i = 0; i < fVec.size(); i)
	{
		vectors.push_back(glm::vec3(fVec[i++], fVec[i++], fVec[i++]));
	}
	return vectors;
}
std::vector<glm::vec4> Model::groupFloatsVec4(std::vector<float> fVec)
{
	std::vector<glm::vec4> vectors;
	for (int i = 0; i < fVec.size(); i)
	{
		vectors.push_back(glm::vec4(fVec[i++], fVec[i++], fVec[i++], fVec[i++]));
	}
	return vectors;
}