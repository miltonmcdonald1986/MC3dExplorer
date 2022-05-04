#pragma once


#include <map>

#include "MC3dExplorerLib_Camera.h"
#include "MC3dExplorerLib_ProjectionOrthographic.h"


namespace MC3dExplorerLib
{


	struct GlobalState
	{
		Camera																camera = Camera();
		ProjectionOrthographic												projection = ProjectionOrthographic();
		std::vector<Drawable*>												drawables = std::vector<Drawable*>();
		glm::vec3															clearColor = glm::vec3(0.f, 0.f, 0.f);
		double																cursorPosX = 0.;
		double																cursorPosY = 0.;
		double																cursorPosXPrev = 0.;
		double																cursorPosYPrev = 0.;
		int																	polygonMode = GL_FILL;
		float											mixPercentage = 0.f;
		std::map<ShaderIds, std::unique_ptr<Shader> >	shaders = {};
		float																windowHeight = 600.f;
		float																windowWidth = 800.f;
		float																zoom = 10.f / 800.f;
	};


}
