#pragma once

/*
 * NetherGL - OpenGL abstraction layer with optional error checking
 * 
 * GL Error Checking Feature:
 * To enable automatic GL error checking on each call, define NETHER_GL_ERROR_CHECKING:
 * 
 * Option 1: Uncomment the line below
 * Option 2: Add -DNETHER_GL_ERROR_CHECKING to your compiler flags
 * Option 3: Define it in your build system (CMake, etc.)
 * 
 * When enabled, every nether::gl:: function call will automatically check for 
 * OpenGL errors and print them to stderr in the format:
 * [NETHER GL ERROR] <function_name> - <error_description>
 * 
 * Example output:
 * [NETHER GL ERROR] bindTexture - GL_INVALID_ENUM
 * 
 * Note: This adds a glGetError() call after each GL function, which can impact 
 * performance, so it's recommended to only enable during development/debugging.
 */

// Define to enable GL error checking on each call
// Uncomment the line below to enable GL error checking
// #define NETHER_GL_ERROR_CHECKING

#ifdef AETHER_USE_GLAD
#include <glad/gl.h>
#elif AETHER_USE_QT
#include <QOpenGLFunctions>
#include <QOpenGLContext>
#include <QOpenGLExtraFunctions>
#endif

// Include headers needed for error checking
#ifdef NETHER_GL_ERROR_CHECKING
#include <iostream>
#include <string>
#endif

namespace nether {
namespace gl {

// Forward declaration needed for error checking
class OpenGLFunctions;
extern OpenGLFunctions* g_gl;

// OpenGL function abstraction interface
class OpenGLFunctions {
public:
    virtual ~OpenGLFunctions() = default;
    
    // Shader functions
    virtual unsigned int CreateShader(unsigned int type) = 0;
    virtual void ShaderSource(unsigned int shader, int count, const char* const* string, const int* length) = 0;
    virtual void CompileShader(unsigned int shader) = 0;
    virtual void DeleteShader(unsigned int shader) = 0;
    virtual void GetShaderiv(unsigned int shader, unsigned int pname, int* params) = 0;
    virtual void GetShaderInfoLog(unsigned int shader, int bufSize, int* length, char* infoLog) = 0;
    
    // Program functions
    virtual unsigned int CreateProgram() = 0;
    virtual void AttachShader(unsigned int program, unsigned int shader) = 0;
    virtual void LinkProgram(unsigned int program) = 0;
    virtual void UseProgram(unsigned int program) = 0;
    virtual void DeleteProgram(unsigned int program) = 0;
    virtual void GetProgramiv(unsigned int program, unsigned int pname, int* params) = 0;
    virtual void GetProgramInfoLog(unsigned int program, int bufSize, int* length, char* infoLog) = 0;
    virtual int GetUniformLocation(unsigned int program, const char* name) = 0;
    virtual int GetAttribLocation(unsigned int program, const char* name) = 0;
    
    // Buffer functions
    virtual void GenBuffers(int n, unsigned int* buffers) = 0;
    virtual void BindBuffer(unsigned int target, unsigned int buffer) = 0;
    virtual void BufferData(unsigned int target, long long size, const void* data, unsigned int usage) = 0;
    virtual void DeleteBuffers(int n, const unsigned int* buffers) = 0;
    
    // Vertex Array functions
    virtual void GenVertexArrays(int n, unsigned int* arrays) = 0;
    virtual void BindVertexArray(unsigned int array) = 0;
    virtual void DeleteVertexArrays(int n, const unsigned int* arrays) = 0;
    virtual void EnableVertexAttribArray(unsigned int index) = 0;
    virtual void VertexAttribPointer(unsigned int index, int size, unsigned int type, unsigned char normalized, int stride, const void* pointer) = 0;
    
    // Texture functions
    virtual void GenTextures(int n, unsigned int* textures) = 0;
    virtual void BindTexture(unsigned int target, unsigned int texture) = 0;
    virtual void TexImage2D(unsigned int target, int level, int internalformat, int width, int height, int border, unsigned int format, unsigned int type, const void* pixels) = 0;
    virtual void TexParameteri(unsigned int target, unsigned int pname, int param) = 0;
    virtual void DeleteTextures(int n, const unsigned int* textures) = 0;
    virtual void ActiveTexture(unsigned int texture) = 0;
    virtual void GenerateMipmap(unsigned int target) = 0;
    virtual void GetTexLevelParameteriv(unsigned int target, int level, unsigned int pname, int* params) = 0;
    
    // Uniform functions
    virtual void Uniform1i(int location, int v0) = 0;
    virtual void Uniform1f(int location, float v0) = 0;
    virtual void Uniform2f(int location, float v0, float v1) = 0;
    virtual void Uniform3f(int location, float v0, float v1, float v2) = 0;
    virtual void Uniform4f(int location, float v0, float v1, float v2, float v3) = 0;
    virtual void UniformMatrix4fv(int location, int count, unsigned char transpose, const float* value) = 0;
    
    // Drawing functions
    virtual void DrawElements(unsigned int mode, int count, unsigned int type, const void* indices) = 0;
    virtual void DrawArrays(unsigned int mode, int first, int count) = 0;
    
    // State functions
    virtual void Enable(unsigned int cap) = 0;
    virtual void Disable(unsigned int cap) = 0;
    virtual void BlendFunc(unsigned int sfactor, unsigned int dfactor) = 0;
    virtual void DepthFunc(unsigned int func) = 0;
    virtual void CullFace(unsigned int mode) = 0;
    virtual void Clear(unsigned int mask) = 0;
    virtual void ClearColor(float red, float green, float blue, float alpha) = 0;
    virtual void Viewport(int x, int y, int width, int height) = 0;
    virtual void PolygonMode(unsigned int face, unsigned int mode) = 0;
    
    // Error checking
    virtual unsigned int GetError() = 0;
};

#ifdef NETHER_GL_ERROR_CHECKING
// GL error checking utility function - now defined after OpenGLFunctions class
inline void checkGLError(const char* functionName) {
    unsigned int error = g_gl->GetError();
    if (error != 0x0000) { // GL_NO_ERROR = 0x0000
        std::string errorString;
        switch (error) {
            case 0x0500: // GL_INVALID_ENUM
                errorString = "GL_INVALID_ENUM";
                break;
            case 0x0501: // GL_INVALID_VALUE
                errorString = "GL_INVALID_VALUE";
                break;
            case 0x0502: // GL_INVALID_OPERATION
                errorString = "GL_INVALID_OPERATION";
                break;
            case 0x0503: // GL_STACK_OVERFLOW (deprecated in core profile)
                errorString = "GL_STACK_OVERFLOW";
                break;
            case 0x0504: // GL_STACK_UNDERFLOW (deprecated in core profile)
                errorString = "GL_STACK_UNDERFLOW";
                break;
            case 0x0505: // GL_OUT_OF_MEMORY
                errorString = "GL_OUT_OF_MEMORY";
                break;
            case 0x0506: // GL_INVALID_FRAMEBUFFER_OPERATION
                errorString = "GL_INVALID_FRAMEBUFFER_OPERATION";
                break;
            case 0x0507: // GL_CONTEXT_LOST
                errorString = "GL_CONTEXT_LOST";
                break;
            default:
                errorString = "UNKNOWN_GL_ERROR (0x" + std::to_string(error) + ")";
                break;
        }
        std::cerr << "[NETHER GL ERROR] " << functionName << " - " << errorString << std::endl;
    }
}

#define NETHER_GL_CHECK(call) do { call; nether::gl::checkGLError(#call); } while(0)
#else
#define NETHER_GL_CHECK(call) call
#endif

#ifdef AETHER_USE_GLAD
// Direct OpenGL implementation using GLAD
class DirectOpenGLFunctions : public OpenGLFunctions {
public:
    // Shader functions
    unsigned int CreateShader(unsigned int type) override { return glCreateShader(type); }
    void ShaderSource(unsigned int shader, int count, const char* const* string, const int* length) override { glShaderSource(shader, count, string, length); }
    void CompileShader(unsigned int shader) override { glCompileShader(shader); }
    void DeleteShader(unsigned int shader) override { glDeleteShader(shader); }
    void GetShaderiv(unsigned int shader, unsigned int pname, int* params) override { glGetShaderiv(shader, pname, params); }
    void GetShaderInfoLog(unsigned int shader, int bufSize, int* length, char* infoLog) override { glGetShaderInfoLog(shader, bufSize, length, infoLog); }
    
    // Program functions
    unsigned int CreateProgram() override { return glCreateProgram(); }
    void AttachShader(unsigned int program, unsigned int shader) override { glAttachShader(program, shader); }
    void LinkProgram(unsigned int program) override { glLinkProgram(program); }
    void UseProgram(unsigned int program) override { glUseProgram(program); }
    void DeleteProgram(unsigned int program) override { glDeleteProgram(program); }
    void GetProgramiv(unsigned int program, unsigned int pname, int* params) override { glGetProgramiv(program, pname, params); }
    void GetProgramInfoLog(unsigned int program, int bufSize, int* length, char* infoLog) override { glGetProgramInfoLog(program, bufSize, length, infoLog); }
    int GetUniformLocation(unsigned int program, const char* name) override { return glGetUniformLocation(program, name); }
    int GetAttribLocation(unsigned int program, const char* name) override { return glGetAttribLocation(program, name); }
    
    // Buffer functions
    void GenBuffers(int n, unsigned int* buffers) override { glGenBuffers(n, buffers); }
    void BindBuffer(unsigned int target, unsigned int buffer) override { glBindBuffer(target, buffer); }
    void BufferData(unsigned int target, long long size, const void* data, unsigned int usage) override { glBufferData(target, size, data, usage); }
    void DeleteBuffers(int n, const unsigned int* buffers) override { glDeleteBuffers(n, buffers); }
    
    // Vertex Array functions
    void GenVertexArrays(int n, unsigned int* arrays) override { glGenVertexArrays(n, arrays); }
    void BindVertexArray(unsigned int array) override { glBindVertexArray(array); }
    void DeleteVertexArrays(int n, const unsigned int* arrays) override { glDeleteVertexArrays(n, arrays); }
    void EnableVertexAttribArray(unsigned int index) override { glEnableVertexAttribArray(index); }
    void VertexAttribPointer(unsigned int index, int size, unsigned int type, unsigned char normalized, int stride, const void* pointer) override { 
        glVertexAttribPointer(index, size, type, normalized, stride, pointer); 
    }
    
    // Texture functions
    void GenTextures(int n, unsigned int* textures) override { glGenTextures(n, textures); }
    void BindTexture(unsigned int target, unsigned int texture) override { glBindTexture(target, texture); }
    void TexImage2D(unsigned int target, int level, int internalformat, int width, int height, int border, unsigned int format, unsigned int type, const void* pixels) override { 
        glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels); 
    }
    void TexParameteri(unsigned int target, unsigned int pname, int param) override { glTexParameteri(target, pname, param); }
    void DeleteTextures(int n, const unsigned int* textures) override { glDeleteTextures(n, textures); }
    void ActiveTexture(unsigned int texture) override { glActiveTexture(texture); }
    void GenerateMipmap(unsigned int target) override { glGenerateMipmap(target); }
    void GetTexLevelParameteriv(unsigned int target, int level, unsigned int pname, int* params) override { glGetTexLevelParameteriv(target, level, pname, params); }
    
    // Uniform functions
    void Uniform1i(int location, int v0) override { glUniform1i(location, v0); }
    void Uniform1f(int location, float v0) override { glUniform1f(location, v0); }
    void Uniform2f(int location, float v0, float v1) override { glUniform2f(location, v0, v1); }
    void Uniform3f(int location, float v0, float v1, float v2) override { glUniform3f(location, v0, v1, v2); }
    void Uniform4f(int location, float v0, float v1, float v2, float v3) override { glUniform4f(location, v0, v1, v2, v3); }
    void UniformMatrix4fv(int location, int count, unsigned char transpose, const float* value) override { glUniformMatrix4fv(location, count, transpose, value); }
    
    // Drawing functions
    void DrawElements(unsigned int mode, int count, unsigned int type, const void* indices) override { glDrawElements(mode, count, type, indices); }
    void DrawArrays(unsigned int mode, int first, int count) override { glDrawArrays(mode, first, count); }
    
    // State functions
    void Enable(unsigned int cap) override { glEnable(cap); }
    void Disable(unsigned int cap) override { glDisable(cap); }
    void BlendFunc(unsigned int sfactor, unsigned int dfactor) override { glBlendFunc(sfactor, dfactor); }
    void DepthFunc(unsigned int func) override { glDepthFunc(func); }
    void CullFace(unsigned int mode) override { glCullFace(mode); }
    void Clear(unsigned int mask) override { glClear(mask); }
    void ClearColor(float red, float green, float blue, float alpha) override { glClearColor(red, green, blue, alpha); }
    void Viewport(int x, int y, int width, int height) override { glViewport(x, y, width, height); }
    void PolygonMode(unsigned int face, unsigned int mode) override { glPolygonMode(face, mode); }
    
    // Error checking
    unsigned int GetError() override { return glGetError(); }
};
#endif

#ifdef AETHER_USE_QT
// Qt OpenGL implementation using QOpenGLExtraFunctions (OpenGL 4.0+ functions)
class QtOpenGLFunctions : public OpenGLFunctions {
private:
    QOpenGLExtraFunctions* m_gl;
    
public:
    QtOpenGLFunctions(QOpenGLContext* context) 
        : m_gl(context->extraFunctions())
    {
    }
    
    // Shader functions
    unsigned int CreateShader(unsigned int type) override { 
        return m_gl->glCreateShader(type); 
    }
    void ShaderSource(unsigned int shader, int count, const char* const* string, const int* length) override { 
        // Convert const char* const* to const char** for Qt compatibility
        const char** qtString = const_cast<const char**>(string);
        m_gl->glShaderSource(shader, count, qtString, length);
    }
    void CompileShader(unsigned int shader) override { 
        m_gl->glCompileShader(shader);
    }
    void DeleteShader(unsigned int shader) override { 
        m_gl->glDeleteShader(shader);
    }
    void GetShaderiv(unsigned int shader, unsigned int pname, int* params) override { 
        m_gl->glGetShaderiv(shader, pname, params);
    }
    void GetShaderInfoLog(unsigned int shader, int bufSize, int* length, char* infoLog) override { 
        m_gl->glGetShaderInfoLog(shader, bufSize, length, infoLog);
    }
    
    // Program functions
    unsigned int CreateProgram() override { 
        return m_gl->glCreateProgram();
    }
    void AttachShader(unsigned int program, unsigned int shader) override { 
        m_gl->glAttachShader(program, shader);
    }
    void LinkProgram(unsigned int program) override { 
        m_gl->glLinkProgram(program);
    }
    void UseProgram(unsigned int program) override { 
        m_gl->glUseProgram(program);
    }
    void DeleteProgram(unsigned int program) override { 
        m_gl->glDeleteProgram(program);
    }
    void GetProgramiv(unsigned int program, unsigned int pname, int* params) override { 
        m_gl->glGetProgramiv(program, pname, params);
    }
    void GetProgramInfoLog(unsigned int program, int bufSize, int* length, char* infoLog) override { 
        m_gl->glGetProgramInfoLog(program, bufSize, length, infoLog);
    }
    int GetUniformLocation(unsigned int program, const char* name) override { 
        return m_gl->glGetUniformLocation(program, name);
    }
    int GetAttribLocation(unsigned int program, const char* name) override { 
        return m_gl->glGetAttribLocation(program, name);
    }
    
    // Buffer functions
    void GenBuffers(int n, unsigned int* buffers) override { 
        m_gl->glGenBuffers(n, buffers);
    }
    void BindBuffer(unsigned int target, unsigned int buffer) override { 
        m_gl->glBindBuffer(target, buffer);
    }
    void BufferData(unsigned int target, long long size, const void* data, unsigned int usage) override { 
        m_gl->glBufferData(target, size, data, usage);
    }
    void DeleteBuffers(int n, const unsigned int* buffers) override { 
        m_gl->glDeleteBuffers(n, buffers);
    }
    
    // Vertex Array functions - QOpenGLExtraFunctions has VAO support
    void GenVertexArrays(int n, unsigned int* arrays) override { 
        m_gl->glGenVertexArrays(n, arrays);
    }
    void BindVertexArray(unsigned int array) override { 
        m_gl->glBindVertexArray(array);
    }
    void DeleteVertexArrays(int n, const unsigned int* arrays) override { 
        m_gl->glDeleteVertexArrays(n, arrays);
    }
    void EnableVertexAttribArray(unsigned int index) override { 
        m_gl->glEnableVertexAttribArray(index);
    }
    void VertexAttribPointer(unsigned int index, int size, unsigned int type, unsigned char normalized, int stride, const void* pointer) override { 
        m_gl->glVertexAttribPointer(index, size, type, normalized, stride, pointer);
    }
    
    // Texture functions
    void GenTextures(int n, unsigned int* textures) override { 
        m_gl->glGenTextures(n, textures);
    }
    void BindTexture(unsigned int target, unsigned int texture) override { 
        m_gl->glBindTexture(target, texture);
    }
    void TexImage2D(unsigned int target, int level, int internalformat, int width, int height, int border, unsigned int format, unsigned int type, const void* pixels) override { 
        m_gl->glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
    }
    void TexParameteri(unsigned int target, unsigned int pname, int param) override { 
        m_gl->glTexParameteri(target, pname, param);
    }
    void DeleteTextures(int n, const unsigned int* textures) override { 
        m_gl->glDeleteTextures(n, textures);
    }
    void ActiveTexture(unsigned int texture) override { 
        m_gl->glActiveTexture(texture);
    }
    void GenerateMipmap(unsigned int target) override { 
        m_gl->glGenerateMipmap(target);
    }
    void GetTexLevelParameteriv(unsigned int target, int level, unsigned int pname, int* params) override { 
        m_gl->glGetTexLevelParameteriv(target, level, pname, params);
    }
    
    // Uniform functions
    void Uniform1i(int location, int v0) override { 
        m_gl->glUniform1i(location, v0);
    }
    void Uniform1f(int location, float v0) override { 
        m_gl->glUniform1f(location, v0);
    }
    void Uniform2f(int location, float v0, float v1) override { 
        m_gl->glUniform2f(location, v0, v1);
    }
    void Uniform3f(int location, float v0, float v1, float v2) override { 
        m_gl->glUniform3f(location, v0, v1, v2);
    }
    void Uniform4f(int location, float v0, float v1, float v2, float v3) override { 
        m_gl->glUniform4f(location, v0, v1, v2, v3);
    }
    void UniformMatrix4fv(int location, int count, unsigned char transpose, const float* value) override { 
        m_gl->glUniformMatrix4fv(location, count, transpose, value);
    }
    
    // Drawing functions
    void DrawElements(unsigned int mode, int count, unsigned int type, const void* indices) override { 
        m_gl->glDrawElements(mode, count, type, indices);
    }
    void DrawArrays(unsigned int mode, int first, int count) override { 
        m_gl->glDrawArrays(mode, first, count);
    }
    
    // State functions
    void Enable(unsigned int cap) override { 
        m_gl->glEnable(cap);
    }
    void Disable(unsigned int cap) override { 
        m_gl->glDisable(cap);
    }
    void BlendFunc(unsigned int sfactor, unsigned int dfactor) override { 
        m_gl->glBlendFunc(sfactor, dfactor);
    }
    void DepthFunc(unsigned int func) override { 
        m_gl->glDepthFunc(func);
    }
    void CullFace(unsigned int mode) override { 
        m_gl->glCullFace(mode);
    }
    void Clear(unsigned int mask) override { 
        m_gl->glClear(mask);
    }
    void ClearColor(float red, float green, float blue, float alpha) override { 
        m_gl->glClearColor(red, green, blue, alpha);
    }
    void Viewport(int x, int y, int width, int height) override { 
        m_gl->glViewport(x, y, width, height);
    }
    void PolygonMode(unsigned int face, unsigned int mode) override { 
        // QOpenGLExtraFunctions should have polygon mode support
        // m_gl->glPolygonMode(face, mode);
    }
    
    // Error checking
    unsigned int GetError() override { 
        return m_gl->glGetError();
    }
};
#endif

// Global OpenGL function pointer - to be set by the application
extern OpenGLFunctions* g_gl;

// Convenience functions that use the global function pointer - now with optional error checking
inline unsigned int createShader(unsigned int type) { 
    unsigned int result = g_gl->CreateShader(type);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("createShader");
#endif
    return result;
}

inline void shaderSource(unsigned int shader, int count, const char* const* string, const int* length) { 
    g_gl->ShaderSource(shader, count, string, length);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("shaderSource");
#endif
}

inline void compileShader(unsigned int shader) { 
    g_gl->CompileShader(shader);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("compileShader");
#endif
}

inline void deleteShader(unsigned int shader) { 
    g_gl->DeleteShader(shader);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("deleteShader");
#endif
}

inline void getShaderiv(unsigned int shader, unsigned int pname, int* params) { 
    g_gl->GetShaderiv(shader, pname, params);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("getShaderiv");
#endif
}

inline void getShaderInfoLog(unsigned int shader, int bufSize, int* length, char* infoLog) { 
    g_gl->GetShaderInfoLog(shader, bufSize, length, infoLog);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("getShaderInfoLog");
#endif
}

inline unsigned int createProgram() { 
    unsigned int result = g_gl->CreateProgram();
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("createProgram");
#endif
    return result;
}

inline void attachShader(unsigned int program, unsigned int shader) { 
    g_gl->AttachShader(program, shader);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("attachShader");
#endif
}

inline void linkProgram(unsigned int program) { 
    g_gl->LinkProgram(program);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("linkProgram");
#endif
}

inline void useProgram(unsigned int program) { 
    g_gl->UseProgram(program);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("useProgram");
#endif
}

inline void deleteProgram(unsigned int program) { 
    g_gl->DeleteProgram(program);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("deleteProgram");
#endif
}

inline void getProgramiv(unsigned int program, unsigned int pname, int* params) { 
    g_gl->GetProgramiv(program, pname, params);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("getProgramiv");
#endif
}

inline void getProgramInfoLog(unsigned int program, int bufSize, int* length, char* infoLog) { 
    g_gl->GetProgramInfoLog(program, bufSize, length, infoLog);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("getProgramInfoLog");
#endif
}

inline int getUniformLocation(unsigned int program, const char* name) { 
    int result = g_gl->GetUniformLocation(program, name);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("getUniformLocation");
#endif
    return result;
}

inline int getAttribLocation(unsigned int program, const char* name) { 
    int result = g_gl->GetAttribLocation(program, name);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("getAttribLocation");
#endif
    return result;
}

inline void genBuffers(int n, unsigned int* buffers) { 
    g_gl->GenBuffers(n, buffers);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("genBuffers");
#endif
}

inline void bindBuffer(unsigned int target, unsigned int buffer) { 
    g_gl->BindBuffer(target, buffer);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("bindBuffer");
#endif
}

inline void bufferData(unsigned int target, long long size, const void* data, unsigned int usage) { 
    g_gl->BufferData(target, size, data, usage);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("bufferData");
#endif
}

inline void deleteBuffers(int n, const unsigned int* buffers) { 
    g_gl->DeleteBuffers(n, buffers);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("deleteBuffers");
#endif
}

inline void genVertexArrays(int n, unsigned int* arrays) { 
    g_gl->GenVertexArrays(n, arrays);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("genVertexArrays");
#endif
}

inline void bindVertexArray(unsigned int array) { 
    g_gl->BindVertexArray(array);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("bindVertexArray");
#endif
}

inline void deleteVertexArrays(int n, const unsigned int* arrays) { 
    g_gl->DeleteVertexArrays(n, arrays);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("deleteVertexArrays");
#endif
}

inline void enableVertexAttribArray(unsigned int index) { 
    g_gl->EnableVertexAttribArray(index);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("enableVertexAttribArray");
#endif
}

inline void vertexAttribPointer(unsigned int index, int size, unsigned int type, unsigned char normalized, int stride, const void* pointer) { 
    g_gl->VertexAttribPointer(index, size, type, normalized, stride, pointer); 
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("vertexAttribPointer");
#endif
}

inline void genTextures(int n, unsigned int* textures) { 
    g_gl->GenTextures(n, textures);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("genTextures");
#endif
}

inline void bindTexture(unsigned int target, unsigned int texture) { 
    g_gl->BindTexture(target, texture);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("bindTexture");
#endif
}

inline void texImage2D(unsigned int target, int level, int internalformat, int width, int height, int border, unsigned int format, unsigned int type, const void* pixels) { 
    g_gl->TexImage2D(target, level, internalformat, width, height, border, format, type, pixels); 
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("texImage2D");
#endif
}

inline void texParameteri(unsigned int target, unsigned int pname, int param) { 
    g_gl->TexParameteri(target, pname, param);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("texParameteri");
#endif
}

inline void deleteTextures(int n, const unsigned int* textures) { 
    g_gl->DeleteTextures(n, textures);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("deleteTextures");
#endif
}

inline void activeTexture(unsigned int texture) { 
    g_gl->ActiveTexture(texture);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("activeTexture");
#endif
}

inline void generateMipmap(unsigned int target) { 
    g_gl->GenerateMipmap(target);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("generateMipmap");
#endif
}

inline void getTexLevelParameteriv(unsigned int target, int level, unsigned int pname, int* params) { 
    g_gl->GetTexLevelParameteriv(target, level, pname, params);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("getTexLevelParameteriv");
#endif
}

inline void uniform1i(int location, int v0) { 
    g_gl->Uniform1i(location, v0);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("uniform1i");
#endif
}

inline void uniform1f(int location, float v0) { 
    g_gl->Uniform1f(location, v0);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("uniform1f");
#endif
}

inline void uniform2f(int location, float v0, float v1) { 
    g_gl->Uniform2f(location, v0, v1);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("uniform2f");
#endif
}

inline void uniform3f(int location, float v0, float v1, float v2) { 
    g_gl->Uniform3f(location, v0, v1, v2);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("uniform3f");
#endif
}

inline void uniform4f(int location, float v0, float v1, float v2, float v3) { 
    g_gl->Uniform4f(location, v0, v1, v2, v3);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("uniform4f");
#endif
}

inline void uniformMatrix4fv(int location, int count, unsigned char transpose, const float* value) { 
    g_gl->UniformMatrix4fv(location, count, transpose, value);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("uniformMatrix4fv");
#endif
}

inline void drawElements(unsigned int mode, int count, unsigned int type, const void* indices) { 
    g_gl->DrawElements(mode, count, type, indices);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("drawElements");
#endif
}

inline void drawArrays(unsigned int mode, int first, int count) { 
    g_gl->DrawArrays(mode, first, count);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("drawArrays");
#endif
}

inline void enable(unsigned int cap) { 
    g_gl->Enable(cap);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("enable");
#endif
}

inline void disable(unsigned int cap) { 
    g_gl->Disable(cap);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("disable");
#endif
}

inline void blendFunc(unsigned int sfactor, unsigned int dfactor) { 
    g_gl->BlendFunc(sfactor, dfactor);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("blendFunc");
#endif
}

inline void depthFunc(unsigned int func) { 
    g_gl->DepthFunc(func);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("depthFunc");
#endif
}

inline void cullFace(unsigned int mode) { 
    g_gl->CullFace(mode);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("cullFace");
#endif
}

inline void clear(unsigned int mask) { 
    g_gl->Clear(mask);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("clear");
#endif
}

inline void clearColor(float red, float green, float blue, float alpha) { 
    g_gl->ClearColor(red, green, blue, alpha);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("clearColor");
#endif
}

inline void viewport(int x, int y, int width, int height) { 
    g_gl->Viewport(x, y, width, height);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("viewport");
#endif
}

inline void polygonMode(unsigned int face, unsigned int mode) { 
    g_gl->PolygonMode(face, mode);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("polygonMode");
#endif
}

inline unsigned int getError() { 
    return g_gl->GetError();
    // Note: We don't check for errors on getError() itself to avoid infinite recursion
}

// Initialization functions
void initializeDirectGL();
#ifdef AETHER_USE_QT
void initializeQtGL(QOpenGLContext* context);
#endif

} // namespace gl
} // namespace nether
