#include "histogram.h"

#include <stdio.h>
#include <glad/glad.h>

#include <cglm/cglm.h>

static GLuint vbo = 0;
static GLuint shader = 0;
static GLint model_location = 0;
static GLint projection_location = 0;

static mat4 model;
static mat4 ortho;

int histogram_init()
{
    float vertices[] = {
        0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f
    };

    glCreateBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), (void*)vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    GLint result = 0;

    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    const char* vertex_shader_source = 
        "#version 460 core\n"
        ""
        "layout (location = 0) in vec3 i_pos;\n"
        ""
        "uniform mat4 model;\n"
        "uniform mat4 projection;\n"
        "void main() {\n"
        "   gl_Position = projection * model * vec4(i_pos, 1.0f);\n"
        "}"
    ;

    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
    glCompileShader(vertex_shader);
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &result);
    if(result != GL_TRUE)
    {
        char error_buf[512];
        glGetShaderInfoLog(vertex_shader, sizeof(error_buf), NULL, error_buf);
        fprintf(stderr, "Could not compile vertex shader: %s", error_buf);

        goto vertex_out;
    }

    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragment_shader_source = 
        "#version 460 core\n"
        ""
        "out vec4 o_col;\n"
        ""
        "void main() {\n"
        "   o_col = vec4(1.0f);\n"
        "}"
    ;

    glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
    glCompileShader(fragment_shader);
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &result);
    if(result != GL_TRUE)
    {
        char error_buf[512];
        glGetShaderInfoLog(fragment_shader, sizeof(error_buf), NULL, error_buf);
        fprintf(stderr, "Could not compile fragment shader: %s", error_buf);

        goto fragment_out;
    }

    shader = glCreateProgram();
    glAttachShader(shader, vertex_shader);
    glAttachShader(shader, fragment_shader);

    glLinkProgram(shader);
    glGetProgramiv(shader, GL_LINK_STATUS, &result);
    if(result != GL_TRUE)
    {
        char error_buf[512];
        glGetProgramInfoLog(shader, sizeof(error_buf), NULL, error_buf);
        fprintf(stderr, "Could not link shader program: %s", error_buf);
    }

    glm_mat4_identity(model);
    glm_ortho(0.0f, 1.0f, 0.0f, 1.0f, -1.0f, 1.0f, ortho);

    model_location      = glGetUniformLocation(shader, "model");
    projection_location = glGetUniformLocation(shader, "projection");

fragment_out:
    glDeleteShader(fragment_shader);

vertex_out:
    glDeleteShader(vertex_shader);

    return result;
}

void histogram_render(void)
{
    glUseProgram(shader);
    glUniformMatrix4fv(projection_location, 1, GL_FALSE, ortho[0]);

    for(int i = 0; i < visualizer_data.array_size; i++)
    {
        glm_mat4_identity(model);
        glm_translate(model, (vec3) {(float)i / visualizer_data.array_size, 0.0f, 0.0f});
        glm_scale(model, (vec3) {1.0f / (visualizer_data.array_size + 1), 1.0f / visualizer_data.array_size + (float)visualizer_data.array[i] / (visualizer_data.array_size + 1), 1.0f});

        glUniformMatrix4fv(model_location, 1, GL_FALSE, model[0]);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    }
}

void histogram_exit(void)
{
    glDeleteProgram(shader);
    glDeleteBuffers(1, &vbo);
}