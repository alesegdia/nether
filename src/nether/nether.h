#pragma once

#include <glad/gl.h>
#include <SDL.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "nether/Color.h"
#include "nether/BufferObject.h"
#include "nether/Renderer.h"
#include "nether/SDLContext.h"
#include "nether/ShaderProgram.h"
#include "nether/VertexArrayObject.h"
#include "nether/TestApp.h"
#include "nether/Texture.h"
#include "nether/Vertices.h"

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <rztl/rztl.h>

namespace nether
{

	class SceneNode
	{
	public:
	};

	class Scene
	{
	public:
		void AddNode(const std::shared_ptr<SceneNode>& sceneNode)
		{
			m_nodes.push_back(sceneNode);
		}

	private:
		std::vector<std::shared_ptr<SceneNode>> m_nodes;

	};

	class Camera
	{
	public:
		Camera(float sw, float sh, glm::vec3 pos, float yaw, float pitch, float fov)
			: m_screenWidth(sw)
			, m_screenHeight(sh)
		{
			m_lastX = m_screenWidth / 2.f;
			m_lastY = m_screenHeight / 2.f;
			Setup(pos, yaw, pitch, fov);
		}

		void Setup(glm::vec3 pos, float yaw, float pitch, float fov)
		{
			m_camPos = pos;
			m_yaw = yaw;
			m_pitch = pitch;
			m_fov = fov;

			m_projection = glm::perspective(glm::radians(m_fov), (float)m_screenWidth / (float)m_screenHeight, 0.1f, 100.0f);
		}

		const glm::mat4& GetProjection()
		{
			return m_projection;
		}

		const glm::mat4& GetView()
		{
			return glm::lookAt(m_camPos, m_camPos + m_camFront, m_camUp);
		}

		void Move(const glm::vec3& d)
		{
			m_camPos += d;
		}

		void Rotate(float yaw, float pitch)
		{
			m_yaw += yaw;
			m_pitch += pitch;
		
			if (m_pitch > 89.0f)
				m_pitch = 89.0f;
			if (m_pitch < -89.0f)
				m_pitch = -89.0f;

			glm::vec3 front;
			front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
			front.y = sin(glm::radians(pitch));
			front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
			m_camFront = glm::normalize(front);
		}

		const glm::vec3& GetCamFront()
		{
			return m_camFront;
		}

		const glm::vec3& GetCamUp()
		{
			return m_camUp;
		}

	private:
		glm::vec3 m_camPos;
		glm::vec3 m_camFront = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 m_camUp = glm::vec3(0.0f, 1.0f, 0.0f);

		glm::mat4 m_projection;

		float m_screenWidth;
		float m_screenHeight;

		float m_yaw;
		float m_pitch;
		float m_lastX;
		float m_lastY;
		float m_fov;
	};

}

