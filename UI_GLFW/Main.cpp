#include <array>
#include <iostream>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <MC3dExplorerLib_DemoTriangle.h>


class Middleman
{
public:
	Middleman(GLFWwindow* window) 
		: m_Window(window)
	{
	}

	auto Render() const -> void
	{
		glClear(GL_COLOR_BUFFER_BIT);

		MC3dExplorerLib::DemoTriangle demoTriangle;
		demoTriangle.Draw();
	}

private:
	GLFWwindow* m_Window;
};


int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}
	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

	Middleman middleman(window);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		middleman.Render();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
