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
    virtual void ClearDepth(double depth) = 0;
    virtual void ClearStencil(int stencil) = 0;
    virtual void Viewport(int x, int y, int width, int height) = 0;
    virtual void PolygonMode(unsigned int face, unsigned int mode) = 0;
    
    // Error checking
    virtual unsigned int GetError() = 0;
    
    // OpenGL 4.0+ Core Functions
    
    // Framebuffer functions
    virtual void GenFramebuffers(int n, unsigned int* framebuffers) = 0;
    virtual void BindFramebuffer(unsigned int target, unsigned int framebuffer) = 0;
    virtual void DeleteFramebuffers(int n, const unsigned int* framebuffers) = 0;
    virtual void FramebufferTexture2D(unsigned int target, unsigned int attachment, unsigned int textarget, unsigned int texture, int level) = 0;
    virtual void GenRenderbuffers(int n, unsigned int* renderbuffers) = 0;
    virtual void BindRenderbuffer(unsigned int target, unsigned int renderbuffer) = 0;
    virtual void DeleteRenderbuffers(int n, const unsigned int* renderbuffers) = 0;
    virtual void RenderbufferStorage(unsigned int target, unsigned int internalformat, int width, int height) = 0;
    virtual void FramebufferRenderbuffer(unsigned int target, unsigned int attachment, unsigned int renderbuffertarget, unsigned int renderbuffer) = 0;
    virtual unsigned int CheckFramebufferStatus(unsigned int target) = 0;
    virtual void DrawBuffers(int n, const unsigned int* bufs) = 0;
    virtual void ReadBuffer(unsigned int mode) = 0;
    virtual void BlitFramebuffer(int srcX0, int srcY0, int srcX1, int srcY1, int dstX0, int dstY0, int dstX1, int dstY1, unsigned int mask, unsigned int filter) = 0;
    
    // Advanced texture functions
    virtual void TexImage3D(unsigned int target, int level, int internalformat, int width, int height, int depth, int border, unsigned int format, unsigned int type, const void* pixels) = 0;
    virtual void TexSubImage2D(unsigned int target, int level, int xoffset, int yoffset, int width, int height, unsigned int format, unsigned int type, const void* pixels) = 0;
    virtual void TexSubImage3D(unsigned int target, int level, int xoffset, int yoffset, int zoffset, int width, int height, int depth, unsigned int format, unsigned int type, const void* pixels) = 0;
    virtual void CompressedTexImage2D(unsigned int target, int level, unsigned int internalformat, int width, int height, int border, int imageSize, const void* data) = 0;
    virtual void CompressedTexSubImage2D(unsigned int target, int level, int xoffset, int yoffset, int width, int height, unsigned int format, int imageSize, const void* data) = 0;
    virtual void TexStorage2D(unsigned int target, int levels, unsigned int internalformat, int width, int height) = 0;
    virtual void TexStorage3D(unsigned int target, int levels, unsigned int internalformat, int width, int height, int depth) = 0;
    virtual void GetTexImage(unsigned int target, int level, unsigned int format, unsigned int type, void* pixels) = 0;
    virtual void CopyTexImage2D(unsigned int target, int level, unsigned int internalformat, int x, int y, int width, int height, int border) = 0;
    virtual void CopyTexSubImage2D(unsigned int target, int level, int xoffset, int yoffset, int x, int y, int width, int height) = 0;
    
    // Uniform buffer objects
    virtual void BindBufferBase(unsigned int target, unsigned int index, unsigned int buffer) = 0;
    virtual void BindBufferRange(unsigned int target, unsigned int index, unsigned int buffer, long long offset, long long size) = 0;
    virtual unsigned int GetUniformBlockIndex(unsigned int program, const char* uniformBlockName) = 0;
    virtual void UniformBlockBinding(unsigned int program, unsigned int uniformBlockIndex, unsigned int uniformBlockBinding) = 0;
    virtual void GetActiveUniformBlockiv(unsigned int program, unsigned int uniformBlockIndex, unsigned int pname, int* params) = 0;
    
    // Transform feedback
    virtual void GenTransformFeedbacks(int n, unsigned int* ids) = 0;
    virtual void BindTransformFeedback(unsigned int target, unsigned int id) = 0;
    virtual void DeleteTransformFeedbacks(int n, const unsigned int* ids) = 0;
    virtual void BeginTransformFeedback(unsigned int primitiveMode) = 0;
    virtual void EndTransformFeedback() = 0;
    virtual void TransformFeedbackVaryings(unsigned int program, int count, const char* const* varyings, unsigned int bufferMode) = 0;
    virtual void GetTransformFeedbackVarying(unsigned int program, unsigned int index, int bufSize, int* length, int* size, unsigned int* type, char* name) = 0;
    
    // Geometry shader and tessellation functions
    virtual void ProgramParameteri(unsigned int program, unsigned int pname, int value) = 0;
    virtual void PatchParameteri(unsigned int pname, int value) = 0;
    virtual void PatchParameterfv(unsigned int pname, const float* values) = 0;
    
    // Query objects
    virtual void GenQueries(int n, unsigned int* ids) = 0;
    virtual void DeleteQueries(int n, const unsigned int* ids) = 0;
    virtual void BeginQuery(unsigned int target, unsigned int id) = 0;
    virtual void EndQuery(unsigned int target) = 0;
    virtual void GetQueryObjectiv(unsigned int id, unsigned int pname, int* params) = 0;
    virtual void GetQueryObjectuiv(unsigned int id, unsigned int pname, unsigned int* params) = 0;
    virtual void QueryCounter(unsigned int id, unsigned int target) = 0;
    virtual void GetQueryObjecti64v(unsigned int id, unsigned int pname, long long* params) = 0;
    virtual void GetQueryObjectui64v(unsigned int id, unsigned int pname, unsigned long long* params) = 0;
    
    // Instanced rendering
    virtual void DrawArraysInstanced(unsigned int mode, int first, int count, int instancecount) = 0;
    virtual void DrawElementsInstanced(unsigned int mode, int count, unsigned int type, const void* indices, int instancecount) = 0;
    virtual void VertexAttribDivisor(unsigned int index, unsigned int divisor) = 0;
    
    // Advanced vertex attributes
    virtual void VertexAttribIPointer(unsigned int index, int size, unsigned int type, int stride, const void* pointer) = 0;
    virtual void VertexAttribLPointer(unsigned int index, int size, unsigned int type, int stride, const void* pointer) = 0;
    virtual void GetVertexAttribIiv(unsigned int index, unsigned int pname, int* params) = 0;
    virtual void GetVertexAttribIuiv(unsigned int index, unsigned int pname, unsigned int* params) = 0;
    
    // Multiple uniform functions
    virtual void Uniform1iv(int location, int count, const int* value) = 0;
    virtual void Uniform2iv(int location, int count, const int* value) = 0;
    virtual void Uniform3iv(int location, int count, const int* value) = 0;
    virtual void Uniform4iv(int location, int count, const int* value) = 0;
    virtual void Uniform1fv(int location, int count, const float* value) = 0;
    virtual void Uniform2fv(int location, int count, const float* value) = 0;
    virtual void Uniform3fv(int location, int count, const float* value) = 0;
    virtual void Uniform4fv(int location, int count, const float* value) = 0;
    virtual void Uniform1uiv(int location, int count, const unsigned int* value) = 0;
    virtual void Uniform2uiv(int location, int count, const unsigned int* value) = 0;
    virtual void Uniform3uiv(int location, int count, const unsigned int* value) = 0;
    virtual void Uniform4uiv(int location, int count, const unsigned int* value) = 0;
    virtual void UniformMatrix2fv(int location, int count, unsigned char transpose, const float* value) = 0;
    virtual void UniformMatrix3fv(int location, int count, unsigned char transpose, const float* value) = 0;
    virtual void UniformMatrix2x3fv(int location, int count, unsigned char transpose, const float* value) = 0;
    virtual void UniformMatrix3x2fv(int location, int count, unsigned char transpose, const float* value) = 0;
    virtual void UniformMatrix2x4fv(int location, int count, unsigned char transpose, const float* value) = 0;
    virtual void UniformMatrix4x2fv(int location, int count, unsigned char transpose, const float* value) = 0;
    virtual void UniformMatrix3x4fv(int location, int count, unsigned char transpose, const float* value) = 0;
    virtual void UniformMatrix4x3fv(int location, int count, unsigned char transpose, const float* value) = 0;
    
    // Texture sampler objects
    virtual void GenSamplers(int count, unsigned int* samplers) = 0;
    virtual void DeleteSamplers(int count, const unsigned int* samplers) = 0;
    virtual void BindSampler(unsigned int unit, unsigned int sampler) = 0;
    virtual void SamplerParameteri(unsigned int sampler, unsigned int pname, int param) = 0;
    virtual void SamplerParameterf(unsigned int sampler, unsigned int pname, float param) = 0;
    virtual void SamplerParameteriv(unsigned int sampler, unsigned int pname, const int* param) = 0;
    virtual void SamplerParameterfv(unsigned int sampler, unsigned int pname, const float* param) = 0;
    virtual void GetSamplerParameteriv(unsigned int sampler, unsigned int pname, int* params) = 0;
    virtual void GetSamplerParameterfv(unsigned int sampler, unsigned int pname, float* params) = 0;
    
    // Compute shaders (OpenGL 4.3+)
    virtual void DispatchCompute(unsigned int num_groups_x, unsigned int num_groups_y, unsigned int num_groups_z) = 0;
    virtual void DispatchComputeIndirect(long long indirect) = 0;
    virtual void MemoryBarrier(unsigned int barriers) = 0;
    
    // Shader storage buffer objects (OpenGL 4.3+)
    virtual void ShaderStorageBlockBinding(unsigned int program, unsigned int storageBlockIndex, unsigned int storageBlockBinding) = 0;
    
    // Multi-draw functions
    virtual void MultiDrawArrays(unsigned int mode, const int* first, const int* count, int drawcount) = 0;
    virtual void MultiDrawElements(unsigned int mode, const int* count, unsigned int type, const void* const* indices, int drawcount) = 0;
    virtual void MultiDrawArraysIndirect(unsigned int mode, const void* indirect, int drawcount, int stride) = 0;
    virtual void MultiDrawElementsIndirect(unsigned int mode, unsigned int type, const void* indirect, int drawcount, int stride) = 0;
    
    // Copy functions
    virtual void CopyBufferSubData(unsigned int readTarget, unsigned int writeTarget, long long readOffset, long long writeOffset, long long size) = 0;
    virtual void CopyImageSubData(unsigned int srcName, unsigned int srcTarget, int srcLevel, int srcX, int srcY, int srcZ, unsigned int dstName, unsigned int dstTarget, int dstLevel, int dstX, int dstY, int dstZ, int srcWidth, int srcHeight, int srcDepth) = 0;
    
    // Blend functions
    virtual void BlendEquation(unsigned int mode) = 0;
    virtual void BlendEquationSeparate(unsigned int modeRGB, unsigned int modeAlpha) = 0;
    virtual void BlendFuncSeparate(unsigned int sfactorRGB, unsigned int dfactorRGB, unsigned int sfactorAlpha, unsigned int dfactorAlpha) = 0;
    virtual void BlendColor(float red, float green, float blue, float alpha) = 0;
    
    // Stencil functions
    virtual void StencilFunc(unsigned int func, int ref, unsigned int mask) = 0;
    virtual void StencilFuncSeparate(unsigned int face, unsigned int func, int ref, unsigned int mask) = 0;
    virtual void StencilOp(unsigned int fail, unsigned int zfail, unsigned int zpass) = 0;
    virtual void StencilOpSeparate(unsigned int face, unsigned int sfail, unsigned int dpfail, unsigned int dppass) = 0;
    virtual void StencilMask(unsigned int mask) = 0;
    virtual void StencilMaskSeparate(unsigned int face, unsigned int mask) = 0;
    
    // Advanced buffer functions
    virtual void BufferSubData(unsigned int target, long long offset, long long size, const void* data) = 0;
    virtual void GetBufferSubData(unsigned int target, long long offset, long long size, void* data) = 0;
    virtual void* MapBuffer(unsigned int target, unsigned int access) = 0;
    virtual unsigned char UnmapBuffer(unsigned int target) = 0;
    virtual void* MapBufferRange(unsigned int target, long long offset, long long length, unsigned int access) = 0;
    virtual void FlushMappedBufferRange(unsigned int target, long long offset, long long length) = 0;
    
    // Debug functions (OpenGL 4.3+)
    virtual void DebugMessageControl(unsigned int source, unsigned int type, unsigned int severity, int count, const unsigned int* ids, unsigned char enabled) = 0;
    virtual void DebugMessageInsert(unsigned int source, unsigned int type, unsigned int id, unsigned int severity, int length, const char* buf) = 0;
    virtual void DebugMessageCallback(void* callback, const void* userParam) = 0;
    virtual unsigned int DebugMessageLog(unsigned int count, int bufSize, unsigned int* sources, unsigned int* types, unsigned int* ids, unsigned int* severities, int* lengths, char* messageLog) = 0;
    virtual void GetDebugMessageLog(unsigned int count, int bufSize, unsigned int* sources, unsigned int* types, unsigned int* ids, unsigned int* severities, int* lengths, char* messageLog) = 0;
    virtual void PushDebugGroup(unsigned int source, unsigned int id, int length, const char* message) = 0;
    virtual void PopDebugGroup() = 0;
    virtual void ObjectLabel(unsigned int identifier, unsigned int name, int length, const char* label) = 0;
    virtual void GetObjectLabel(unsigned int identifier, unsigned int name, int bufSize, int* length, char* label) = 0;
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
    void ClearDepth(double depth) override { glClearDepth(depth); }
    void ClearStencil(int stencil) override { glClearStencil(stencil); }
    void Viewport(int x, int y, int width, int height) override { glViewport(x, y, width, height); }
    void PolygonMode(unsigned int face, unsigned int mode) override { glPolygonMode(face, mode); }
    
    // Error checking
    unsigned int GetError() override { return glGetError(); }
    
    // OpenGL 4.0+ Core Functions - GLAD Implementation
    
    // Framebuffer functions
    void GenFramebuffers(int n, unsigned int* framebuffers) override { glGenFramebuffers(n, framebuffers); }
    void BindFramebuffer(unsigned int target, unsigned int framebuffer) override { glBindFramebuffer(target, framebuffer); }
    void DeleteFramebuffers(int n, const unsigned int* framebuffers) override { glDeleteFramebuffers(n, framebuffers); }
    void FramebufferTexture2D(unsigned int target, unsigned int attachment, unsigned int textarget, unsigned int texture, int level) override { glFramebufferTexture2D(target, attachment, textarget, texture, level); }
    void GenRenderbuffers(int n, unsigned int* renderbuffers) override { glGenRenderbuffers(n, renderbuffers); }
    void BindRenderbuffer(unsigned int target, unsigned int renderbuffer) override { glBindRenderbuffer(target, renderbuffer); }
    void DeleteRenderbuffers(int n, const unsigned int* renderbuffers) override { glDeleteRenderbuffers(n, renderbuffers); }
    void RenderbufferStorage(unsigned int target, unsigned int internalformat, int width, int height) override { glRenderbufferStorage(target, internalformat, width, height); }
    void FramebufferRenderbuffer(unsigned int target, unsigned int attachment, unsigned int renderbuffertarget, unsigned int renderbuffer) override { glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer); }
    unsigned int CheckFramebufferStatus(unsigned int target) override { return glCheckFramebufferStatus(target); }
    void DrawBuffers(int n, const unsigned int* bufs) override { glDrawBuffers(n, bufs); }
    void ReadBuffer(unsigned int mode) override { glReadBuffer(mode); }
    void BlitFramebuffer(int srcX0, int srcY0, int srcX1, int srcY1, int dstX0, int dstY0, int dstX1, int dstY1, unsigned int mask, unsigned int filter) override { glBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter); }
    
    // Advanced texture functions
    void TexImage3D(unsigned int target, int level, int internalformat, int width, int height, int depth, int border, unsigned int format, unsigned int type, const void* pixels) override { glTexImage3D(target, level, internalformat, width, height, depth, border, format, type, pixels); }
    void TexSubImage2D(unsigned int target, int level, int xoffset, int yoffset, int width, int height, unsigned int format, unsigned int type, const void* pixels) override { glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels); }
    void TexSubImage3D(unsigned int target, int level, int xoffset, int yoffset, int zoffset, int width, int height, int depth, unsigned int format, unsigned int type, const void* pixels) override { glTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels); }
    void CompressedTexImage2D(unsigned int target, int level, unsigned int internalformat, int width, int height, int border, int imageSize, const void* data) override { glCompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data); }
    void CompressedTexSubImage2D(unsigned int target, int level, int xoffset, int yoffset, int width, int height, unsigned int format, int imageSize, const void* data) override { glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data); }
    void TexStorage2D(unsigned int target, int levels, unsigned int internalformat, int width, int height) override { glTexStorage2D(target, levels, internalformat, width, height); }
    void TexStorage3D(unsigned int target, int levels, unsigned int internalformat, int width, int height, int depth) override { glTexStorage3D(target, levels, internalformat, width, height, depth); }
    void GetTexImage(unsigned int target, int level, unsigned int format, unsigned int type, void* pixels) override { glGetTexImage(target, level, format, type, pixels); }
    void CopyTexImage2D(unsigned int target, int level, unsigned int internalformat, int x, int y, int width, int height, int border) override { glCopyTexImage2D(target, level, internalformat, x, y, width, height, border); }
    void CopyTexSubImage2D(unsigned int target, int level, int xoffset, int yoffset, int x, int y, int width, int height) override { glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height); }
    
    // Uniform buffer objects
    void BindBufferBase(unsigned int target, unsigned int index, unsigned int buffer) override { glBindBufferBase(target, index, buffer); }
    void BindBufferRange(unsigned int target, unsigned int index, unsigned int buffer, long long offset, long long size) override { glBindBufferRange(target, index, buffer, offset, size); }
    unsigned int GetUniformBlockIndex(unsigned int program, const char* uniformBlockName) override { return glGetUniformBlockIndex(program, uniformBlockName); }
    void UniformBlockBinding(unsigned int program, unsigned int uniformBlockIndex, unsigned int uniformBlockBinding) override { glUniformBlockBinding(program, uniformBlockIndex, uniformBlockBinding); }
    void GetActiveUniformBlockiv(unsigned int program, unsigned int uniformBlockIndex, unsigned int pname, int* params) override { glGetActiveUniformBlockiv(program, uniformBlockIndex, pname, params); }
    
    // Transform feedback
    void GenTransformFeedbacks(int n, unsigned int* ids) override { glGenTransformFeedbacks(n, ids); }
    void BindTransformFeedback(unsigned int target, unsigned int id) override { glBindTransformFeedback(target, id); }
    void DeleteTransformFeedbacks(int n, const unsigned int* ids) override { glDeleteTransformFeedbacks(n, ids); }
    void BeginTransformFeedback(unsigned int primitiveMode) override { glBeginTransformFeedback(primitiveMode); }
    void EndTransformFeedback() override { glEndTransformFeedback(); }
    void TransformFeedbackVaryings(unsigned int program, int count, const char* const* varyings, unsigned int bufferMode) override { glTransformFeedbackVaryings(program, count, varyings, bufferMode); }
    void GetTransformFeedbackVarying(unsigned int program, unsigned int index, int bufSize, int* length, int* size, unsigned int* type, char* name) override { glGetTransformFeedbackVarying(program, index, bufSize, length, size, type, name); }
    
    // Geometry shader and tessellation functions
    void ProgramParameteri(unsigned int program, unsigned int pname, int value) override { glProgramParameteri(program, pname, value); }
    void PatchParameteri(unsigned int pname, int value) override { glPatchParameteri(pname, value); }
    void PatchParameterfv(unsigned int pname, const float* values) override { glPatchParameterfv(pname, values); }
    
    // Query objects
    void GenQueries(int n, unsigned int* ids) override { glGenQueries(n, ids); }
    void DeleteQueries(int n, const unsigned int* ids) override { glDeleteQueries(n, ids); }
    void BeginQuery(unsigned int target, unsigned int id) override { glBeginQuery(target, id); }
    void EndQuery(unsigned int target) override { glEndQuery(target); }
    void GetQueryObjectiv(unsigned int id, unsigned int pname, int* params) override { glGetQueryObjectiv(id, pname, params); }
    void GetQueryObjectuiv(unsigned int id, unsigned int pname, unsigned int* params) override { glGetQueryObjectuiv(id, pname, params); }
    void QueryCounter(unsigned int id, unsigned int target) override { glQueryCounter(id, target); }
    void GetQueryObjecti64v(unsigned int id, unsigned int pname, long long* params) override { glGetQueryObjecti64v(id, pname, params); }
    void GetQueryObjectui64v(unsigned int id, unsigned int pname, unsigned long long* params) override { glGetQueryObjectui64v(id, pname, params); }
    
    // Instanced rendering
    void DrawArraysInstanced(unsigned int mode, int first, int count, int instancecount) override { glDrawArraysInstanced(mode, first, count, instancecount); }
    void DrawElementsInstanced(unsigned int mode, int count, unsigned int type, const void* indices, int instancecount) override { glDrawElementsInstanced(mode, count, type, indices, instancecount); }
    void VertexAttribDivisor(unsigned int index, unsigned int divisor) override { glVertexAttribDivisor(index, divisor); }
    
    // Advanced vertex attributes
    void VertexAttribIPointer(unsigned int index, int size, unsigned int type, int stride, const void* pointer) override { glVertexAttribIPointer(index, size, type, stride, pointer); }
    void VertexAttribLPointer(unsigned int index, int size, unsigned int type, int stride, const void* pointer) override { glVertexAttribLPointer(index, size, type, stride, pointer); }
    void GetVertexAttribIiv(unsigned int index, unsigned int pname, int* params) override { glGetVertexAttribIiv(index, pname, params); }
    void GetVertexAttribIuiv(unsigned int index, unsigned int pname, unsigned int* params) override { glGetVertexAttribIuiv(index, pname, params); }
    
    // Multiple uniform functions
    void Uniform1iv(int location, int count, const int* value) override { glUniform1iv(location, count, value); }
    void Uniform2iv(int location, int count, const int* value) override { glUniform2iv(location, count, value); }
    void Uniform3iv(int location, int count, const int* value) override { glUniform3iv(location, count, value); }
    void Uniform4iv(int location, int count, const int* value) override { glUniform4iv(location, count, value); }
    void Uniform1fv(int location, int count, const float* value) override { glUniform1fv(location, count, value); }
    void Uniform2fv(int location, int count, const float* value) override { glUniform2fv(location, count, value); }
    void Uniform3fv(int location, int count, const float* value) override { glUniform3fv(location, count, value); }
    void Uniform4fv(int location, int count, const float* value) override { glUniform4fv(location, count, value); }
    void Uniform1uiv(int location, int count, const unsigned int* value) override { glUniform1uiv(location, count, value); }
    void Uniform2uiv(int location, int count, const unsigned int* value) override { glUniform2uiv(location, count, value); }
    void Uniform3uiv(int location, int count, const unsigned int* value) override { glUniform3uiv(location, count, value); }
    void Uniform4uiv(int location, int count, const unsigned int* value) override { glUniform4uiv(location, count, value); }
    void UniformMatrix2fv(int location, int count, unsigned char transpose, const float* value) override { glUniformMatrix2fv(location, count, transpose, value); }
    void UniformMatrix3fv(int location, int count, unsigned char transpose, const float* value) override { glUniformMatrix3fv(location, count, transpose, value); }
    void UniformMatrix2x3fv(int location, int count, unsigned char transpose, const float* value) override { glUniformMatrix2x3fv(location, count, transpose, value); }
    void UniformMatrix3x2fv(int location, int count, unsigned char transpose, const float* value) override { glUniformMatrix3x2fv(location, count, transpose, value); }
    void UniformMatrix2x4fv(int location, int count, unsigned char transpose, const float* value) override { glUniformMatrix2x4fv(location, count, transpose, value); }
    void UniformMatrix4x2fv(int location, int count, unsigned char transpose, const float* value) override { glUniformMatrix4x2fv(location, count, transpose, value); }
    void UniformMatrix3x4fv(int location, int count, unsigned char transpose, const float* value) override { glUniformMatrix3x4fv(location, count, transpose, value); }
    void UniformMatrix4x3fv(int location, int count, unsigned char transpose, const float* value) override { glUniformMatrix4x3fv(location, count, transpose, value); }
    
    // Texture sampler objects
    void GenSamplers(int count, unsigned int* samplers) override { glGenSamplers(count, samplers); }
    void DeleteSamplers(int count, const unsigned int* samplers) override { glDeleteSamplers(count, samplers); }
    void BindSampler(unsigned int unit, unsigned int sampler) override { glBindSampler(unit, sampler); }
    void SamplerParameteri(unsigned int sampler, unsigned int pname, int param) override { glSamplerParameteri(sampler, pname, param); }
    void SamplerParameterf(unsigned int sampler, unsigned int pname, float param) override { glSamplerParameterf(sampler, pname, param); }
    void SamplerParameteriv(unsigned int sampler, unsigned int pname, const int* param) override { glSamplerParameteriv(sampler, pname, param); }
    void SamplerParameterfv(unsigned int sampler, unsigned int pname, const float* param) override { glSamplerParameterfv(sampler, pname, param); }
    void GetSamplerParameteriv(unsigned int sampler, unsigned int pname, int* params) override { glGetSamplerParameteriv(sampler, pname, params); }
    void GetSamplerParameterfv(unsigned int sampler, unsigned int pname, float* params) override { glGetSamplerParameterfv(sampler, pname, params); }
    
    // Compute shaders (OpenGL 4.3+)
    void DispatchCompute(unsigned int num_groups_x, unsigned int num_groups_y, unsigned int num_groups_z) override { glDispatchCompute(num_groups_x, num_groups_y, num_groups_z); }
    void DispatchComputeIndirect(long long indirect) override { glDispatchComputeIndirect(indirect); }
    void MemoryBarrier(unsigned int barriers) override { glMemoryBarrier(barriers); }
    
    // Shader storage buffer objects (OpenGL 4.3+)
    void ShaderStorageBlockBinding(unsigned int program, unsigned int storageBlockIndex, unsigned int storageBlockBinding) override { glShaderStorageBlockBinding(program, storageBlockIndex, storageBlockBinding); }
    
    // Multi-draw functions
    void MultiDrawArrays(unsigned int mode, const int* first, const int* count, int drawcount) override { glMultiDrawArrays(mode, first, count, drawcount); }
    void MultiDrawElements(unsigned int mode, const int* count, unsigned int type, const void* const* indices, int drawcount) override { glMultiDrawElements(mode, count, type, indices, drawcount); }
    void MultiDrawArraysIndirect(unsigned int mode, const void* indirect, int drawcount, int stride) override { glMultiDrawArraysIndirect(mode, indirect, drawcount, stride); }
    void MultiDrawElementsIndirect(unsigned int mode, unsigned int type, const void* indirect, int drawcount, int stride) override { glMultiDrawElementsIndirect(mode, type, indirect, drawcount, stride); }
    
    // Copy functions
    void CopyBufferSubData(unsigned int readTarget, unsigned int writeTarget, long long readOffset, long long writeOffset, long long size) override { glCopyBufferSubData(readTarget, writeTarget, readOffset, writeOffset, size); }
    void CopyImageSubData(unsigned int srcName, unsigned int srcTarget, int srcLevel, int srcX, int srcY, int srcZ, unsigned int dstName, unsigned int dstTarget, int dstLevel, int dstX, int dstY, int dstZ, int srcWidth, int srcHeight, int srcDepth) override { glCopyImageSubData(srcName, srcTarget, srcLevel, srcX, srcY, srcZ, dstName, dstTarget, dstLevel, dstX, dstY, dstZ, srcWidth, srcHeight, srcDepth); }
    
    // Blend functions
    void BlendEquation(unsigned int mode) override { glBlendEquation(mode); }
    void BlendEquationSeparate(unsigned int modeRGB, unsigned int modeAlpha) override { glBlendEquationSeparate(modeRGB, modeAlpha); }
    void BlendFuncSeparate(unsigned int sfactorRGB, unsigned int dfactorRGB, unsigned int sfactorAlpha, unsigned int dfactorAlpha) override { glBlendFuncSeparate(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha); }
    void BlendColor(float red, float green, float blue, float alpha) override { glBlendColor(red, green, blue, alpha); }
    
    // Stencil functions
    void StencilFunc(unsigned int func, int ref, unsigned int mask) override { glStencilFunc(func, ref, mask); }
    void StencilFuncSeparate(unsigned int face, unsigned int func, int ref, unsigned int mask) override { glStencilFuncSeparate(face, func, ref, mask); }
    void StencilOp(unsigned int fail, unsigned int zfail, unsigned int zpass) override { glStencilOp(fail, zfail, zpass); }
    void StencilOpSeparate(unsigned int face, unsigned int sfail, unsigned int dpfail, unsigned int dppass) override { glStencilOpSeparate(face, sfail, dpfail, dppass); }
    void StencilMask(unsigned int mask) override { glStencilMask(mask); }
    void StencilMaskSeparate(unsigned int face, unsigned int mask) override { glStencilMaskSeparate(face, mask); }
    
    // Advanced buffer functions
    void BufferSubData(unsigned int target, long long offset, long long size, const void* data) override { glBufferSubData(target, offset, size, data); }
    void GetBufferSubData(unsigned int target, long long offset, long long size, void* data) override { glGetBufferSubData(target, offset, size, data); }
    void* MapBuffer(unsigned int target, unsigned int access) override { return glMapBuffer(target, access); }
    unsigned char UnmapBuffer(unsigned int target) override { return glUnmapBuffer(target); }
    void* MapBufferRange(unsigned int target, long long offset, long long length, unsigned int access) override { return glMapBufferRange(target, offset, length, access); }
    void FlushMappedBufferRange(unsigned int target, long long offset, long long length) override { glFlushMappedBufferRange(target, offset, length); }
    
    // Debug functions (OpenGL 4.3+)
    void DebugMessageControl(unsigned int source, unsigned int type, unsigned int severity, int count, const unsigned int* ids, unsigned char enabled) override { glDebugMessageControl(source, type, severity, count, ids, enabled); }
    void DebugMessageInsert(unsigned int source, unsigned int type, unsigned int id, unsigned int severity, int length, const char* buf) override { glDebugMessageInsert(source, type, id, severity, length, buf); }
    void DebugMessageCallback(void* callback, const void* userParam) override { glDebugMessageCallback((GLDEBUGPROC)callback, userParam); }
    unsigned int DebugMessageLog(unsigned int count, int bufSize, unsigned int* sources, unsigned int* types, unsigned int* ids, unsigned int* severities, int* lengths, char* messageLog) override { return glGetDebugMessageLog(count, bufSize, sources, types, ids, severities, lengths, messageLog); }
    void GetDebugMessageLog(unsigned int count, int bufSize, unsigned int* sources, unsigned int* types, unsigned int* ids, unsigned int* severities, int* lengths, char* messageLog) override { glGetDebugMessageLog(count, bufSize, sources, types, ids, severities, lengths, messageLog); }
    void PushDebugGroup(unsigned int source, unsigned int id, int length, const char* message) override { glPushDebugGroup(source, id, length, message); }
    void PopDebugGroup() override { glPopDebugGroup(); }
    void ObjectLabel(unsigned int identifier, unsigned int name, int length, const char* label) override { glObjectLabel(identifier, name, length, label); }
    void GetObjectLabel(unsigned int identifier, unsigned int name, int bufSize, int* length, char* label) override { glGetObjectLabel(identifier, name, bufSize, length, label); }
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
    
    // OpenGL 4.0+ Core Functions - Qt Implementation
    
    // Framebuffer functions
    void GenFramebuffers(int n, unsigned int* framebuffers) override { 
        m_gl->glGenFramebuffers(n, framebuffers);
    }
    void BindFramebuffer(unsigned int target, unsigned int framebuffer) override { 
        m_gl->glBindFramebuffer(target, framebuffer);
    }
    void DeleteFramebuffers(int n, const unsigned int* framebuffers) override { 
        m_gl->glDeleteFramebuffers(n, framebuffers);
    }
    void FramebufferTexture2D(unsigned int target, unsigned int attachment, unsigned int textarget, unsigned int texture, int level) override { 
        m_gl->glFramebufferTexture2D(target, attachment, textarget, texture, level);
    }
    void GenRenderbuffers(int n, unsigned int* renderbuffers) override { 
        m_gl->glGenRenderbuffers(n, renderbuffers);
    }
    void BindRenderbuffer(unsigned int target, unsigned int renderbuffer) override { 
        m_gl->glBindRenderbuffer(target, renderbuffer);
    }
    void DeleteRenderbuffers(int n, const unsigned int* renderbuffers) override { 
        m_gl->glDeleteRenderbuffers(n, renderbuffers);
    }
    void RenderbufferStorage(unsigned int target, unsigned int internalformat, int width, int height) override { 
        m_gl->glRenderbufferStorage(target, internalformat, width, height);
    }
    void FramebufferRenderbuffer(unsigned int target, unsigned int attachment, unsigned int renderbuffertarget, unsigned int renderbuffer) override { 
        m_gl->glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
    }
    unsigned int CheckFramebufferStatus(unsigned int target) override { 
        return m_gl->glCheckFramebufferStatus(target);
    }
    void DrawBuffers(int n, const unsigned int* bufs) override { 
        m_gl->glDrawBuffers(n, bufs);
    }
    void ReadBuffer(unsigned int mode) override { 
        m_gl->glReadBuffer(mode);
    }
    void BlitFramebuffer(int srcX0, int srcY0, int srcX1, int srcY1, int dstX0, int dstY0, int dstX1, int dstY1, unsigned int mask, unsigned int filter) override { 
        m_gl->glBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
    }
    
    // Advanced texture functions
    void TexImage3D(unsigned int target, int level, int internalformat, int width, int height, int depth, int border, unsigned int format, unsigned int type, const void* pixels) override { 
        m_gl->glTexImage3D(target, level, internalformat, width, height, depth, border, format, type, pixels);
    }
    void TexSubImage2D(unsigned int target, int level, int xoffset, int yoffset, int width, int height, unsigned int format, unsigned int type, const void* pixels) override { 
        m_gl->glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
    }
    void TexSubImage3D(unsigned int target, int level, int xoffset, int yoffset, int zoffset, int width, int height, int depth, unsigned int format, unsigned int type, const void* pixels) override { 
        m_gl->glTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
    }
    void CompressedTexImage2D(unsigned int target, int level, unsigned int internalformat, int width, int height, int border, int imageSize, const void* data) override { 
        m_gl->glCompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data);
    }
    void CompressedTexSubImage2D(unsigned int target, int level, int xoffset, int yoffset, int width, int height, unsigned int format, int imageSize, const void* data) override { 
        m_gl->glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data);
    }
    void TexStorage2D(unsigned int target, int levels, unsigned int internalformat, int width, int height) override { 
        m_gl->glTexStorage2D(target, levels, internalformat, width, height);
    }
    void TexStorage3D(unsigned int target, int levels, unsigned int internalformat, int width, int height, int depth) override { 
        m_gl->glTexStorage3D(target, levels, internalformat, width, height, depth);
    }
    void GetTexImage(unsigned int target, int level, unsigned int format, unsigned int type, void* pixels) override { 
        m_gl->glGetTexImage(target, level, format, type, pixels);
    }
    void CopyTexImage2D(unsigned int target, int level, unsigned int internalformat, int x, int y, int width, int height, int border) override { 
        m_gl->glCopyTexImage2D(target, level, internalformat, x, y, width, height, border);
    }
    void CopyTexSubImage2D(unsigned int target, int level, int xoffset, int yoffset, int x, int y, int width, int height) override { 
        m_gl->glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);
    }
    
    // Uniform buffer objects
    void BindBufferBase(unsigned int target, unsigned int index, unsigned int buffer) override { 
        m_gl->glBindBufferBase(target, index, buffer);
    }
    void BindBufferRange(unsigned int target, unsigned int index, unsigned int buffer, long long offset, long long size) override { 
        m_gl->glBindBufferRange(target, index, buffer, offset, size);
    }
    unsigned int GetUniformBlockIndex(unsigned int program, const char* uniformBlockName) override { 
        return m_gl->glGetUniformBlockIndex(program, uniformBlockName);
    }
    void UniformBlockBinding(unsigned int program, unsigned int uniformBlockIndex, unsigned int uniformBlockBinding) override { 
        m_gl->glUniformBlockBinding(program, uniformBlockIndex, uniformBlockBinding);
    }
    void GetActiveUniformBlockiv(unsigned int program, unsigned int uniformBlockIndex, unsigned int pname, int* params) override { 
        m_gl->glGetActiveUniformBlockiv(program, uniformBlockIndex, pname, params);
    }
    
    // Transform feedback
    void GenTransformFeedbacks(int n, unsigned int* ids) override { 
        m_gl->glGenTransformFeedbacks(n, ids);
    }
    void BindTransformFeedback(unsigned int target, unsigned int id) override { 
        m_gl->glBindTransformFeedback(target, id);
    }
    void DeleteTransformFeedbacks(int n, const unsigned int* ids) override { 
        m_gl->glDeleteTransformFeedbacks(n, ids);
    }
    void BeginTransformFeedback(unsigned int primitiveMode) override { 
        m_gl->glBeginTransformFeedback(primitiveMode);
    }
    void EndTransformFeedback() override { 
        m_gl->glEndTransformFeedback();
    }
    void TransformFeedbackVaryings(unsigned int program, int count, const char* const* varyings, unsigned int bufferMode) override { 
        // Convert const char* const* to const char** for Qt compatibility
        const char** qtVaryings = const_cast<const char**>(varyings);
        m_gl->glTransformFeedbackVaryings(program, count, qtVaryings, bufferMode);
    }
    void GetTransformFeedbackVarying(unsigned int program, unsigned int index, int bufSize, int* length, int* size, unsigned int* type, char* name) override { 
        m_gl->glGetTransformFeedbackVarying(program, index, bufSize, length, size, type, name);
    }
    
    // Geometry shader and tessellation functions
    void ProgramParameteri(unsigned int program, unsigned int pname, int value) override { 
        m_gl->glProgramParameteri(program, pname, value);
    }
    void PatchParameteri(unsigned int pname, int value) override { 
        m_gl->glPatchParameteri(pname, value);
    }
    void PatchParameterfv(unsigned int pname, const float* values) override { 
        m_gl->glPatchParameterfv(pname, values);
    }
    
    // Query objects
    void GenQueries(int n, unsigned int* ids) override { 
        m_gl->glGenQueries(n, ids);
    }
    void DeleteQueries(int n, const unsigned int* ids) override { 
        m_gl->glDeleteQueries(n, ids);
    }
    void BeginQuery(unsigned int target, unsigned int id) override { 
        m_gl->glBeginQuery(target, id);
    }
    void EndQuery(unsigned int target) override { 
        m_gl->glEndQuery(target);
    }
    void GetQueryObjectiv(unsigned int id, unsigned int pname, int* params) override { 
        m_gl->glGetQueryObjectiv(id, pname, params);
    }
    void GetQueryObjectuiv(unsigned int id, unsigned int pname, unsigned int* params) override { 
        m_gl->glGetQueryObjectuiv(id, pname, params);
    }
    void QueryCounter(unsigned int id, unsigned int target) override { 
        m_gl->glQueryCounter(id, target);
    }
    void GetQueryObjecti64v(unsigned int id, unsigned int pname, long long* params) override { 
        m_gl->glGetQueryObjecti64v(id, pname, params);
    }
    void GetQueryObjectui64v(unsigned int id, unsigned int pname, unsigned long long* params) override { 
        m_gl->glGetQueryObjectui64v(id, pname, params);
    }
    
    // Instanced rendering
    void DrawArraysInstanced(unsigned int mode, int first, int count, int instancecount) override { 
        m_gl->glDrawArraysInstanced(mode, first, count, instancecount);
    }
    void DrawElementsInstanced(unsigned int mode, int count, unsigned int type, const void* indices, int instancecount) override { 
        m_gl->glDrawElementsInstanced(mode, count, type, indices, instancecount);
    }
    void VertexAttribDivisor(unsigned int index, unsigned int divisor) override { 
        m_gl->glVertexAttribDivisor(index, divisor);
    }
    
    // Advanced vertex attributes
    void VertexAttribIPointer(unsigned int index, int size, unsigned int type, int stride, const void* pointer) override { 
        m_gl->glVertexAttribIPointer(index, size, type, stride, pointer);
    }
    void VertexAttribLPointer(unsigned int index, int size, unsigned int type, int stride, const void* pointer) override { 
        m_gl->glVertexAttribLPointer(index, size, type, stride, pointer);
    }
    void GetVertexAttribIiv(unsigned int index, unsigned int pname, int* params) override { 
        m_gl->glGetVertexAttribIiv(index, pname, params);
    }
    void GetVertexAttribIuiv(unsigned int index, unsigned int pname, unsigned int* params) override { 
        m_gl->glGetVertexAttribIuiv(index, pname, params);
    }
    
    // Multiple uniform functions
    void Uniform1iv(int location, int count, const int* value) override { 
        m_gl->glUniform1iv(location, count, value);
    }
    void Uniform2iv(int location, int count, const int* value) override { 
        m_gl->glUniform2iv(location, count, value);
    }
    void Uniform3iv(int location, int count, const int* value) override { 
        m_gl->glUniform3iv(location, count, value);
    }
    void Uniform4iv(int location, int count, const int* value) override { 
        m_gl->glUniform4iv(location, count, value);
    }
    void Uniform1fv(int location, int count, const float* value) override { 
        m_gl->glUniform1fv(location, count, value);
    }
    void Uniform2fv(int location, int count, const float* value) override { 
        m_gl->glUniform2fv(location, count, value);
    }
    void Uniform3fv(int location, int count, const float* value) override { 
        m_gl->glUniform3fv(location, count, value);
    }
    void Uniform4fv(int location, int count, const float* value) override { 
        m_gl->glUniform4fv(location, count, value);
    }
    void Uniform1uiv(int location, int count, const unsigned int* value) override { 
        m_gl->glUniform1uiv(location, count, value);
    }
    void Uniform2uiv(int location, int count, const unsigned int* value) override { 
        m_gl->glUniform2uiv(location, count, value);
    }
    void Uniform3uiv(int location, int count, const unsigned int* value) override { 
        m_gl->glUniform3uiv(location, count, value);
    }
    void Uniform4uiv(int location, int count, const unsigned int* value) override { 
        m_gl->glUniform4uiv(location, count, value);
    }
    void UniformMatrix2fv(int location, int count, unsigned char transpose, const float* value) override { 
        m_gl->glUniformMatrix2fv(location, count, transpose, value);
    }
    void UniformMatrix3fv(int location, int count, unsigned char transpose, const float* value) override { 
        m_gl->glUniformMatrix3fv(location, count, transpose, value);
    }
    void UniformMatrix2x3fv(int location, int count, unsigned char transpose, const float* value) override { 
        m_gl->glUniformMatrix2x3fv(location, count, transpose, value);
    }
    void UniformMatrix3x2fv(int location, int count, unsigned char transpose, const float* value) override { 
        m_gl->glUniformMatrix3x2fv(location, count, transpose, value);
    }
    void UniformMatrix2x4fv(int location, int count, unsigned char transpose, const float* value) override { 
        m_gl->glUniformMatrix2x4fv(location, count, transpose, value);
    }
    void UniformMatrix4x2fv(int location, int count, unsigned char transpose, const float* value) override { 
        m_gl->glUniformMatrix4x2fv(location, count, transpose, value);
    }
    void UniformMatrix3x4fv(int location, int count, unsigned char transpose, const float* value) override { 
        m_gl->glUniformMatrix3x4fv(location, count, transpose, value);
    }
    void UniformMatrix4x3fv(int location, int count, unsigned char transpose, const float* value) override { 
        m_gl->glUniformMatrix4x3fv(location, count, transpose, value);
    }
    
    // Texture sampler objects
    void GenSamplers(int count, unsigned int* samplers) override { 
        m_gl->glGenSamplers(count, samplers);
    }
    void DeleteSamplers(int count, const unsigned int* samplers) override { 
        m_gl->glDeleteSamplers(count, samplers);
    }
    void BindSampler(unsigned int unit, unsigned int sampler) override { 
        m_gl->glBindSampler(unit, sampler);
    }
    void SamplerParameteri(unsigned int sampler, unsigned int pname, int param) override { 
        m_gl->glSamplerParameteri(sampler, pname, param);
    }
    void SamplerParameterf(unsigned int sampler, unsigned int pname, float param) override { 
        m_gl->glSamplerParameterf(sampler, pname, param);
    }
    void SamplerParameteriv(unsigned int sampler, unsigned int pname, const int* param) override { 
        m_gl->glSamplerParameteriv(sampler, pname, param);
    }
    void SamplerParameterfv(unsigned int sampler, unsigned int pname, const float* param) override { 
        m_gl->glSamplerParameterfv(sampler, pname, param);
    }
    void GetSamplerParameteriv(unsigned int sampler, unsigned int pname, int* params) override { 
        m_gl->glGetSamplerParameteriv(sampler, pname, params);
    }
    void GetSamplerParameterfv(unsigned int sampler, unsigned int pname, float* params) override { 
        m_gl->glGetSamplerParameterfv(sampler, pname, params);
    }
    
    // Compute shaders (OpenGL 4.3+)
    void DispatchCompute(unsigned int num_groups_x, unsigned int num_groups_y, unsigned int num_groups_z) override { 
        m_gl->glDispatchCompute(num_groups_x, num_groups_y, num_groups_z);
    }
    void DispatchComputeIndirect(long long indirect) override { 
        m_gl->glDispatchComputeIndirect(indirect);
    }
    void MemoryBarrier(unsigned int barriers) override { 
        m_gl->glMemoryBarrier(barriers);
    }
    
    // Shader storage buffer objects (OpenGL 4.3+)
    void ShaderStorageBlockBinding(unsigned int program, unsigned int storageBlockIndex, unsigned int storageBlockBinding) override { 
        m_gl->glShaderStorageBlockBinding(program, storageBlockIndex, storageBlockBinding);
    }
    
    // Multi-draw functions
    void MultiDrawArrays(unsigned int mode, const int* first, const int* count, int drawcount) override { 
        m_gl->glMultiDrawArrays(mode, first, count, drawcount);
    }
    void MultiDrawElements(unsigned int mode, const int* count, unsigned int type, const void* const* indices, int drawcount) override { 
        m_gl->glMultiDrawElements(mode, count, type, indices, drawcount);
    }
    void MultiDrawArraysIndirect(unsigned int mode, const void* indirect, int drawcount, int stride) override { 
        m_gl->glMultiDrawArraysIndirect(mode, indirect, drawcount, stride);
    }
    void MultiDrawElementsIndirect(unsigned int mode, unsigned int type, const void* indirect, int drawcount, int stride) override { 
        m_gl->glMultiDrawElementsIndirect(mode, type, indirect, drawcount, stride);
    }
    
    // Copy functions
    void CopyBufferSubData(unsigned int readTarget, unsigned int writeTarget, long long readOffset, long long writeOffset, long long size) override { 
        m_gl->glCopyBufferSubData(readTarget, writeTarget, readOffset, writeOffset, size);
    }
    void CopyImageSubData(unsigned int srcName, unsigned int srcTarget, int srcLevel, int srcX, int srcY, int srcZ, unsigned int dstName, unsigned int dstTarget, int dstLevel, int dstX, int dstY, int dstZ, int srcWidth, int srcHeight, int srcDepth) override { 
        m_gl->glCopyImageSubData(srcName, srcTarget, srcLevel, srcX, srcY, srcZ, dstName, dstTarget, dstLevel, dstX, dstY, dstZ, srcWidth, srcHeight, srcDepth);
    }
    
    // Blend functions
    void BlendEquation(unsigned int mode) override { 
        m_gl->glBlendEquation(mode);
    }
    void BlendEquationSeparate(unsigned int modeRGB, unsigned int modeAlpha) override { 
        m_gl->glBlendEquationSeparate(modeRGB, modeAlpha);
    }
    void BlendFuncSeparate(unsigned int sfactorRGB, unsigned int dfactorRGB, unsigned int sfactorAlpha, unsigned int dfactorAlpha) override { 
        m_gl->glBlendFuncSeparate(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha);
    }
    void BlendColor(float red, float green, float blue, float alpha) override { 
        m_gl->glBlendColor(red, green, blue, alpha);
    }
    
    // Stencil functions
    void StencilFunc(unsigned int func, int ref, unsigned int mask) override { 
        m_gl->glStencilFunc(func, ref, mask);
    }
    void StencilFuncSeparate(unsigned int face, unsigned int func, int ref, unsigned int mask) override { 
        m_gl->glStencilFuncSeparate(face, func, ref, mask);
    }
    void StencilOp(unsigned int fail, unsigned int zfail, unsigned int zpass) override { 
        m_gl->glStencilOp(fail, zfail, zpass);
    }
    void StencilOpSeparate(unsigned int face, unsigned int sfail, unsigned int dpfail, unsigned int dppass) override { 
        m_gl->glStencilOpSeparate(face, sfail, dpfail, dppass);
    }
    void StencilMask(unsigned int mask) override { 
        m_gl->glStencilMask(mask);
    }
    void StencilMaskSeparate(unsigned int face, unsigned int mask) override { 
        m_gl->glStencilMaskSeparate(face, mask);
    }
    
    // Advanced buffer functions
    void BufferSubData(unsigned int target, long long offset, long long size, const void* data) override { 
        m_gl->glBufferSubData(target, offset, size, data);
    }
    void GetBufferSubData(unsigned int target, long long offset, long long size, void* data) override { 
        m_gl->glGetBufferSubData(target, offset, size, data);
    }
    void* MapBuffer(unsigned int target, unsigned int access) override { 
        return m_gl->glMapBuffer(target, access);
    }
    unsigned char UnmapBuffer(unsigned int target) override { 
        return m_gl->glUnmapBuffer(target);
    }
    void* MapBufferRange(unsigned int target, long long offset, long long length, unsigned int access) override { 
        return m_gl->glMapBufferRange(target, offset, length, access);
    }
    void FlushMappedBufferRange(unsigned int target, long long offset, long long length) override { 
        m_gl->glFlushMappedBufferRange(target, offset, length);
    }
    
    // Debug functions (OpenGL 4.3+) - Note: Some of these might not be available in Qt's OpenGL functions
    void DebugMessageControl(unsigned int source, unsigned int type, unsigned int severity, int count, const unsigned int* ids, unsigned char enabled) override { 
        // May not be available in all Qt versions
        if (m_gl->hasOpenGLFeature(QOpenGLFunctions::DebugMarkers)) {
            m_gl->glDebugMessageControl(source, type, severity, count, ids, enabled);
        }
    }
    void DebugMessageInsert(unsigned int source, unsigned int type, unsigned int id, unsigned int severity, int length, const char* buf) override { 
        if (m_gl->hasOpenGLFeature(QOpenGLFunctions::DebugMarkers)) {
            m_gl->glDebugMessageInsert(source, type, id, severity, length, buf);
        }
    }
    void DebugMessageCallback(void* callback, const void* userParam) override { 
        // This might not be available in Qt's OpenGL functions
        // m_gl->glDebugMessageCallback((GLDEBUGPROC)callback, userParam);
    }
    unsigned int DebugMessageLog(unsigned int count, int bufSize, unsigned int* sources, unsigned int* types, unsigned int* ids, unsigned int* severities, int* lengths, char* messageLog) override { 
        if (m_gl->hasOpenGLFeature(QOpenGLFunctions::DebugMarkers)) {
            return m_gl->glGetDebugMessageLog(count, bufSize, sources, types, ids, severities, lengths, messageLog);
        }
        return 0;
    }
    void GetDebugMessageLog(unsigned int count, int bufSize, unsigned int* sources, unsigned int* types, unsigned int* ids, unsigned int* severities, int* lengths, char* messageLog) override { 
        if (m_gl->hasOpenGLFeature(QOpenGLFunctions::DebugMarkers)) {
            m_gl->glGetDebugMessageLog(count, bufSize, sources, types, ids, severities, lengths, messageLog);
        }
    }
    void PushDebugGroup(unsigned int source, unsigned int id, int length, const char* message) override { 
        if (m_gl->hasOpenGLFeature(QOpenGLFunctions::DebugMarkers)) {
            m_gl->glPushDebugGroup(source, id, length, message);
        }
    }
    void PopDebugGroup() override { 
        if (m_gl->hasOpenGLFeature(QOpenGLFunctions::DebugMarkers)) {
            m_gl->glPopDebugGroup();
        }
    }
    void ObjectLabel(unsigned int identifier, unsigned int name, int length, const char* label) override { 
        if (m_gl->hasOpenGLFeature(QOpenGLFunctions::DebugMarkers)) {
            m_gl->glObjectLabel(identifier, name, length, label);
        }
    }
    void GetObjectLabel(unsigned int identifier, unsigned int name, int bufSize, int* length, char* label) override { 
        if (m_gl->hasOpenGLFeature(QOpenGLFunctions::DebugMarkers)) {
            m_gl->glGetObjectLabel(identifier, name, bufSize, length, label);
        }
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

inline void clearDepth(double depth) { 
    g_gl->ClearDepth(depth);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("clearDepth");
#endif
}

inline void clearStencil(int stencil) { 
    g_gl->ClearStencil(stencil);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("clearStencil");
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

// OpenGL 4.0+ Core convenience functions with optional error checking

// Framebuffer functions
inline void genFramebuffers(int n, unsigned int* framebuffers) { 
    g_gl->GenFramebuffers(n, framebuffers);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("genFramebuffers");
#endif
}

inline void bindFramebuffer(unsigned int target, unsigned int framebuffer) { 
    g_gl->BindFramebuffer(target, framebuffer);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("bindFramebuffer");
#endif
}

inline void deleteFramebuffers(int n, const unsigned int* framebuffers) { 
    g_gl->DeleteFramebuffers(n, framebuffers);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("deleteFramebuffers");
#endif
}

inline void framebufferTexture2D(unsigned int target, unsigned int attachment, unsigned int textarget, unsigned int texture, int level) { 
    g_gl->FramebufferTexture2D(target, attachment, textarget, texture, level);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("framebufferTexture2D");
#endif
}

inline void genRenderbuffers(int n, unsigned int* renderbuffers) { 
    g_gl->GenRenderbuffers(n, renderbuffers);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("genRenderbuffers");
#endif
}

inline void bindRenderbuffer(unsigned int target, unsigned int renderbuffer) { 
    g_gl->BindRenderbuffer(target, renderbuffer);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("bindRenderbuffer");
#endif
}

inline void deleteRenderbuffers(int n, const unsigned int* renderbuffers) { 
    g_gl->DeleteRenderbuffers(n, renderbuffers);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("deleteRenderbuffers");
#endif
}

inline void renderbufferStorage(unsigned int target, unsigned int internalformat, int width, int height) { 
    g_gl->RenderbufferStorage(target, internalformat, width, height);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("renderbufferStorage");
#endif
}

inline void framebufferRenderbuffer(unsigned int target, unsigned int attachment, unsigned int renderbuffertarget, unsigned int renderbuffer) { 
    g_gl->FramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("framebufferRenderbuffer");
#endif
}

inline unsigned int checkFramebufferStatus(unsigned int target) { 
    unsigned int result = g_gl->CheckFramebufferStatus(target);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("checkFramebufferStatus");
#endif
    return result;
}

inline void drawBuffers(int n, const unsigned int* bufs) { 
    g_gl->DrawBuffers(n, bufs);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("drawBuffers");
#endif
}

inline void readBuffer(unsigned int mode) { 
    g_gl->ReadBuffer(mode);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("readBuffer");
#endif
}

inline void blitFramebuffer(int srcX0, int srcY0, int srcX1, int srcY1, int dstX0, int dstY0, int dstX1, int dstY1, unsigned int mask, unsigned int filter) { 
    g_gl->BlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("blitFramebuffer");
#endif
}

// Advanced texture functions
inline void texImage3D(unsigned int target, int level, int internalformat, int width, int height, int depth, int border, unsigned int format, unsigned int type, const void* pixels) { 
    g_gl->TexImage3D(target, level, internalformat, width, height, depth, border, format, type, pixels);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("texImage3D");
#endif
}

inline void texSubImage2D(unsigned int target, int level, int xoffset, int yoffset, int width, int height, unsigned int format, unsigned int type, const void* pixels) { 
    g_gl->TexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("texSubImage2D");
#endif
}

inline void texSubImage3D(unsigned int target, int level, int xoffset, int yoffset, int zoffset, int width, int height, int depth, unsigned int format, unsigned int type, const void* pixels) { 
    g_gl->TexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("texSubImage3D");
#endif
}

inline void compressedTexImage2D(unsigned int target, int level, unsigned int internalformat, int width, int height, int border, int imageSize, const void* data) { 
    g_gl->CompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("compressedTexImage2D");
#endif
}

inline void compressedTexSubImage2D(unsigned int target, int level, int xoffset, int yoffset, int width, int height, unsigned int format, int imageSize, const void* data) { 
    g_gl->CompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("compressedTexSubImage2D");
#endif
}

inline void texStorage2D(unsigned int target, int levels, unsigned int internalformat, int width, int height) { 
    g_gl->TexStorage2D(target, levels, internalformat, width, height);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("texStorage2D");
#endif
}

inline void texStorage3D(unsigned int target, int levels, unsigned int internalformat, int width, int height, int depth) { 
    g_gl->TexStorage3D(target, levels, internalformat, width, height, depth);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("texStorage3D");
#endif
}

inline void getTexImage(unsigned int target, int level, unsigned int format, unsigned int type, void* pixels) { 
    g_gl->GetTexImage(target, level, format, type, pixels);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("getTexImage");
#endif
}

inline void copyTexImage2D(unsigned int target, int level, unsigned int internalformat, int x, int y, int width, int height, int border) { 
    g_gl->CopyTexImage2D(target, level, internalformat, x, y, width, height, border);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("copyTexImage2D");
#endif
}

inline void copyTexSubImage2D(unsigned int target, int level, int xoffset, int yoffset, int x, int y, int width, int height) { 
    g_gl->CopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("copyTexSubImage2D");
#endif
}

// Uniform buffer objects
inline void bindBufferBase(unsigned int target, unsigned int index, unsigned int buffer) { 
    g_gl->BindBufferBase(target, index, buffer);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("bindBufferBase");
#endif
}

inline void bindBufferRange(unsigned int target, unsigned int index, unsigned int buffer, long long offset, long long size) { 
    g_gl->BindBufferRange(target, index, buffer, offset, size);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("bindBufferRange");
#endif
}

inline unsigned int getUniformBlockIndex(unsigned int program, const char* uniformBlockName) { 
    unsigned int result = g_gl->GetUniformBlockIndex(program, uniformBlockName);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("getUniformBlockIndex");
#endif
    return result;
}

inline void uniformBlockBinding(unsigned int program, unsigned int uniformBlockIndex, unsigned int uniformBlockBinding) { 
    g_gl->UniformBlockBinding(program, uniformBlockIndex, uniformBlockBinding);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("uniformBlockBinding");
#endif
}

inline void getActiveUniformBlockiv(unsigned int program, unsigned int uniformBlockIndex, unsigned int pname, int* params) { 
    g_gl->GetActiveUniformBlockiv(program, uniformBlockIndex, pname, params);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("getActiveUniformBlockiv");
#endif
}

// Transform feedback
inline void genTransformFeedbacks(int n, unsigned int* ids) { 
    g_gl->GenTransformFeedbacks(n, ids);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("genTransformFeedbacks");
#endif
}

inline void bindTransformFeedback(unsigned int target, unsigned int id) { 
    g_gl->BindTransformFeedback(target, id);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("bindTransformFeedback");
#endif
}

inline void deleteTransformFeedbacks(int n, const unsigned int* ids) { 
    g_gl->DeleteTransformFeedbacks(n, ids);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("deleteTransformFeedbacks");
#endif
}

inline void beginTransformFeedback(unsigned int primitiveMode) { 
    g_gl->BeginTransformFeedback(primitiveMode);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("beginTransformFeedback");
#endif
}

inline void endTransformFeedback() { 
    g_gl->EndTransformFeedback();
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("endTransformFeedback");
#endif
}

inline void transformFeedbackVaryings(unsigned int program, int count, const char* const* varyings, unsigned int bufferMode) { 
    g_gl->TransformFeedbackVaryings(program, count, varyings, bufferMode);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("transformFeedbackVaryings");
#endif
}

inline void getTransformFeedbackVarying(unsigned int program, unsigned int index, int bufSize, int* length, int* size, unsigned int* type, char* name) { 
    g_gl->GetTransformFeedbackVarying(program, index, bufSize, length, size, type, name);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("getTransformFeedbackVarying");
#endif
}

// Geometry shader and tessellation functions
inline void programParameteri(unsigned int program, unsigned int pname, int value) { 
    g_gl->ProgramParameteri(program, pname, value);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("programParameteri");
#endif
}

inline void patchParameteri(unsigned int pname, int value) { 
    g_gl->PatchParameteri(pname, value);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("patchParameteri");
#endif
}

inline void patchParameterfv(unsigned int pname, const float* values) { 
    g_gl->PatchParameterfv(pname, values);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("patchParameterfv");
#endif
}

// Query objects
inline void genQueries(int n, unsigned int* ids) { 
    g_gl->GenQueries(n, ids);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("genQueries");
#endif
}

inline void deleteQueries(int n, const unsigned int* ids) { 
    g_gl->DeleteQueries(n, ids);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("deleteQueries");
#endif
}

inline void beginQuery(unsigned int target, unsigned int id) { 
    g_gl->BeginQuery(target, id);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("beginQuery");
#endif
}

inline void endQuery(unsigned int target) { 
    g_gl->EndQuery(target);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("endQuery");
#endif
}

inline void getQueryObjectiv(unsigned int id, unsigned int pname, int* params) { 
    g_gl->GetQueryObjectiv(id, pname, params);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("getQueryObjectiv");
#endif
}

inline void getQueryObjectuiv(unsigned int id, unsigned int pname, unsigned int* params) { 
    g_gl->GetQueryObjectuiv(id, pname, params);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("getQueryObjectuiv");
#endif
}

inline void queryCounter(unsigned int id, unsigned int target) { 
    g_gl->QueryCounter(id, target);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("queryCounter");
#endif
}

inline void getQueryObjecti64v(unsigned int id, unsigned int pname, long long* params) { 
    g_gl->GetQueryObjecti64v(id, pname, params);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("getQueryObjecti64v");
#endif
}

inline void getQueryObjectui64v(unsigned int id, unsigned int pname, unsigned long long* params) { 
    g_gl->GetQueryObjectui64v(id, pname, params);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("getQueryObjectui64v");
#endif
}

// Instanced rendering
inline void drawArraysInstanced(unsigned int mode, int first, int count, int instancecount) { 
    g_gl->DrawArraysInstanced(mode, first, count, instancecount);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("drawArraysInstanced");
#endif
}

inline void drawElementsInstanced(unsigned int mode, int count, unsigned int type, const void* indices, int instancecount) { 
    g_gl->DrawElementsInstanced(mode, count, type, indices, instancecount);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("drawElementsInstanced");
#endif
}

inline void vertexAttribDivisor(unsigned int index, unsigned int divisor) { 
    g_gl->VertexAttribDivisor(index, divisor);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("vertexAttribDivisor");
#endif
}

// Advanced vertex attributes
inline void vertexAttribIPointer(unsigned int index, int size, unsigned int type, int stride, const void* pointer) { 
    g_gl->VertexAttribIPointer(index, size, type, stride, pointer);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("vertexAttribIPointer");
#endif
}

inline void vertexAttribLPointer(unsigned int index, int size, unsigned int type, int stride, const void* pointer) { 
    g_gl->VertexAttribLPointer(index, size, type, stride, pointer);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("vertexAttribLPointer");
#endif
}

inline void getVertexAttribIiv(unsigned int index, unsigned int pname, int* params) { 
    g_gl->GetVertexAttribIiv(index, pname, params);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("getVertexAttribIiv");
#endif
}

inline void getVertexAttribIuiv(unsigned int index, unsigned int pname, unsigned int* params) { 
    g_gl->GetVertexAttribIuiv(index, pname, params);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("getVertexAttribIuiv");
#endif
}

// Multiple uniform functions
inline void uniform1iv(int location, int count, const int* value) { 
    g_gl->Uniform1iv(location, count, value);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("uniform1iv");
#endif
}

inline void uniform2iv(int location, int count, const int* value) { 
    g_gl->Uniform2iv(location, count, value);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("uniform2iv");
#endif
}

inline void uniform3iv(int location, int count, const int* value) { 
    g_gl->Uniform3iv(location, count, value);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("uniform3iv");
#endif
}

inline void uniform4iv(int location, int count, const int* value) { 
    g_gl->Uniform4iv(location, count, value);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("uniform4iv");
#endif
}

inline void uniform1fv(int location, int count, const float* value) { 
    g_gl->Uniform1fv(location, count, value);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("uniform1fv");
#endif
}

inline void uniform2fv(int location, int count, const float* value) { 
    g_gl->Uniform2fv(location, count, value);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("uniform2fv");
#endif
}

inline void uniform3fv(int location, int count, const float* value) { 
    g_gl->Uniform3fv(location, count, value);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("uniform3fv");
#endif
}

inline void uniform4fv(int location, int count, const float* value) { 
    g_gl->Uniform4fv(location, count, value);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("uniform4fv");
#endif
}

inline void uniform1uiv(int location, int count, const unsigned int* value) { 
    g_gl->Uniform1uiv(location, count, value);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("uniform1uiv");
#endif
}

inline void uniform2uiv(int location, int count, const unsigned int* value) { 
    g_gl->Uniform2uiv(location, count, value);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("uniform2uiv");
#endif
}

inline void uniform3uiv(int location, int count, const unsigned int* value) { 
    g_gl->Uniform3uiv(location, count, value);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("uniform3uiv");
#endif
}

inline void uniform4uiv(int location, int count, const unsigned int* value) { 
    g_gl->Uniform4uiv(location, count, value);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("uniform4uiv");
#endif
}

inline void uniformMatrix2fv(int location, int count, unsigned char transpose, const float* value) { 
    g_gl->UniformMatrix2fv(location, count, transpose, value);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("uniformMatrix2fv");
#endif
}

inline void uniformMatrix3fv(int location, int count, unsigned char transpose, const float* value) { 
    g_gl->UniformMatrix3fv(location, count, transpose, value);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("uniformMatrix3fv");
#endif
}

inline void uniformMatrix2x3fv(int location, int count, unsigned char transpose, const float* value) { 
    g_gl->UniformMatrix2x3fv(location, count, transpose, value);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("uniformMatrix2x3fv");
#endif
}

inline void uniformMatrix3x2fv(int location, int count, unsigned char transpose, const float* value) { 
    g_gl->UniformMatrix3x2fv(location, count, transpose, value);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("uniformMatrix3x2fv");
#endif
}

inline void uniformMatrix2x4fv(int location, int count, unsigned char transpose, const float* value) { 
    g_gl->UniformMatrix2x4fv(location, count, transpose, value);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("uniformMatrix2x4fv");
#endif
}

inline void uniformMatrix4x2fv(int location, int count, unsigned char transpose, const float* value) { 
    g_gl->UniformMatrix4x2fv(location, count, transpose, value);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("uniformMatrix4x2fv");
#endif
}

inline void uniformMatrix3x4fv(int location, int count, unsigned char transpose, const float* value) { 
    g_gl->UniformMatrix3x4fv(location, count, transpose, value);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("uniformMatrix3x4fv");
#endif
}

inline void uniformMatrix4x3fv(int location, int count, unsigned char transpose, const float* value) { 
    g_gl->UniformMatrix4x3fv(location, count, transpose, value);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("uniformMatrix4x3fv");
#endif
}

// Texture sampler objects
inline void genSamplers(int count, unsigned int* samplers) { 
    g_gl->GenSamplers(count, samplers);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("genSamplers");
#endif
}

inline void deleteSamplers(int count, const unsigned int* samplers) { 
    g_gl->DeleteSamplers(count, samplers);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("deleteSamplers");
#endif
}

inline void bindSampler(unsigned int unit, unsigned int sampler) { 
    g_gl->BindSampler(unit, sampler);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("bindSampler");
#endif
}

inline void samplerParameteri(unsigned int sampler, unsigned int pname, int param) { 
    g_gl->SamplerParameteri(sampler, pname, param);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("samplerParameteri");
#endif
}

inline void samplerParameterf(unsigned int sampler, unsigned int pname, float param) { 
    g_gl->SamplerParameterf(sampler, pname, param);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("samplerParameterf");
#endif
}

inline void samplerParameteriv(unsigned int sampler, unsigned int pname, const int* param) { 
    g_gl->SamplerParameteriv(sampler, pname, param);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("samplerParameteriv");
#endif
}

inline void samplerParameterfv(unsigned int sampler, unsigned int pname, const float* param) { 
    g_gl->SamplerParameterfv(sampler, pname, param);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("samplerParameterfv");
#endif
}

inline void getSamplerParameteriv(unsigned int sampler, unsigned int pname, int* params) { 
    g_gl->GetSamplerParameteriv(sampler, pname, params);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("getSamplerParameteriv");
#endif
}

inline void getSamplerParameterfv(unsigned int sampler, unsigned int pname, float* params) { 
    g_gl->GetSamplerParameterfv(sampler, pname, params);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("getSamplerParameterfv");
#endif
}

// Compute shaders (OpenGL 4.3+)
inline void dispatchCompute(unsigned int num_groups_x, unsigned int num_groups_y, unsigned int num_groups_z) { 
    g_gl->DispatchCompute(num_groups_x, num_groups_y, num_groups_z);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("dispatchCompute");
#endif
}

inline void dispatchComputeIndirect(long long indirect) { 
    g_gl->DispatchComputeIndirect(indirect);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("dispatchComputeIndirect");
#endif
}

inline void memoryBarrier(unsigned int barriers) { 
    g_gl->MemoryBarrier(barriers);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("memoryBarrier");
#endif
}

// Shader storage buffer objects (OpenGL 4.3+)
inline void shaderStorageBlockBinding(unsigned int program, unsigned int storageBlockIndex, unsigned int storageBlockBinding) { 
    g_gl->ShaderStorageBlockBinding(program, storageBlockIndex, storageBlockBinding);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("shaderStorageBlockBinding");
#endif
}

// Multi-draw functions
inline void multiDrawArrays(unsigned int mode, const int* first, const int* count, int drawcount) { 
    g_gl->MultiDrawArrays(mode, first, count, drawcount);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("multiDrawArrays");
#endif
}

inline void multiDrawElements(unsigned int mode, const int* count, unsigned int type, const void* const* indices, int drawcount) { 
    g_gl->MultiDrawElements(mode, count, type, indices, drawcount);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("multiDrawElements");
#endif
}

inline void multiDrawArraysIndirect(unsigned int mode, const void* indirect, int drawcount, int stride) { 
    g_gl->MultiDrawArraysIndirect(mode, indirect, drawcount, stride);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("multiDrawArraysIndirect");
#endif
}

inline void multiDrawElementsIndirect(unsigned int mode, unsigned int type, const void* indirect, int drawcount, int stride) { 
    g_gl->MultiDrawElementsIndirect(mode, type, indirect, drawcount, stride);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("multiDrawElementsIndirect");
#endif
}

// Copy functions
inline void copyBufferSubData(unsigned int readTarget, unsigned int writeTarget, long long readOffset, long long writeOffset, long long size) { 
    g_gl->CopyBufferSubData(readTarget, writeTarget, readOffset, writeOffset, size);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("copyBufferSubData");
#endif
}

inline void copyImageSubData(unsigned int srcName, unsigned int srcTarget, int srcLevel, int srcX, int srcY, int srcZ, unsigned int dstName, unsigned int dstTarget, int dstLevel, int dstX, int dstY, int dstZ, int srcWidth, int srcHeight, int srcDepth) { 
    g_gl->CopyImageSubData(srcName, srcTarget, srcLevel, srcX, srcY, srcZ, dstName, dstTarget, dstLevel, dstX, dstY, dstZ, srcWidth, srcHeight, srcDepth);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("copyImageSubData");
#endif
}

// Blend functions
inline void blendEquation(unsigned int mode) { 
    g_gl->BlendEquation(mode);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("blendEquation");
#endif
}

inline void blendEquationSeparate(unsigned int modeRGB, unsigned int modeAlpha) { 
    g_gl->BlendEquationSeparate(modeRGB, modeAlpha);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("blendEquationSeparate");
#endif
}

inline void blendFuncSeparate(unsigned int sfactorRGB, unsigned int dfactorRGB, unsigned int sfactorAlpha, unsigned int dfactorAlpha) { 
    g_gl->BlendFuncSeparate(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("blendFuncSeparate");
#endif
}

inline void blendColor(float red, float green, float blue, float alpha) { 
    g_gl->BlendColor(red, green, blue, alpha);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("blendColor");
#endif
}

// Stencil functions
inline void stencilFunc(unsigned int func, int ref, unsigned int mask) { 
    g_gl->StencilFunc(func, ref, mask);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("stencilFunc");
#endif
}

inline void stencilFuncSeparate(unsigned int face, unsigned int func, int ref, unsigned int mask) { 
    g_gl->StencilFuncSeparate(face, func, ref, mask);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("stencilFuncSeparate");
#endif
}

inline void stencilOp(unsigned int fail, unsigned int zfail, unsigned int zpass) { 
    g_gl->StencilOp(fail, zfail, zpass);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("stencilOp");
#endif
}

inline void stencilOpSeparate(unsigned int face, unsigned int sfail, unsigned int dpfail, unsigned int dppass) { 
    g_gl->StencilOpSeparate(face, sfail, dpfail, dppass);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("stencilOpSeparate");
#endif
}

inline void stencilMask(unsigned int mask) { 
    g_gl->StencilMask(mask);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("stencilMask");
#endif
}

inline void stencilMaskSeparate(unsigned int face, unsigned int mask) { 
    g_gl->StencilMaskSeparate(face, mask);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("stencilMaskSeparate");
#endif
}

// Advanced buffer functions
inline void bufferSubData(unsigned int target, long long offset, long long size, const void* data) { 
    g_gl->BufferSubData(target, offset, size, data);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("bufferSubData");
#endif
}

inline void getBufferSubData(unsigned int target, long long offset, long long size, void* data) { 
    g_gl->GetBufferSubData(target, offset, size, data);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("getBufferSubData");
#endif
}

inline void* mapBuffer(unsigned int target, unsigned int access) { 
    void* result = g_gl->MapBuffer(target, access);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("mapBuffer");
#endif
    return result;
}

inline unsigned char unmapBuffer(unsigned int target) { 
    unsigned char result = g_gl->UnmapBuffer(target);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("unmapBuffer");
#endif
    return result;
}

inline void* mapBufferRange(unsigned int target, long long offset, long long length, unsigned int access) { 
    void* result = g_gl->MapBufferRange(target, offset, length, access);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("mapBufferRange");
#endif
    return result;
}

inline void flushMappedBufferRange(unsigned int target, long long offset, long long length) { 
    g_gl->FlushMappedBufferRange(target, offset, length);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("flushMappedBufferRange");
#endif
}

// Debug functions (OpenGL 4.3+)
inline void debugMessageControl(unsigned int source, unsigned int type, unsigned int severity, int count, const unsigned int* ids, unsigned char enabled) { 
    g_gl->DebugMessageControl(source, type, severity, count, ids, enabled);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("debugMessageControl");
#endif
}

inline void debugMessageInsert(unsigned int source, unsigned int type, unsigned int id, unsigned int severity, int length, const char* buf) { 
    g_gl->DebugMessageInsert(source, type, id, severity, length, buf);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("debugMessageInsert");
#endif
}

inline void debugMessageCallback(void* callback, const void* userParam) { 
    g_gl->DebugMessageCallback(callback, userParam);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("debugMessageCallback");
#endif
}

inline unsigned int debugMessageLog(unsigned int count, int bufSize, unsigned int* sources, unsigned int* types, unsigned int* ids, unsigned int* severities, int* lengths, char* messageLog) { 
    unsigned int result = g_gl->DebugMessageLog(count, bufSize, sources, types, ids, severities, lengths, messageLog);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("debugMessageLog");
#endif
    return result;
}

inline void getDebugMessageLog(unsigned int count, int bufSize, unsigned int* sources, unsigned int* types, unsigned int* ids, unsigned int* severities, int* lengths, char* messageLog) { 
    g_gl->GetDebugMessageLog(count, bufSize, sources, types, ids, severities, lengths, messageLog);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("getDebugMessageLog");
#endif
}

inline void pushDebugGroup(unsigned int source, unsigned int id, int length, const char* message) { 
    g_gl->PushDebugGroup(source, id, length, message);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("pushDebugGroup");
#endif
}

inline void popDebugGroup() { 
    g_gl->PopDebugGroup();
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("popDebugGroup");
#endif
}

inline void objectLabel(unsigned int identifier, unsigned int name, int length, const char* label) { 
    g_gl->ObjectLabel(identifier, name, length, label);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("objectLabel");
#endif
}

inline void getObjectLabel(unsigned int identifier, unsigned int name, int bufSize, int* length, char* label) { 
    g_gl->GetObjectLabel(identifier, name, bufSize, length, label);
#ifdef NETHER_GL_ERROR_CHECKING
    checkGLError("getObjectLabel");
#endif
}

// Initialization functions
void initializeDirectGL();
#ifdef AETHER_USE_QT
void initializeQtGL(QOpenGLContext* context);
#endif

} // namespace gl
} // namespace nether
