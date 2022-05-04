#include "MC3dExplorerLib_MC3dExplorer.h"

#include <glm/glm.hpp>

#include <Mathematics/AlignedBox.h>
#include <Mathematics/IntrLine3AlignedBox3.h>
#include <Mathematics/IntrLine3Triangle3.h>
#include <Mathematics/Line.h>
#include <Mathematics/Vector3.h>

#include "MC3dExplorerLib_GlobalState.h"


namespace
{


	auto ToGteVector3(const glm::vec3& glmVector) -> gte::Vector3<float>
	{
		return gte::Vector3<float>({ glmVector.x, glmVector.y, glmVector.z });
	}


}


MC3dExplorerLib::MC3dExplorer::MC3dExplorer()
{
	m_GlobalState = new GlobalState();

	//ErrorCode errorCode = GLFWInit(window, pGS.get());
	//pGS->projection.SetWindow(window);

	//switch (errorCode)
	//{
	//case MC_OpenGL::ErrorCode::NONE:
	//	if (window == nullptr)
	//		return static_cast<int>(MC_OpenGL::ErrorCode::ERROR_GLFW_WINDOW_IS_NULL);
	//	break;
	//default:
	//	return static_cast<int>(errorCode);
	//}

	glEnable(GL_DEPTH_TEST);


	InitDrawables();

	//Shader shaderAllWhite(R"(..\shaders\vsBasicCoordinateSystems.glsl)", R"(..\shaders\fsAllWhite.glsl)");
	//m_ShaderSolidColor = Shader(R"(..\shaders\vsBasicCoordinateSystems.glsl)", R"(..\shaders\fsBasicLightColor.glsl)");

	// Load shaders
	std::unique_ptr<Shader> solidColorShader(new Shader(R"(..\shaders\vsBasicCoordinateSystems.glsl)", R"(..\shaders\fsBasicLightColor.glsl)"));
	m_GlobalState->shaders[ShaderIds::SolidColor] = { std::move(solidColorShader) };


	//glUseProgram(m_ShaderSolidColor.GetProgramId());
	//m_ShaderSolidColor.SetVec3("lightColor", glm::vec3(1.f, 1.f, 1.f));
	//m_ShaderSolidColor.SetVec3("objectColor", glm::vec3(0.5f, 0.5f, 1.f));

	//for (int i = 0; i < 10; ++i)
	//{
		//m_GlobalState->drawables.push_back(new Cube(m_ShaderSolidColor.GetProgramId(), glm::translate(glm::mat4(1.f), cubePositions[i])));
		//m_GlobalState->drawables.back()->SetColor(glm::vec3(0.5f, 0.5f, 1.f));
	//}
	//m_GlobalState->projection.ZoomFit(m_GlobalState->camera, m_GlobalState->drawables, m_GlobalState->camera.ViewMatrix());

	//glfwGetCursorPos(window, &pGS->cursorPosX, &pGS->cursorPosY);
}


MC3dExplorerLib::MC3dExplorer::~MC3dExplorer()
{
	delete m_GlobalState;
}


auto MC3dExplorerLib::MC3dExplorer::ArcballRotate() const -> void
{
	float cursorDx = static_cast<float>(m_GlobalState->cursorPosX - m_GlobalState->cursorPosXPrev);
	float cursorDy = static_cast<float>(m_GlobalState->cursorPosY - m_GlobalState->cursorPosYPrev);

	float angleX = cursorDx * 2.f * glm::pi<float>() / m_GlobalState->windowWidth;
	float angleY = cursorDy * 2.f * glm::pi<float>() / m_GlobalState->windowHeight;

	m_GlobalState->camera.DoArcballRotation(angleX, angleY);
	m_GlobalState->projection.ZoomFit(m_GlobalState->camera, m_GlobalState->drawables, m_GlobalState->camera.ViewMatrix(), true);
}


auto MC3dExplorerLib::MC3dExplorer::ChangeColorOfBackground(const glm::vec3& color) -> void
{
	m_GlobalState->clearColor = color;
}


auto MC3dExplorerLib::MC3dExplorer::ChangeColorOfSelected(const glm::vec3& color) -> void
{
	for (auto& drawable : m_GlobalState->drawables)
	{
		if (drawable->GetSelected())
			drawable->SetColor(color);
	}
}


auto MC3dExplorerLib::MC3dExplorer::CursorZoom(int rotation) -> void
{
	m_GlobalState->projection.ZoomInOutToCursor((float)rotation);
}


auto MC3dExplorerLib::MC3dExplorer::Draw() const -> void
{
	//m_ShaderSolidColor.SetVec3("viewPos", glm::vec3(0.5f * (m_GlobalState->projection.GetRight() + m_GlobalState->projection.GetLeft()), 0.5f * (m_GlobalState->projection.GetTop() + m_GlobalState->projection.GetBottom()), 22.f/*abs(pGS->projection.m_Near)*/));

	glViewport(0, 0, (GLsizei)m_GlobalState->windowWidth, (GLsizei)m_GlobalState->windowHeight);
	glClearColor(m_GlobalState->clearColor.r, m_GlobalState->clearColor.g, m_GlobalState->clearColor.b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (const Drawable* drawable : m_GlobalState->drawables)
	{
		m_GlobalState->shaders[ShaderIds::SolidColor]->SetVec3("viewPos", glm::vec3(0.5f * (m_GlobalState->projection.GetRight() + m_GlobalState->projection.GetLeft()), 0.5f * (m_GlobalState->projection.GetTop() + m_GlobalState->projection.GetBottom()), 22.f/*abs(pGS->projection.m_Near)*/));
		m_GlobalState->shaders[ShaderIds::SolidColor]->SetVec3("lightColor", glm::vec3(1.f, 1.f, 1.f));
		//Shader* shader = m_GlobalState->shaders[drawable->GetShaderId()].get();
		//shader->Use();
		//if (drawable->GetShaderId() == ShaderIds::SolidColor)
		//{
			//shader->SetVec3("viewPos", glm::vec3(0.5f * (m_GlobalState->projection.GetRight() + m_GlobalState->projection.GetLeft()), 0.5f * (m_GlobalState->projection.GetTop() + m_GlobalState->projection.GetBottom()), 22.f/*abs(pGS->projection.m_Near)*/));
			/*if (drawable->GetHover() || drawable->GetSelected())
				shader->SetVec3("objectColor", glm::vec3(1.f, 1.f, 0.f));
			else
				shader->SetVec3("objectColor", drawable->GetColor());*/
		//}

		drawable->Draw(m_GlobalState->camera.ViewMatrix(), m_GlobalState->projection.ProjectionMatrix());
	}
}


auto MC3dExplorerLib::MC3dExplorer::Hover() const -> void
{
	const ProjectionOrthographic& projection = m_GlobalState->projection;

	glm::vec3 ndc = glm::vec3(m_GlobalState->cursorPosX / m_GlobalState->windowWidth, 1.f - m_GlobalState->cursorPosY/ m_GlobalState->windowHeight, projection.GetNear()) * 2.f - 1.f;
	auto viewSpace = glm::inverse(m_GlobalState->projection.ProjectionMatrix()) * glm::vec4(ndc, 1.f);
	auto worldSpaceNear = glm::inverse(m_GlobalState->camera.ViewMatrix()) * glm::vec4(viewSpace);

	ndc = glm::vec3(m_GlobalState->cursorPosX / m_GlobalState->windowWidth, 1.f - m_GlobalState->cursorPosY / m_GlobalState->windowHeight, m_GlobalState->projection.GetFar()) * 2.f - 1.f;
	viewSpace = glm::inverse(m_GlobalState->projection.ProjectionMatrix()) * glm::vec4(ndc, 1.f);
	auto worldSpaceFar = glm::inverse(m_GlobalState->camera.ViewMatrix()) * glm::vec4(viewSpace);

	int minIndex = (int)m_GlobalState->drawables.size();
	double minParm = std::numeric_limits<double>::max();
	for (int i = 0; i < m_GlobalState->drawables.size(); ++i)
	{
		m_GlobalState->drawables[i]->SetHover(false);

		float x0 = std::numeric_limits<float>::max();
		float y0 = std::numeric_limits<float>::max();
		float z0 = std::numeric_limits<float>::max();
		float x1 = std::numeric_limits<float>::lowest();
		float y1 = std::numeric_limits<float>::lowest();
		float z1 = std::numeric_limits<float>::lowest();
		const auto& drawable = m_GlobalState->drawables[i];
		const auto& boundingBox = drawable->BoundingBox();
		for (int j = 0; j < boundingBox.size(); ++j)
		{
			glm::vec3 ptWorldSpace = drawable->ModelMatrix() * glm::vec4(boundingBox[j], 1.f);
			x0 = std::min(x0, ptWorldSpace.x);
			y0 = std::min(y0, ptWorldSpace.y);
			x1 = std::max(x1, ptWorldSpace.x);
			y1 = std::max(y1, ptWorldSpace.y);
			z0 = std::min(z0, ptWorldSpace.z);
			z1 = std::max(z1, ptWorldSpace.z);
		}

		gte::Vector3<float> bboxMin({ x0, y0, z0 });
		gte::Vector3<float> bboxMax({ x1, y1, z1 });

		gte::Line3<float> line(ToGteVector3(worldSpaceNear), ToGteVector3(glm::normalize(worldSpaceFar - worldSpaceNear)));
		gte::AlignedBox3<float> box(bboxMin, bboxMax);

		gte::FIQuery<float, gte::Line3<float>, gte::AlignedBox3<float> > fiq;
		auto fiqResult = fiq(line, box);
		if (fiqResult.intersect)
		{
			if (m_GlobalState->drawables[i]->GetType() == DrawableType::Triangles)
			{
				Triangles* stl = (Triangles*)(m_GlobalState->drawables[i]);
				auto mesh = stl->GetMesh();
				for (int j = 0; j < mesh.num_tris(); ++j)
				{
					auto inds = mesh.tri_corner_inds(j);
					auto v0 = mesh.vrt_coords(inds[0]);
					auto v1 = mesh.vrt_coords(inds[1]);
					auto v2 = mesh.vrt_coords(inds[2]);

					gte::Triangle3<float> triangle(gte::Vector3<float>({ v0[0], v0[1], v0[2] }), gte::Vector3<float>({ v1[0], v1[1], v1[2] }), gte::Vector3<float>({ v2[0], v2[1], v2[2] }));
					gte::FIQuery<float, gte::Line3<float>, gte::Triangle3<float> > fiqTriangle;
					gte::FIQuery<float, gte::Line3<float>, gte::Triangle3<float> >::Result fiqTriangleResult = fiqTriangle(line, triangle);
					if ((fiqTriangleResult.intersect)/* && (fiqTriangleResult.parameter < minParm)*/)
					{
						minParm = fiqResult.parameter[0];
						minIndex = i;
					}
				}
			}
			else if (fiqResult.parameter[0] < minParm)
			{
				minParm = fiqResult.parameter[0];
				minIndex = i;
			}
		}
	}

	if (minIndex < m_GlobalState->drawables.size())
		m_GlobalState->drawables[minIndex]->SetHover(true);
}


auto MC3dExplorerLib::MC3dExplorer::LoadObjectFromFile(const std::filesystem::path& path) -> void
{
	if (path.extension() == ".stl");
	{
		auto triangles = new Triangles(m_GlobalState->shaders[ShaderIds::SolidColor].get(), path.string());
		triangles->SetColor(glm::vec3(0.5f, 0.5f, 0.5f));
		m_GlobalState->drawables.push_back(triangles);
		ZoomFit();
	}
}


auto MC3dExplorerLib::MC3dExplorer::Pan() -> void
{
	float cursorDx = static_cast<float>(m_GlobalState->cursorPosX - m_GlobalState->cursorPosXPrev);
	float cursorDy = static_cast<float>(m_GlobalState->cursorPosY - m_GlobalState->cursorPosYPrev);

	m_GlobalState->projection.Pan(cursorDx, cursorDy);
}


auto MC3dExplorerLib::MC3dExplorer::Select() -> void
{
	for (int i = 0; i < m_GlobalState->drawables.size(); ++i)
	{
		if (m_GlobalState->drawables[i]->GetHover())
		{
			if (m_GlobalState->drawables[i]->GetSelected())
				m_GlobalState->drawables[i]->SetSelected(false);
			else
				m_GlobalState->drawables[i]->SetSelected(true);
		}
	}
}


auto MC3dExplorerLib::MC3dExplorer::SetCursorPos(float x, float y) -> void
{
	m_GlobalState->projection.SetCursorPos(x, y);

	m_GlobalState->cursorPosXPrev = m_GlobalState->cursorPosX;
	m_GlobalState->cursorPosYPrev = m_GlobalState->cursorPosY;

	m_GlobalState->cursorPosX = x;
	m_GlobalState->cursorPosY = y;
}


auto MC3dExplorerLib::MC3dExplorer::SetGLPolygonMode(GLPolygonMode polygonMode) -> void
{
	switch (polygonMode)
	{
	case GLPolygonMode::Shaded:
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	case GLPolygonMode::Wireframe:
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	}
}


auto MC3dExplorerLib::MC3dExplorer::SetViewBack() -> void
{
	m_GlobalState->camera.SetViewBack();

	m_GlobalState->projection.ZoomFit(m_GlobalState->camera, m_GlobalState->drawables, m_GlobalState->camera.ViewMatrix(), true);
	m_GlobalState->projection.AutoCenter(m_GlobalState->camera, m_GlobalState->drawables, m_GlobalState->camera.ViewMatrix());
}


auto MC3dExplorerLib::MC3dExplorer::SetViewBottom() -> void
{
	m_GlobalState->camera.SetViewBottom();

	m_GlobalState->projection.ZoomFit(m_GlobalState->camera, m_GlobalState->drawables, m_GlobalState->camera.ViewMatrix(), true);
	m_GlobalState->projection.AutoCenter(m_GlobalState->camera, m_GlobalState->drawables, m_GlobalState->camera.ViewMatrix());
}


auto MC3dExplorerLib::MC3dExplorer::SetViewFront() -> void
{
	m_GlobalState->camera.SetViewFront();

	m_GlobalState->projection.ZoomFit(m_GlobalState->camera, m_GlobalState->drawables, m_GlobalState->camera.ViewMatrix(), true);
	m_GlobalState->projection.AutoCenter(m_GlobalState->camera, m_GlobalState->drawables, m_GlobalState->camera.ViewMatrix());
}


auto MC3dExplorerLib::MC3dExplorer::SetViewLeft() -> void
{
	m_GlobalState->camera.SetViewLeft();

	m_GlobalState->projection.ZoomFit(m_GlobalState->camera, m_GlobalState->drawables, m_GlobalState->camera.ViewMatrix(), true);
	m_GlobalState->projection.AutoCenter(m_GlobalState->camera, m_GlobalState->drawables, m_GlobalState->camera.ViewMatrix());
}


auto MC3dExplorerLib::MC3dExplorer::SetViewIsometric() -> void
{
	m_GlobalState->camera.SetViewIsometric();

	m_GlobalState->projection.ZoomFit(m_GlobalState->camera, m_GlobalState->drawables, m_GlobalState->camera.ViewMatrix(), true);
	m_GlobalState->projection.AutoCenter(m_GlobalState->camera, m_GlobalState->drawables, m_GlobalState->camera.ViewMatrix());
}


auto MC3dExplorerLib::MC3dExplorer::SetViewRight() -> void
{
	m_GlobalState->camera.SetViewRight();

	m_GlobalState->projection.ZoomFit(m_GlobalState->camera, m_GlobalState->drawables, m_GlobalState->camera.ViewMatrix(), true);
	m_GlobalState->projection.AutoCenter(m_GlobalState->camera, m_GlobalState->drawables, m_GlobalState->camera.ViewMatrix());
}


auto MC3dExplorerLib::MC3dExplorer::SetViewTop() -> void
{
	m_GlobalState->camera.SetViewTop();

	m_GlobalState->projection.ZoomFit(m_GlobalState->camera, m_GlobalState->drawables, m_GlobalState->camera.ViewMatrix(), true);
	m_GlobalState->projection.AutoCenter(m_GlobalState->camera, m_GlobalState->drawables, m_GlobalState->camera.ViewMatrix());
}


auto MC3dExplorerLib::MC3dExplorer::SetWindowSize(float width, float height) -> void
{
	//if (WindowIsMinimized(width, height))
	//	return;

	glViewport(0, 0, width, height);

	m_GlobalState->projection.Resize(m_GlobalState->windowWidth, m_GlobalState->windowHeight, (float)width, (float)height);
	m_GlobalState->projection.SetWindowHeight(height);
	m_GlobalState->projection.SetWindowWidth(width);

	m_GlobalState->windowHeight = (float)height;
	m_GlobalState->windowWidth = (float)width;
}


auto MC3dExplorerLib::MC3dExplorer::UnselectAll() -> void
{
	for (auto &drawable : m_GlobalState->drawables)
	{
		drawable->SetSelected(false);
	}
}


auto MC3dExplorerLib::MC3dExplorer::ZoomFit() -> void
{
	m_GlobalState->projection.ZoomFit(m_GlobalState->camera, m_GlobalState->drawables, m_GlobalState->camera.ViewMatrix());
}
