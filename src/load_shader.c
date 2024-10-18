#include <stdio.h>
#include <assert.h>

#include "utils.h"

#include "load_shader.h"

GLuint LoadShaders(const char *vertex_file_path, const char *fragment_file_path)
{
    // Create the shaders
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    // Read the Vertex Shader code from the file
    FILE *vertex_shader_file = fopen(vertex_file_path, "r");
    assert(vertex_shader_file != NULL);
    int vertex_file_length = get_file_length(vertex_shader_file);
    char vertex_shader_code[vertex_file_length];
    fread(vertex_shader_code, vertex_file_length, 1, vertex_shader_file);
    fclose(vertex_shader_file);
    const GLchar *vertex_shader_code2 = vertex_shader_code;

    // Read the Fragment Shader code from the file
    FILE *fragment_shader_file = fopen(fragment_file_path, "r");
    assert(fragment_shader_file != NULL);
    int fragment_file_length = get_file_length(fragment_shader_file);
    char fragment_shader_code[fragment_file_length];
    fread(fragment_shader_code, fragment_file_length, 1, fragment_shader_file);
    fclose(fragment_shader_file);
    const GLchar *fragment_shader_code2 = fragment_shader_code;
    
    GLint Result = GL_FALSE;
    int InfoLogLength;

    // Compile Vertex Shader
    printf("Compiling shader : %s\n", vertex_file_path);
    glShaderSource(VertexShaderID, 1, &vertex_shader_code2, &vertex_file_length);
    glCompileShader(VertexShaderID);

    // Check Vertex Shader
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0)
    {
        printf("erreur ta gueule 01\n");
        // std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
        // glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
        // printf("%s\n", &VertexShaderErrorMessage[0]);
    }

    // Compile Fragment Shader
    printf("Compiling shader : %s\n", fragment_file_path);
    glShaderSource(FragmentShaderID, 1, &fragment_shader_code2, &fragment_file_length);
    glCompileShader(FragmentShaderID);

    // Check Fragment Shader
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0)
    {
        printf("erreur ta gueule 02\n");
        // std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
        // glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
        // printf("%s\n", &FragmentShaderErrorMessage[0]);
    }

    // Link the program
    printf("Linking program\n");
    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);

    // Check the program
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0)
    {
        printf("erreur ta gueule 03\n");
        // std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
        // glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        // printf("%s\n", &ProgramErrorMessage[0]);
    }

    glDetachShader(ProgramID, VertexShaderID);
    glDetachShader(ProgramID, FragmentShaderID);

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    return ProgramID;
}
