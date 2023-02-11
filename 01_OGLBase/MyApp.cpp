#include "MyApp.h"

#include <math.h>
#include <vector>

#include <array>
#include <list>
#include <tuple>
#include <imgui/imgui.h>
#include "includes/GLUtils.hpp"

CMyApp::CMyApp(void)
{
	m_camera.SetView(glm::vec3(0, 2, 0), glm::vec3(0, 0, 1), glm::vec3(0, 1, 0));
	m_mesh = nullptr;
}

CMyApp::~CMyApp(void)
{
}

void CMyApp::InitCube()
{
	//struct Vertex{ glm::vec3 position; glm::vec3 normals; glm::vec2 texture; };
	std::vector<Vertex>vertices;
	
	//front									 
	vertices.push_back({ glm::vec3(-0.5, -0.5, +0.5), glm::vec3(0, 0, 1), glm::vec2(0, 0) });
	vertices.push_back({ glm::vec3(+0.5, -0.5, +0.5), glm::vec3(0, 0, 1), glm::vec2(1, 0) });
	vertices.push_back({ glm::vec3(-0.5, +0.5, +0.5), glm::vec3(0, 0, 1), glm::vec2(0, 1) });
	vertices.push_back({ glm::vec3(+0.5, +0.5, +0.5), glm::vec3(0, 0, 1), glm::vec2(1, 1) });
	//back
	vertices.push_back({ glm::vec3(+0.5, -0.5, -0.5), glm::vec3(0, 0, -1), glm::vec2(0, 0) });
	vertices.push_back({ glm::vec3(-0.5, -0.5, -0.5), glm::vec3(0, 0, -1), glm::vec2(1, 0) });
	vertices.push_back({ glm::vec3(+0.5, +0.5, -0.5), glm::vec3(0, 0, -1), glm::vec2(0, 1) });
	vertices.push_back({ glm::vec3(-0.5, +0.5, -0.5), glm::vec3(0, 0, -1), glm::vec2(1, 1) });
	//right									 
	vertices.push_back({ glm::vec3(+0.5, -0.5, +0.5), glm::vec3(1, 0, 0), glm::vec2(0, 0) });
	vertices.push_back({ glm::vec3(+0.5, -0.5, -0.5), glm::vec3(1, 0, 0), glm::vec2(1, 0) });
	vertices.push_back({ glm::vec3(+0.5, +0.5, +0.5), glm::vec3(1, 0, 0), glm::vec2(0, 1) });
	vertices.push_back({ glm::vec3(+0.5, +0.5, -0.5), glm::vec3(1, 0, 0), glm::vec2(1, 1) });
	//left									 
	vertices.push_back({ glm::vec3(-0.5, -0.5, -0.5), glm::vec3(-1, 0, 0), glm::vec2(0, 0) });
	vertices.push_back({ glm::vec3(-0.5, -0.5, +0.5), glm::vec3(-1, 0, 0), glm::vec2(1, 0) });
	vertices.push_back({ glm::vec3(-0.5, +0.5, -0.5), glm::vec3(-1, 0, 0), glm::vec2(0, 1) });
	vertices.push_back({ glm::vec3(-0.5, +0.5, +0.5), glm::vec3(-1, 0, 0), glm::vec2(1, 1) });
	//top									 
	vertices.push_back({ glm::vec3(-0.5, +0.5, +0.5), glm::vec3(0, 1, 0), glm::vec2(0, 0) });
	vertices.push_back({ glm::vec3(+0.5, +0.5, +0.5), glm::vec3(0, 1, 0), glm::vec2(1, 0) });
	vertices.push_back({ glm::vec3(-0.5, +0.5, -0.5), glm::vec3(0, 1, 0), glm::vec2(0, 1) });
	vertices.push_back({ glm::vec3(+0.5, +0.5, -0.5), glm::vec3(0, 1, 0), glm::vec2(1, 1) });
	//bottom								 
	vertices.push_back({ glm::vec3(-0.5, -0.5, -0.5), glm::vec3(0, -1, 0), glm::vec2(0, 0) });
	vertices.push_back({ glm::vec3(+0.5, -0.5, -0.5), glm::vec3(0, -1, 0), glm::vec2(1, 0) });
	vertices.push_back({ glm::vec3(-0.5, -0.5, +0.5), glm::vec3(0, -1, 0), glm::vec2(0, 1) });
	vertices.push_back({ glm::vec3(+0.5, -0.5, +0.5), glm::vec3(0, -1, 0), glm::vec2(1, 1) });

	std::vector<int> indices(36);
	int index = 0;
	for (int i = 0; i < 6 * 4; i += 4)
	{
		indices[index + 0] = i + 0;
		indices[index + 1] = i + 1;
		indices[index + 2] = i + 2;
		indices[index + 3] = i + 1;
		indices[index + 4] = i + 3;
		indices[index + 5] = i + 2;
		index += 6;
	}

	m_CubeVertexBuffer.BufferData(vertices);

	m_CubeIndices.BufferData(indices);

	m_CubeVao.Init(
		{
			{ CreateAttribute<		0,
									glm::vec3,
									0,
									sizeof(Vertex)
								>, m_CubeVertexBuffer },
			{ CreateAttribute<1, glm::vec3, (sizeof(glm::vec3)), sizeof(Vertex)>, m_CubeVertexBuffer },
			{ CreateAttribute<2, glm::vec2, (2 * sizeof(glm::vec3)), sizeof(Vertex)>, m_CubeVertexBuffer },
		},
		m_CubeIndices
	);
}

void CMyApp::InitBullet()
{
	std::vector<Vertex>vertices;

	//front									 
	vertices.push_back({ glm::vec3(-0.5, -0.5, +0.5), glm::vec3(0, 0, 1), glm::vec2(0, 0) });
	vertices.push_back({ glm::vec3(+0.5, -0.5, +0.5), glm::vec3(0, 0, 1), glm::vec2(1, 0) });
	vertices.push_back({ glm::vec3(-0.5, +0.5, +0.5), glm::vec3(0, 0, 1), glm::vec2(0, 1) });
	vertices.push_back({ glm::vec3(+0.5, +0.5, +0.5), glm::vec3(0, 0, 1), glm::vec2(1, 1) });
	//back
	vertices.push_back({ glm::vec3(+0.5, -0.5, -0.5), glm::vec3(0, 0, -1), glm::vec2(0, 0) });
	vertices.push_back({ glm::vec3(-0.5, -0.5, -0.5), glm::vec3(0, 0, -1), glm::vec2(1, 0) });
	vertices.push_back({ glm::vec3(+0.5, +0.5, -0.5), glm::vec3(0, 0, -1), glm::vec2(0, 1) });
	vertices.push_back({ glm::vec3(-0.5, +0.5, -0.5), glm::vec3(0, 0, -1), glm::vec2(1, 1) });
	//right									 
	vertices.push_back({ glm::vec3(+0.5, -0.5, +0.5), glm::vec3(1, 0, 0), glm::vec2(0, 0) });
	vertices.push_back({ glm::vec3(+0.5, -0.5, -0.5), glm::vec3(1, 0, 0), glm::vec2(1, 0) });
	vertices.push_back({ glm::vec3(+0.5, +0.5, +0.5), glm::vec3(1, 0, 0), glm::vec2(0, 1) });
	vertices.push_back({ glm::vec3(+0.5, +0.5, -0.5), glm::vec3(1, 0, 0), glm::vec2(1, 1) });
	//left									 
	vertices.push_back({ glm::vec3(-0.5, -0.5, -0.5), glm::vec3(-1, 0, 0), glm::vec2(0, 0) });
	vertices.push_back({ glm::vec3(-0.5, -0.5, +0.5), glm::vec3(-1, 0, 0), glm::vec2(1, 0) });
	vertices.push_back({ glm::vec3(-0.5, +0.5, -0.5), glm::vec3(-1, 0, 0), glm::vec2(0, 1) });
	vertices.push_back({ glm::vec3(-0.5, +0.5, +0.5), glm::vec3(-1, 0, 0), glm::vec2(1, 1) });
	//top									 
	vertices.push_back({ glm::vec3(-0.5, +0.5, +0.5), glm::vec3(0, 1, 0), glm::vec2(0, 0) });
	vertices.push_back({ glm::vec3(+0.5, +0.5, +0.5), glm::vec3(0, 1, 0), glm::vec2(1, 0) });
	vertices.push_back({ glm::vec3(-0.5, +0.5, -0.5), glm::vec3(0, 1, 0), glm::vec2(0, 1) });
	vertices.push_back({ glm::vec3(+0.5, +0.5, -0.5), glm::vec3(0, 1, 0), glm::vec2(1, 1) });
	//bottom								 
	vertices.push_back({ glm::vec3(-0.5, -0.5, -0.5), glm::vec3(0, -1, 0), glm::vec2(0, 0) });
	vertices.push_back({ glm::vec3(+0.5, -0.5, -0.5), glm::vec3(0, -1, 0), glm::vec2(1, 0) });
	vertices.push_back({ glm::vec3(-0.5, -0.5, +0.5), glm::vec3(0, -1, 0), glm::vec2(0, 1) });
	vertices.push_back({ glm::vec3(+0.5, -0.5, +0.5), glm::vec3(0, -1, 0), glm::vec2(1, 1) });

	std::vector<int> indices(36);
	int index = 0;
	for (int i = 0; i < 6 * 4; i += 4)
	{
		indices[index + 0] = i + 0;
		indices[index + 1] = i + 1;
		indices[index + 2] = i + 2;
		indices[index + 3] = i + 1;
		indices[index + 4] = i + 3;
		indices[index + 5] = i + 2;
		index += 6;
	}


	m_BulletVertexBuffer.BufferData(vertices);

	m_BulletIndices.BufferData(indices);

	m_BulletVao.Init(
		{
			{ CreateAttribute<		0,
									glm::vec3,
									0,
									sizeof(Vertex)
								>, m_BulletVertexBuffer },
			{ CreateAttribute<1, glm::vec3, (sizeof(glm::vec3)), sizeof(Vertex)>, m_BulletVertexBuffer },
			{ CreateAttribute<2, glm::vec2, (2 * sizeof(glm::vec3)), sizeof(Vertex)>, m_BulletVertexBuffer },
		},
		m_BulletIndices
	);
}

void CMyApp::InitSkyBox()
{
	m_SkyboxPos.BufferData(
		std::vector<glm::vec3>{
		// back
		glm::vec3(-1, -1, -1),
		glm::vec3(1, -1, -1),
		glm::vec3(1, 1, -1),
		glm::vec3(-1, 1, -1),
		// front
		glm::vec3(-1, -1, 1),
		glm::vec3(1, -1, 1),
		glm::vec3(1, 1, 1),
		glm::vec3(-1, 1, 1),
	}
	);

	m_SkyboxIndices.BufferData(
		std::vector<int>{
			// back
			0, 1, 2,
			2, 3, 0,
			// front
			4, 6, 5,
			6, 4, 7,
			// left
			0, 3, 4,
			4, 3, 7,
			// right
			1, 5, 2,
			5, 6, 2,
			// bottom
			1, 0, 4,
			1, 4, 5,
			// top
			3, 2, 6,
			3, 6, 7,
	}
	);

	m_SkyboxVao.Init(
		{
			{ CreateAttribute<0, glm::vec3, 0, sizeof(glm::vec3)>, m_SkyboxPos },
		}, m_SkyboxIndices
	);

	// skybox texture
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	m_skyboxTexture.AttachFromFile("assets/space_blue/xpos.png", true, GL_TEXTURE_CUBE_MAP_POSITIVE_X);
	m_skyboxTexture.AttachFromFile("assets/space_blue/xneg.png", true, GL_TEXTURE_CUBE_MAP_NEGATIVE_X);
	m_skyboxTexture.AttachFromFile("assets/space_blue/ypos.png", true, GL_TEXTURE_CUBE_MAP_POSITIVE_Y);
	m_skyboxTexture.AttachFromFile("assets/space_blue/yneg.png", true, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y);
	m_skyboxTexture.AttachFromFile("assets/space_blue/zpos.png", true, GL_TEXTURE_CUBE_MAP_POSITIVE_Z);
	m_skyboxTexture.AttachFromFile("assets/space_blue/zneg.png", true, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	// skybox 2
	m_skybox2Texture.AttachFromFile("assets/space_red/xpos.png", true, GL_TEXTURE_CUBE_MAP_POSITIVE_X);
	m_skybox2Texture.AttachFromFile("assets/space_red/xneg.png", true, GL_TEXTURE_CUBE_MAP_NEGATIVE_X);
	m_skybox2Texture.AttachFromFile("assets/space_red/ypos.png", true, GL_TEXTURE_CUBE_MAP_POSITIVE_Y);
	m_skybox2Texture.AttachFromFile("assets/space_red/yneg.png", true, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y);
	m_skybox2Texture.AttachFromFile("assets/space_red/zpos.png", true, GL_TEXTURE_CUBE_MAP_POSITIVE_Z);
	m_skybox2Texture.AttachFromFile("assets/space_red/zneg.png", true, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void CMyApp::InitShaders()
{
	m_program.AttachShaders({
		{ GL_VERTEX_SHADER, "myVert.vert"},
		{ GL_FRAGMENT_SHADER, "myFrag.frag"}
	});

	m_program.BindAttribLocations({
		{ 0, "vs_in_pos" },
		{ 1, "vs_in_norm" },
		{ 2, "vs_in_tex" },
	});

	m_program.LinkProgram();

	m_programSkybox.Init(
		{
			{ GL_VERTEX_SHADER, "skybox.vert" },
			{ GL_FRAGMENT_SHADER, "skybox.frag" }
		},
		{
			{ 0, "vs_in_pos" },
		}
	);

	m_bullet.Init(
		{
			{ GL_VERTEX_SHADER, "Bullet.vert" },
			{ GL_FRAGMENT_SHADER, "Bullet.frag" }
		},
		{
			{ 0, "vs_in_pos" },
		}
		);
}

bool CMyApp::Init()
{
	glClearColor(0.125f, 0.25f, 0.5f, 1.0f);

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	InitShaders();
	InitCube();
	InitSkyBox();
	InitBullet();

	m_woodTexture.FromFile("assets/wood.jpg");
	m_suzanneTexture.FromFile("assets/psynguin/color.png");

	// mesh
	m_mesh = std::unique_ptr<Mesh>(ObjParser::parse("assets/psynguin/model.obj"));
	m_mesh->initBuffers();
	
	// camera
	m_camera.SetProj(60.0f, 640.0f / 480.0f, 0.01f, 1000.0f);

	penguins.push_back(Penguin());

	return true;
}

void CMyApp::Clean()
{
}

void CMyApp::Update()
{
	static Uint32 last_time = SDL_GetTicks();
	float delta_time = (SDL_GetTicks() - last_time) / 1000.0f;
	penguin_time += delta_time;

	m_camera.Update(delta_time);

	int kills = 0;
	for (auto& p : penguins)
	{
		if (p.isAlive)
		{
			p.updatePos(delta_time);

			for (auto& b : bullets)
			{
				if (b.isAlive && p.hitReg(b.pos)) { b.isAlive = false; }
			}
		}
		else {
			++kills;
		}
		
		if (p.isAtCenter())
		{
			m_bullet.Use();
			m_bullet.SetUniform("l", GL_TRUE);
			m_bullet.Unuse();
			m_program.Use();
			m_program.SetUniform("l", GL_TRUE);
			m_program.Unuse();
			m_programSkybox.Use();
			m_programSkybox.SetUniform("l", GL_TRUE);
			m_programSkybox.Unuse();
		}
	}

	for (auto& b : bullets)
	{
		if (b.isAlive) b.updatePos(delta_time);
	}

	if (penguins.size() <= 30 && penguin_time >= 1.0f)
	{
		penguins.push_back(Penguin());
		penguin_time -= 1.0f;
	}

	if (kills >= 30)
	{
		m_bullet.Use();
		m_bullet.SetUniform("w", GL_TRUE);
		m_bullet.Unuse();
		m_program.Use();
		m_program.SetUniform("w", GL_TRUE);
		m_program.Unuse();
		m_programSkybox.Use();
		m_programSkybox.SetUniform("w", GL_TRUE);
		m_programSkybox.Unuse();
	}

	last_time = SDL_GetTicks();
}

void CMyApp::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 viewProj = m_camera.GetViewProj();

	m_bullet.Use();
	m_BulletVao.Bind();
	m_bullet.SetUniform("c", (SDL_GetTicks() % 500) > 250 ? GL_TRUE : GL_FALSE);
	for (const auto& b : bullets)
	{
		if (!b.isAlive) { continue; }

		glm::mat4 bulletWorld = glm::translate<float>(b.pos);
		m_bullet.SetUniform("MVP", viewProj * bulletWorld);
		m_bullet.SetUniform("world", bulletWorld);
		m_bullet.SetUniform("worldIT", glm::inverse(glm::transpose(bulletWorld)));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
	}
	m_bullet.Unuse();

	// Penguin
	m_program.Use();
	m_program.SetUniform("t", (float)sin(SDL_GetTicks() / 1000.0f * 2 * M_PI) * 0.5f + 0.5f);
	m_program.SetTexture("texImage", 0, m_suzanneTexture);
	
	for (const auto& p : penguins)
	{
		if (!p.isAlive) { continue; }
		
		glm::mat4 penguinWorld = glm::translate<float>(p.pos) * glm::rotate<float>(p.rotY, glm::vec3(0,1,0));
		
		if (p.isAngry) { penguinWorld *= glm::scale<float>(glm::vec3(2,2,2)); }

		m_program.SetUniform("MVP", viewProj * penguinWorld);
		m_program.SetUniform("world", penguinWorld);
		m_program.SetUniform("worldIT", glm::inverse(glm::transpose(penguinWorld)));
		m_mesh->draw();
	}
	

	m_program.Unuse();

	// skybox
	GLint prevDepthFnc;
	glGetIntegerv(GL_DEPTH_FUNC, &prevDepthFnc);

	glDepthFunc(GL_LEQUAL);

	m_SkyboxVao.Bind();
	m_programSkybox.Use();
	m_programSkybox.SetUniform("MVP", viewProj * glm::translate( m_camera.GetEye()) );
	
	m_programSkybox.SetCubeTexture("skyboxTexture", 0, m_skyboxTexture);
	m_programSkybox.SetCubeTexture("skybox2Texture", 1, m_skybox2Texture);
	m_programSkybox.SetUniform("t", (float)sin(SDL_GetTicks()/1000.0f*2*M_PI)*0.5f + 0.5f);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
	m_programSkybox.Unuse();

	glDepthFunc(prevDepthFnc);


	ImGui::ShowTestWindow();
}

void CMyApp::KeyboardDown(SDL_KeyboardEvent& key)
{
	//m_camera.KeyboardDown(key);
}

void CMyApp::KeyboardUp(SDL_KeyboardEvent& key)
{
	//m_camera.KeyboardUp(key);
}

void CMyApp::MouseMove(SDL_MouseMotionEvent& mouse)
{
	m_camera.MouseMove(mouse);
}

void CMyApp::MouseDown(SDL_MouseButtonEvent& mouse)
{
	bullets.push_back(Bullet(m_camera.GetEye(), glm::vec3(m_camera.GetAt().x, m_camera.GetAt().y-2.0f, m_camera.GetAt().z)));
}

void CMyApp::MouseUp(SDL_MouseButtonEvent& mouse)
{
}

void CMyApp::MouseWheel(SDL_MouseWheelEvent& wheel)
{
}

void CMyApp::Resize(int _w, int _h)
{
	glViewport(0, 0, _w, _h );

	m_camera.Resize(_w, _h);
}
