#include "MC3dExplorerLib_Drawable.h"

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <stl_reader.h>

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Mathematics/Triangle.h>
#include <Mathematics/Vector3.h>


float MC3dExplorerLib::vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};


std::array<glm::vec3, 8> MC3dExplorerLib::boundingBox = {
	glm::vec3(-0.5f, -0.5f, -0.5f),
	glm::vec3(-0.5f, -0.5f,  0.5f),
	glm::vec3(-0.5f,  0.5f, -0.5f),
	glm::vec3(-0.5f,  0.5f,  0.5f),
	glm::vec3(0.5f, -0.5f, -0.5f),
	glm::vec3(0.5f, -0.5f,  0.5f),
	glm::vec3(0.5f,  0.5f, -0.5f),
	glm::vec3(0.5f,  0.5f,  0.5f)
};


std::vector<glm::vec3> MC3dExplorerLib::cubePositions = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
};


GLuint MC3dExplorerLib::vao;
unsigned int MC3dExplorerLib::texture0;
unsigned int MC3dExplorerLib::texture1;


auto MC3dExplorerLib::InitDrawables() -> void
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 180 * sizeof(float), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	// START TEXTURE STUFF

	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("..\\textures\\container.jpg", &width, &height, &nrChannels, 0);

	glGenTextures(1, &texture0);
	glBindTexture(GL_TEXTURE_2D, texture0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cerr << "Error: failed to load texture\n";
		return;// static_cast<int>(MC3dExplorerLib::ErrorCode::ERROR_TEXTURE_FAILED_TO_LOAD);
	}

	stbi_image_free(data);

	data = stbi_load("..\\textures\\juju.png", &width, &height, &nrChannels, 0);
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cerr << "Error: failed to load texture\n";
		return;// static_cast<int>(MC3dExplorerLib::ErrorCode::ERROR_TEXTURE_FAILED_TO_LOAD);
	}

	stbi_image_free(data);
}


//MC3dExplorerLib::WoodenBox::WoodenBox(const glm::mat4& modelMatrix)
//	: Cube(Shader(R"(..\shaders\vsContainer.glsl)", R"(..\shaders\fsContainer.glsl)"), modelMatrix, DrawableType::WoodenBox)
//{
//	// START TEXTURE STUFF
//	int width, height, nrChannels;
//	stbi_set_flip_vertically_on_load(true);
//	unsigned char* data = stbi_load("..\\textures\\container.jpg", &width, &height, &nrChannels, 0);
//
//	glGenTextures(1, &texture0);
//	glBindTexture(GL_TEXTURE_2D, texture0);
//
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//	if (data)
//	{
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//		glGenerateMipmap(GL_TEXTURE_2D);
//	}
//	else
//	{
//		std::cerr << "Error: failed to load texture\n";
//		return;// static_cast<int>(MC3dExplorerLib::ErrorCode::ERROR_TEXTURE_FAILED_TO_LOAD);
//	}
//
//	stbi_image_free(data);
//
//	data = stbi_load("..\\textures\\juju.png", &width, &height, &nrChannels, 0);
//	glGenTextures(1, &texture1);
//	glBindTexture(GL_TEXTURE_2D, texture1);
//
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//	if (data)
//	{
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//		glGenerateMipmap(GL_TEXTURE_2D);
//	}
//	else
//	{
//		std::cerr << "Error: failed to load texture\n";
//		return;// static_cast<int>(MC3dExplorerLib::ErrorCode::ERROR_TEXTURE_FAILED_TO_LOAD);
//	}
//
//	stbi_image_free(data);
//}

//auto MC3dExplorerLib::WoodenBox::Draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) const -> void
//{
//	glUseProgram(m_ShaderId);
//
//	glBindVertexArray(m_Vao);
//
//	glActiveTexture(GL_TEXTURE0);
//	glBindTexture(GL_TEXTURE_2D, MC3dExplorerLib::texture0);
//
//	glActiveTexture(GL_TEXTURE1);
//	glBindTexture(GL_TEXTURE_2D, MC3dExplorerLib::texture1);
//
//	glUniform1i(glGetUniformLocation(m_ShaderId, "samplerContainer"), 0);
//	glUniform1i(glGetUniformLocation(m_ShaderId, "samplerAwesomeFace"), 1);
//
//	glUniform1f(glGetUniformLocation(m_ShaderId, "mixPercentage"), 0.f);
//
//	glUniformMatrix4fv(glGetUniformLocation(m_ShaderId, "model"), 1, GL_FALSE, glm::value_ptr(m_ModelMatrix));
//	glUniformMatrix4fv(glGetUniformLocation(m_ShaderId, "view"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
//	glUniformMatrix4fv(glGetUniformLocation(m_ShaderId, "projection"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
//
//	glDrawArrays(GL_TRIANGLES, 0, 36);
//}


MC3dExplorerLib::Cube::Cube(const Shader* const shader, const glm::mat4& modelMatrix, DrawableType type)
	: Drawable(shader, type)
{
	m_ModelMatrix = modelMatrix;

	float vertices[288] = { // 3 vertex, 2 texture coords, 3 normal
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f,  0.0f
	};

	glGenVertexArrays(1, &m_Vao);
	glBindVertexArray(m_Vao);

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 288 * sizeof(float), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(2);

	m_BoundingBox = std::array<glm::vec3, 8>
	{
		glm::vec3(-0.5f, -0.5f, -0.5f),
			glm::vec3(-0.5f, -0.5f, 0.5f),
			glm::vec3(-0.5f, 0.5f, -0.5f),
			glm::vec3(-0.5f, 0.5f, 0.5f),
			glm::vec3(0.5f, -0.5f, -0.5f),
			glm::vec3(0.5f, -0.5f, 0.5f),
			glm::vec3(0.5f, 0.5f, -0.5f),
			glm::vec3(0.5f, 0.5f, 0.5f)
	};
}


auto MC3dExplorerLib::Cube::Draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) const -> void
{
	GLuint programId = m_Shader->GetProgramId();

	glUseProgram(programId);

	glBindVertexArray(m_Vao);

	glUniformMatrix4fv(glGetUniformLocation(programId, "model"), 1, GL_FALSE, glm::value_ptr(m_ModelMatrix));
	glUniformMatrix4fv(glGetUniformLocation(programId, "view"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(glGetUniformLocation(programId, "projection"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	glDrawArrays(GL_TRIANGLES, 0, 36);
}

auto MC3dExplorerLib::Cube::BoundingBox() const->std::array<glm::vec3, 8>
{
	return m_BoundingBox;
}


auto MC3dExplorerLib::Cube::ModelMatrix() const -> glm::mat4
{
	return m_ModelMatrix;
}


MC3dExplorerLib::Drawable::Drawable(const Shader* const shader, DrawableType type)
	:	m_Shader(shader),
		//m_ShaderId(shaderId),
		m_Type(type)
{
}


auto MC3dExplorerLib::Drawable::GetColor() const -> glm::vec3
{
	return m_Color;
}


auto MC3dExplorerLib::Drawable::GetHover() const -> bool
{
	return m_Hover;
}


auto MC3dExplorerLib::Drawable::GetSelected() const -> bool
{
	return m_Selected;
}

auto MC3dExplorerLib::Drawable::GetType() const -> DrawableType
{
	return m_Type;
}


auto MC3dExplorerLib::Drawable::SetColor(const glm::vec3& rgb) -> void
{
	m_Color = rgb;
}


auto MC3dExplorerLib::Drawable::SetHover(bool hover) -> void
{
	m_Hover = hover;
}


auto MC3dExplorerLib::Drawable::SetModel(const glm::mat4& model) -> void
{
	m_ModelMatrix = model;
}


auto MC3dExplorerLib::Drawable::SetSelected(bool selected) -> void
{
	m_Selected = selected;
}


MC3dExplorerLib::Triangles::Triangles(const Shader* shader, const std::string& stl)
	: Drawable(shader, DrawableType::Triangles)
{
	m_StlMesh = stl_reader::StlMesh();
	m_StlMesh.read_file(stl);
	
	struct Vertex
	{
		float x;
		float y;
		float z;
		float tx;
		float ty;
		float nx;
		float ny;
		float nz;
	};

	std::vector<Vertex> vertices;
	int j = 0;
	for (int i = 0; i < m_StlMesh.num_tris(); ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			auto triangleInd = m_StlMesh.tri_corner_ind(i, j);
			Vertex vertex;
			auto vrtCoords = m_StlMesh.vrt_coords(triangleInd);
			vertex.x = vrtCoords[0];
			vertex.y = vrtCoords[1];
			vertex.z = vrtCoords[2];
			
			vertex.tx = 0.0;
			vertex.ty = 0.0;
			
			auto nrmCoords = m_StlMesh.tri_normal(i);
			vertex.nx = nrmCoords[0];
			vertex.ny = nrmCoords[1];
			vertex.nz = nrmCoords[2];

			vertices.push_back(vertex);
		}
	}

	//m_Indices = std::vector<unsigned int>(m_StlMesh.raw_tris(), m_StlMesh.raw_tris() + m_StlMesh.num_vrts());

	std::vector<float> gpuVertices;
	for (int i = 0; i < vertices.size(); ++i)
	{
		gpuVertices.push_back(vertices[i].x);
		gpuVertices.push_back(vertices[i].y);
		gpuVertices.push_back(vertices[i].z);
		gpuVertices.push_back(vertices[i].tx);
		gpuVertices.push_back(vertices[i].ty);
		gpuVertices.push_back(vertices[i].nx);
		gpuVertices.push_back(vertices[i].ny);
		gpuVertices.push_back(vertices[i].nz);
	}
	//for (int i = 0; i < m_StlMesh.num_vrts(); ++i)
	//{
	//	m_StlMesh.
	//}

	////std::vector<float> gpuVertices;
	//m_Indices.clear();
	//for (size_t itri = 0; itri < m_StlMesh.num_tris(); ++itri)
	//{
	////	const float* n = m_StlMesh.tri_normal(itri);

	//	for (size_t icorner = 0; icorner < 3; ++icorner) 
	//	{
	//		m_Indices.push_back(m_StlMesh.tri_corner_ind(itri, icorner));
	////		const float* c = m_StlMesh.vrt_coords(m_StlMesh.tri_corner_ind(itri, icorner));
	////		gpuVertices.push_back(c[0]);
	////		gpuVertices.push_back(c[1]);
	////		gpuVertices.push_back(c[2]);
	////		gpuVertices.push_back(0.f);
	////		gpuVertices.push_back(0.f);
	////		gpuVertices.push_back(n[0]);
	////		gpuVertices.push_back(n[1]);
	////		gpuVertices.push_back(n[2]);
	//	}
	//}

	m_ModelMatrix = glm::mat4(1.f);

	m_NumVertices = gpuVertices.size() / 8.f;

	float x0 = std::numeric_limits<float>::max();
	float y0 = std::numeric_limits<float>::max();
	float z0 = std::numeric_limits<float>::max();
	float x1 = std::numeric_limits<float>::lowest();
	float y1 = std::numeric_limits<float>::lowest();
	float z1 = std::numeric_limits<float>::lowest();
	for (int i = 0; i < vertices.size(); i += 8)
	{
		x0 = std::min(x0, gpuVertices[i]);
		y0 = std::min(y0, gpuVertices[i + 1]);
		x1 = std::max(x1, gpuVertices[i]);
		y1 = std::max(y1, gpuVertices[i + 1]);
		z0 = std::min(z0, gpuVertices[i + 2]);
		z1 = std::max(z1, gpuVertices[i + 2]);
	}
	m_BoundingBox = std::array<glm::vec3, 8>{
		glm::vec3(x0, y0, z0),
			glm::vec3(x0, y0, z1),
			glm::vec3(x0, y1, z0),
			glm::vec3(x0, y1, z1),
			glm::vec3(x1, y0, z0),
			glm::vec3(x1, y0, z1),
			glm::vec3(x1, y1, z0),
			glm::vec3(x1, y1, z1)
	};

	glGenVertexArrays(1, &m_Vao);
	glBindVertexArray(m_Vao);

	glGenBuffers(1, &m_Vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
	glBufferData(GL_ARRAY_BUFFER, gpuVertices.size() * sizeof(float), gpuVertices.data(), GL_STATIC_DRAW);

	//glGenBuffers(1, &m_Ebo);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Ebo);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*m_Indices.size(), m_Indices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
}


auto MC3dExplorerLib::Triangles::Draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) const -> void
{
	auto programId = m_Shader->GetProgramId();

	glUseProgram(programId);

	if (m_Hover)
		m_Shader->SetVec3("objectColor", glm::vec3(1.f, 1.f, 0.f));
	else
		m_Shader->SetVec3("objectColor", m_Color);

	glUniformMatrix4fv(glGetUniformLocation(programId, "model"), 1, GL_FALSE, glm::value_ptr(m_ModelMatrix));
	glUniformMatrix4fv(glGetUniformLocation(programId, "view"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(glGetUniformLocation(programId, "projection"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	glBindVertexArray(m_Vao);
	glDrawArrays(GL_TRIANGLES, 0, 3*m_StlMesh.num_tris());
	glBindVertexArray(0);
}


auto MC3dExplorerLib::Triangles::GetMesh() const -> stl_reader::StlMesh<float, unsigned int>
{
	return m_StlMesh;
}


auto MC3dExplorerLib::Triangles::ModelMatrix() const -> glm::mat4
{
	return m_ModelMatrix;
}

auto MC3dExplorerLib::Triangles::BoundingBox() const->std::array<glm::vec3, 8>
{
	return m_BoundingBox;
}
