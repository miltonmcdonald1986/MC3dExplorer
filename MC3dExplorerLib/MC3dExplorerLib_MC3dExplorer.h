#pragma once


#include <filesystem>
#include <memory>

#include "MC3dExplorerLib_GlobalState.h"


namespace MC3dExplorerLib
{


	enum class GLPolygonMode
	{
		Shaded,
		Wireframe
	};


	class MC3dExplorer
	{
	public:
		MC3dExplorer();
		~MC3dExplorer();

		auto ArcballRotate() const -> void;
		auto ChangeColorOfBackground(const glm::vec3& color) -> void;
		auto ChangeColorOfSelected(const glm::vec3& color) -> void;
		auto CursorZoom(int rotation) -> void;
		auto Draw() const -> void;
		auto Hover() const -> void;
		auto LoadObjectFromFile(const std::filesystem::path& path) -> void;
		auto Pan() -> void;
		auto Select() -> void;
		auto SetCursorPos(float x, float y) -> void;
		auto SetGLPolygonMode(GLPolygonMode polygonMode) -> void;
		auto SetViewBack() -> void;
		auto SetViewBottom() -> void;
		auto SetViewFront() -> void;
		auto SetViewIsometric() -> void;
		auto SetViewLeft() -> void;
		auto SetViewRight() -> void;
		auto SetViewTop() -> void;
		auto SetWindowSize(float width, float height) -> void;
		auto UnselectAll() -> void;
		auto ZoomFit() -> void;

	private:
		GlobalState*	m_GlobalState;
		Shader			m_ShaderSolidColor;
	};


}
