#include "gl_object_map.hpp"

#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <string.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace NRV::Graphics {
    //
    // Vertex Array Map
    //

    VertexArrayMap::id_t VertexArrayMap::prGenerateId() {
        id_t f_id;
        glGenVertexArrays(1, &f_id);
        return f_id;
    }

    void VertexArrayMap::bind(id_t id) {
        glBindVertexArray(id);
    }

    //
    // Vertex Buffer Map
    //

    VertexBufferMap::id_t VertexBufferMap::prGenerateId() {
        id_t f_id;
        glGenBuffers(1, &f_id);
        return f_id;
    }

    void VertexBufferMap::bind(id_t id) {
        glBindBuffer(GL_ARRAY_BUFFER, id);  
    }

    //
    // Shader Map
    //

    ShaderMap::ShaderMap(Type type)
    : NameMap()
    {
        pr_type = type;
    }

    ShaderMap::id_t ShaderMap::prGenerateId() {
        id_t id;
        switch (pr_type) {
            case vertex:
                id = glCreateShader(GL_VERTEX_SHADER);
                break;
            case tess_control:
                id = glCreateShader(GL_TESS_CONTROL_SHADER);
                break;
            case tess_eval:
                id = glCreateShader(GL_TESS_EVALUATION_SHADER);
                break;
            case geometry:
                id = glCreateShader(GL_GEOMETRY_SHADER);
                break;
            case fragment:
                id = glCreateShader(GL_FRAGMENT_SHADER);
                break;
            case compute:
                id = glCreateShader(GL_COMPUTE_SHADER);
                break;
        }
        return id;
    }

    void ShaderMap::load(id_t id, path_t file) {
        code_t code = prReadFile(file);
        prCompile(id, code);
    }

    ShaderMap::code_t ShaderMap::prReadFile(path_t file) {
        std::ifstream f_ifstream = std::ifstream(file, std::ios::in);
        if (!f_ifstream.is_open()) {
            std::cout << "Error: Attemping to load missing shader file." << std::endl;
            exit(EXIT_FAILURE);
        }
        
        std::stringstream f_stringstream;
        f_stringstream << f_ifstream.rdbuf();
        code_t f_shader_code = (char *)malloc((f_stringstream.str().length() + 1) * sizeof(char));
        strcpy(f_shader_code, f_stringstream.str().c_str());
        f_ifstream.close();
        std::cout << f_shader_code << std::endl;
        return f_shader_code;
    }

    void ShaderMap::prCompile(id_t id, code_t shader_code) {
        glShaderSource(id, 1, &shader_code, NULL);
        free(shader_code);
        glCompileShader(id);

        // Check if compilation was successful
        GLint f_status;
        GLint f_info_log_length;
        glGetShaderiv(id, GL_COMPILE_STATUS, &f_status);
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &f_info_log_length);
        if (f_info_log_length > 0) {
            char *f_info_log_message = (char *)malloc((f_info_log_length + 1) * sizeof(char));
            glGetShaderInfoLog(id, f_info_log_length, NULL, f_info_log_message);
            f_info_log_message[f_info_log_length] = '\0';
            std::cout << "Error: Failed to compile shader with message: " << std::endl;
            std::cout << f_info_log_message << std::endl;
            free(f_info_log_message);
            exit(EXIT_FAILURE);
        }        
    }

    void ShaderMap::operator>>(name_t name) {
        glDeleteShader((*this)[name]);
        NameMap::operator>>(name);
    }

    //
    // Program Map
    //

    ProgramMap::id_t ProgramMap::prGenerateId() {
        return glCreateProgram();
    }

    void ProgramMap::bind(id_t id) {
        glUseProgram(id);
    }

    void ProgramMap::attach(id_t program, id_t shader) {
        glAttachShader(program, shader);
    }

    void ProgramMap::detach(id_t program, id_t shader) {
        glDetachShader(program, shader);
    }

    void ProgramMap::finalize(id_t id) {
        glLinkProgram(id);

        // Check if compilation was successful
        GLint f_status;
        GLint f_info_log_length;
        glGetProgramiv(id, GL_COMPILE_STATUS, &f_status);
        glGetProgramiv(id, GL_INFO_LOG_LENGTH, &f_info_log_length);
        if (f_info_log_length > 0) {
            char *f_info_log_message = (char *)malloc((f_info_log_length + 1) * sizeof(char));
            glGetProgramInfoLog(id, f_info_log_length, NULL, f_info_log_message);
            f_info_log_message[f_info_log_length] = '\0';
            std::cout << "Error: Failed to link program with message: " << std::endl;
            std::cout << f_info_log_message << std::endl;
            free(f_info_log_message);
            exit(EXIT_FAILURE);
        }
    }
}