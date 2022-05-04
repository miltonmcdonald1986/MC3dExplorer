#pragma once


#include <vector>

#include "MC3dExplorerLib_Camera.h"
#include "MC3dExplorerLib_Drawable.h"


namespace MC3dExplorerLib
{


	class ProjectionOrthographic
	{
	public:
		ProjectionOrthographic();

		auto AutoCenter(const Camera& camera, const std::vector<Drawable*>& drawables, const glm::mat4& viewMatrix) -> void;
		auto GetBottom() -> double;
		auto GetFar() -> double;
		auto GetLeft() -> double;
		auto GetNear() const -> double;
		auto GetRight() -> double;
		auto GetTop() -> double;
		auto Pan(float cursorDx, float cursorDy) -> void;
		auto ProjectionMatrix() const->glm::mat4;
		auto Resize(float oldWidth, float oldHeight, float newWidth, float newHeight) -> void;

		auto SetCursorPos(float x, float y) -> void;
		auto SetWindowHeight(float height) -> void;
		auto SetWindowWidth(float width) -> void;
		//auto SetWindow(GLFWwindow* window) -> void;
		auto ZoomFit(const Camera& camera, const std::vector<Drawable*>& drawables, const glm::mat4& viewMatrix, bool fitZOnly = false) -> void;
		auto ZoomInOutToCursor(float offset) -> void;

	//private:
		auto UpdateProjectionMatrix(float zNear, float zFar) -> void;
		auto UpdateProjectionMatrix(float aspectRatio, float cx, float cy, float dx, float dy, float zNear, float zFar) -> void;
		auto ZoomInOut(float offset) -> void;

		float m_Left = -400.f;
		float m_Right = 400.f;
		float m_Bottom = -300.f;
		float m_Top = 300.f;
		float m_Near = 0.1f;
		float m_Far = 100.f;
		float m_CursorX = 0.f;
		float m_CursorY = 0.f;
		float m_WindowWidth = 800.f;
		float m_WindowHeight = 600.f;
	};


}
