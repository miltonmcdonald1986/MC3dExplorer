#pragma once


#include <array>
#include <string>
#include <vector>

#include <GL/glew.h>

#include <Mathematics/Triangle.h>

#include <stl_reader.h>

#include "MC3dExplorerLib_Shader.h"


namespace MC3dExplorerLib
{


	enum class DrawableType
	{
		Cube,
		Triangles,
		WoodenBox
	};


	class Drawable
	{
	public:
		Drawable(const Shader* const shader, DrawableType drawableType);

		virtual auto Draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) const -> void = 0;
		virtual auto BoundingBox() const->std::array<glm::vec3, 8> = 0;
		virtual auto ModelMatrix() const->glm::mat4 = 0;

		auto GetColor() const->glm::vec3;
		auto GetHover() const -> bool;
		auto GetSelected() const -> bool;
		//inline auto GetShaderId() const -> ShaderIds { return m_ShaderId; };
		auto GetType() const->DrawableType;
		auto SetColor(const glm::vec3& rgb) -> void;
		auto SetHover(bool hover) -> void;
		auto SetModel(const glm::mat4& model) -> void;
		auto SetSelected(bool selected) -> void;

	protected:
		const Shader* const m_Shader;
		DrawableType m_Type = DrawableType::Cube;
		glm::vec3 m_Color = glm::vec3(0.f, 0.f, 1.f);
		bool m_Hover = false;
		glm::mat4 m_ModelMatrix = glm::mat4(1.f);
		bool m_Selected = false;
		////ShaderIds m_ShaderId = ShaderIds::SolidColor;
	};


	class Cube : public Drawable
	{
	public:
		Cube(const Shader* shader, const glm::mat4& modelMatrix, DrawableType type = DrawableType::Cube);

		virtual auto Draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) const -> void;

		auto BoundingBox() const->std::array<glm::vec3, 8>;
		auto ModelMatrix() const->glm::mat4;

	protected:
		GLuint						m_Vao = 0;
		std::array<glm::vec3, 8>	m_BoundingBox = std::array<glm::vec3, 8>();
	};


	class Triangles : public Drawable
	{
	public:
		Triangles(const Shader* shader, const std::string& stl);

		auto BoundingBox() const->std::array<glm::vec3, 8>;
		auto Draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) const -> void;
		auto GetMesh() const -> stl_reader::StlMesh<float, unsigned int>;
		auto ModelMatrix() const->glm::mat4;

	private:
		glm::mat4									m_ModelMatrix;
		std::array<glm::vec3, 8>					m_BoundingBox;
		std::vector<unsigned int>					m_Indices;
		std::vector<float>							m_Vertices;
		stl_reader::StlMesh<float, unsigned int>	m_StlMesh;
		GLuint										m_NumVertices;
		GLuint										m_Vao = 0;
		GLuint										m_Vbo = 0;
		//GLuint										m_Ebo = 0;
	};


	//class WoodenBox : public Cube
	//{
	//public:
	//	WoodenBox(const glm::mat4& modelMatrix);

	//	auto Draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) const -> void;
	//};


	auto InitDrawables() -> void;

	extern float vertices[];
	extern GLuint vao;
	extern std::array<glm::vec3, 8> boundingBox;
	extern std::vector<glm::vec3> cubePositions;
	extern unsigned int texture0;
	extern unsigned int texture1;


}
