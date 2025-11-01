#include "nether/NetherGL.h"

namespace nether {
namespace gl {

// Global OpenGL function pointer
OpenGLFunctions* g_gl = nullptr;

#ifdef AETHER_USE_GLAD
// Direct OpenGL implementation instance
static DirectOpenGLFunctions s_directGL;
#endif

#ifdef AETHER_USE_QT
// Qt OpenGL implementation instance - will be created when needed
static QtOpenGLFunctions* s_qtGL = nullptr;
#endif

void initializeDirectGL() {
#ifdef AETHER_USE_GLAD
    g_gl = &s_directGL;
#else
    // Should not be called without GLAD support
    g_gl = nullptr;
#endif
}

#ifdef AETHER_USE_QT
void initializeQtGL(QOpenGLFunctions_4_5_Core* gl) {
    if (s_qtGL) {
        delete s_qtGL;
    }
    s_qtGL = new QtOpenGLFunctions(gl);
    g_gl = s_qtGL;
}
#endif

} // namespace gl
} // namespace nether