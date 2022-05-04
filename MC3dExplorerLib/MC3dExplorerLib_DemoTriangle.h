#pragma once


#include <GL/glew.h>


namespace MC3dExplorerLib
{


	class DemoTriangle
	{
	public:
		DemoTriangle();

		auto Draw() const -> void;

	private:
		GLuint m_ShaderProgram = 0;
		GLuint m_VAO = 0;
	};


}
