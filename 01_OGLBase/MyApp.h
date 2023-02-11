#pragma once

// C++ includes
#include <memory>

// GLEW
#include <GL/glew.h>

// SDL
#include <SDL.h>
#include <SDL_opengl.h>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>

#include "includes/gCamera.h"

#include "includes/ProgramObject.h"
#include "includes/BufferObject.h"
#include "includes/VertexArrayObject.h"
#include "includes/TextureObject.h"

// mesh
#include "includes/ObjParser_OGL3.h"

class CMyApp
{
public:
	CMyApp();
	~CMyApp();

	bool Init();
	void Clean();

	void Update();
	void Render();

	void KeyboardDown(SDL_KeyboardEvent&);
	void KeyboardUp(SDL_KeyboardEvent&);
	void MouseMove(SDL_MouseMotionEvent&);
	void MouseDown(SDL_MouseButtonEvent&);
	void MouseUp(SDL_MouseButtonEvent&);
	void MouseWheel(SDL_MouseWheelEvent&);
	void Resize(int, int);

protected:
	// shader
	ProgramObject		m_program;			// mesh shader
	ProgramObject		m_programSkybox;	// skybox shader
	ProgramObject		m_bullet;

	VertexArrayObject	m_CubeVao;			// VAO
	IndexBuffer			m_CubeIndices;		// index buffer
	ArrayBuffer			m_CubeVertexBuffer;	// VBO
	VertexArrayObject	m_SkyboxVao;
	IndexBuffer			m_SkyboxIndices;	
	ArrayBuffer			m_SkyboxPos;
	VertexArrayObject	m_BulletVao;
	IndexBuffer			m_BulletIndices;
	ArrayBuffer			m_BulletVertexBuffer;

	gCamera				m_camera;

	Texture2D			m_woodTexture;
	Texture2D			m_suzanneTexture;

	TextureCubeMap		m_skyboxTexture;
	TextureCubeMap		m_skybox2Texture;

	struct Vertex
	{
		glm::vec3 p;
		glm::vec3 n;
		glm::vec2 t;
	};

	std::unique_ptr<Mesh> m_mesh;

	struct Penguin {
		glm::vec3 pos{};
		float rotY{};
		float speed{};

		bool isAngry{ false };
		bool isAlive{ true };

		Penguin() {
			pos = glm::vec3{rand() / (float)RAND_MAX * 40, 0, rand() / (float)RAND_MAX * 40 };
			rotY = atan2(glm::vec3{ 0 }.x - pos.x, glm::vec3{ 0 }.z - pos.z);
			speed = rand() / (float)RAND_MAX * 2 + 1;
		}

		void updatePos(float dt)
		{
			if (isAtCenter())
			{
				isAlive = false;
				return;
			}
			pos += glm::normalize(glm::vec3{ 0 } - pos) * dt * speed;
		}

		bool isAtCenter() const
		{
			if (glm::distance(pos, glm::vec3{ 0 }) < 0.05) return true;
			return false;
		}

		bool hitReg(glm::vec3 bulletPos)
		{
			int hitbox = 1;
			if (isAngry) { hitbox = 2; }
			
			if (glm::distance(pos, bulletPos) < hitbox)
			{
				if (isAngry) {
					isAlive = false;
				}
				else {
					isAngry = true;
				}
				return true;
			}
			return false;
		}
	};

	std::vector<Penguin> penguins;

	struct Bullet {
		glm::vec3 pos{};
		glm::vec3 direction{};
		const float speed{ 10 };
		bool isAlive{ true };

		Bullet(glm::vec3 pos, glm::vec3 direction) : pos{pos}, direction{glm::normalize(direction)}
		{

		}

		void updatePos(float dt)
		{
			pos += direction * dt * speed;
		}
	};

	std::vector<Bullet> bullets;

	float penguin_time = 0;

	void InitShaders();
	void InitCube();
	void InitBullet();
	void InitSkyBox();
};

