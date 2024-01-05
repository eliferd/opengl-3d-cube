#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "shader.h"

GLuint shaderProgramId = 0;

void init_shaders()
{
    // Shader program creation
    shaderProgramId = glCreateProgram();

    // Shader cration
    GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

    // Load shader sources from file
    bind_shader_source(vertexShaderId, "vertex.glsl");
    bind_shader_source(fragmentShaderId, "fragment.glsl");

    // Shader compilation
    glCompileShader(vertexShaderId);
    glCompileShader(fragmentShaderId);

    check_compile_status(vertexShaderId, GL_VERTEX_SHADER);
    check_compile_status(fragmentShaderId, GL_FRAGMENT_SHADER);

    // Linking to shader program
    glAttachShader(shaderProgramId, vertexShaderId);
    glAttachShader(shaderProgramId, fragmentShaderId);

    // "Compiling" shader program
    glLinkProgram(shaderProgramId);

    GLint isLinked = 0;
    glGetProgramiv(shaderProgramId, GL_LINK_STATUS, &isLinked);
    if (isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(shaderProgramId, GL_INFO_LOG_LENGTH, &maxLength);

        char infoLog[900] = "";
        glGetProgramInfoLog(shaderProgramId, maxLength, &maxLength, &infoLog[0]);

        printf("GL PROGRAM LINK ERROR : \n%s\n\n", infoLog);

        // The program is useless now. So delete it.
        glDeleteProgram(shaderProgramId);
    }

    use_shader_program();

    // Shaders are not needed anymore as they are in the compiled shader program
    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);
}

void use_shader_program()
{
    glUseProgram(shaderProgramId);
}

void bind_shader_source(const GLuint shaderId, const char* filename)
{
    FILE* shaderFile = fopen(filename, "r");

    if(!shaderFile)
    {
        printf("Could not load shader source file...\n");
    }
    else
    {
        char result[SHADER_SOURCE_MAX_LENGTH] = "";
        char fileOutput[SHADER_SOURCE_MAX_LENGTH] = "";

        while(fgets(result, SHADER_SOURCE_MAX_LENGTH, shaderFile) != NULL)
        {
            strcat(fileOutput, result);
        }

        //printf("SHADER SOURCE for %s : \n%s\n\n\n------\n", filename, fileOutput);


        const GLchar* shaderSource = fileOutput;

        glShaderSource(shaderId, 1, &shaderSource, NULL);
    }
    fclose(shaderFile);
}

void check_compile_status(const GLuint shaderId, const GLenum shaderType)
{
    GLint isCompiled = 0;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;

        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &maxLength);

        char* errorLog = malloc(maxLength * sizeof(char));

        glGetShaderInfoLog(shaderId, maxLength, &maxLength, &errorLog[0]);

        printf("%s Shader compile error : \n%s\n", shaderType == GL_VERTEX_SHADER ? "Vertex" : "Fragment", errorLog);

        free(errorLog);

        glDeleteShader(shaderId); // Don't leak the shader.

        return;
    }
}

GLuint get_shader_program_id()
{
    return shaderProgramId;
}
