#pragma once

#include "nether/SDLContext.h"
#include "nether/Renderer.h"

namespace nether
{

    class TestApp
    {
    public:
        TestApp(int windowWidth = 800, int windowHeight = 600)
            : m_windowWidth(windowWidth)
            , m_windowHeight(windowHeight)
        {

        }

        virtual ~TestApp() {}

        virtual void Step(float delta) = 0;
        virtual void Init() = 0;
        virtual void Cleanup() = 0;

        void Run()
        {
            m_ctx.Init(800, 600);

            Init();

            int exit = 0;
            uint64_t ticks = SDL_GetTicks();

            while (!exit) {
                SDL_Event event;
                while (SDL_PollEvent(&event)) {
                    switch (event.type) {
                    case SDL_EVENT_QUIT:
                        exit = 1;
                        break;
                    case SDL_EVENT_KEY_UP:
                        if (event.key.keysym.sym == SDLK_ESCAPE) {
                            exit = 1;
                        }
                        if (event.key.keysym.sym == SDLK_w) {
                            GetRenderer().SetWireframeMode();
                        }
                        if (event.key.keysym.sym == SDLK_q) {
                            GetRenderer().SetFillMode();
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

    protected:
        nether::SDLContext& GetCtx()
        {
            return m_ctx;
        }

        nether::Renderer& GetRenderer()
        {
            return m_renderer;
        }


    private:
        nether::SDLContext m_ctx;
        nether::Renderer m_renderer;
        int m_windowWidth = 0;
        int m_windowHeight = 0;


    };

}

