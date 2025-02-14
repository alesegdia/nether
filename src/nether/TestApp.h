#pragma once

#include "nether/SDLContext.h"
#include "nether/Renderer.h"

namespace nether
{

    class TestApp
    {
    public:
        TestApp(int windowWidth = 800, int windowHeight = 600);

        virtual ~TestApp();

        virtual void Step(float delta) = 0;
        virtual void Init() = 0;
        virtual void Cleanup() = 0;

        virtual void OnKeyUp(const SDL_Event& evt);

        virtual void MouseMoved(float mousePosX, float mousePosY);

        void Run(int screenWidth = 800, int screenHeight = 600);

    protected:
        nether::SDLContext& GetCtx();

        nether::Renderer& GetRenderer();


    private:
        nether::SDLContext m_ctx;
        nether::Renderer m_renderer;
        int m_windowWidth = 0;
        int m_windowHeight = 0;


    };

}

