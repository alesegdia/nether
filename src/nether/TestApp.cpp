#include "TestApp.h"

namespace nether
{


	TestApp::TestApp(int windowWidth /*= 800*/, int windowHeight /*= 600*/) : m_windowWidth(windowWidth)
		, m_windowHeight(windowHeight)
	{

	}

	TestApp::~TestApp()
	{

	}

	void TestApp::OnKeyUp(const SDL_Event& evt)
	{

	}

	void TestApp::MouseMoved(float mousePosX, float mousePosY)
	{

	}

	void TestApp::Run(int screenWidth /*= 800*/, int screenHeight /*= 600*/)
	{
		m_ctx.Init(screenWidth, screenHeight);

		Init();

		int exit = 0;
		uint64_t ticks = SDL_GetTicks();

		while (!exit) {
			SDL_Event event;
			while (SDL_PollEvent(&event)) {
				switch (event.type) {
				case SDL_QUIT:
					exit = 1;
					break;
				case SDL_KEYUP:
					if (event.key.keysym.sym == SDLK_ESCAPE) {
						exit = 1;
					}
					if (event.key.keysym.sym == SDLK_p) {
						GetRenderer().SetWireframeMode();
					}
					if (event.key.keysym.sym == SDLK_o) {
						GetRenderer().SetFillMode();
					}
					if (event.key.keysym.sym == SDLK_i) {
						GetRenderer().SetFront();
					}
					if (event.key.keysym.sym == SDLK_u) {
						GetRenderer().SetBack();
					}
					if (event.key.keysym.sym == SDLK_y) {
						GetRenderer().SetFrontBack();
					}
					OnKeyUp(event);
					break;
				case SDL_MOUSEMOTION:
				{
					float mx = float(event.motion.x);
					float my = float(event.motion.y);
					MouseMoved(mx, my);
				}
				break;
				default:
					break;
				}
			}

			auto currentTicks = SDL_GetTicks();
			float delta = currentTicks - ticks;
			Step(float(delta));
			ticks = currentTicks;

			m_ctx.EndFrame();
		}

		Cleanup();
		m_ctx.Cleanup();
	}

	nether::SDLContext& TestApp::GetCtx()
	{
		return m_ctx;
	}

	nether::Renderer& TestApp::GetRenderer()
	{
		return m_renderer;
	}

}
