#ifndef SHADER_H_INCLUDED
#define SHADER_H_INCLUDED

#include <glad.h>
#define SHADER_SOURCE_MAX_LENGTH 2048

void init_shaders();
void use_shader_program();
GLuint get_shader_program_id();
void bind_shader_source(const GLuint shaderId, const char* filename);
void check_compile_status(const GLuint shaderId, const GLenum shaderType);

#endif // SHADER_H_INCLUDED
