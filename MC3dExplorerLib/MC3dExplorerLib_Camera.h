#pragma once


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace MC3dExplorerLib
{


	class Camera
	{
	public:
		Camera();

		auto DoArcballRotation(float angleX, float angleY)	-> void;
		auto UpdateViewMatrix()								-> void;
		auto SetViewIsometric()								-> void;
		auto SetViewBack()									-> void;
		auto SetViewBottom()								-> void;
		auto SetViewFront()									-> void;
		auto SetViewLeft()									-> void;
		auto SetViewRight()									-> void;
		auto SetViewTop()									-> void;
		auto ViewMatrix() const->glm::mat4;

		//private:
		glm::vec3 m_Eye;
		glm::vec3 m_Center;
		glm::vec3 m_Right;
		glm::vec3 m_Up;
		glm::mat4 m_View;
	};


}
