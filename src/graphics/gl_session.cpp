#include "gl_session.hpp"

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>


namespace NRV::Graphics {
    GLSession::GLSession() {
        if(!glfwInit()) {
            std::cout << "Error: GLFW Init Failed" << std::endl;
            exit(EXIT_FAILURE);
        }

        prApplyWindowHints();
    }

    GLSession::~GLSession() {
        glfwTerminate();
    }

    void GLSession::prApplyWindowHints() {
        // 4x antialiasing
        glfwWindowHint(GLFW_SAMPLES, 4);
        // OpenGL v3.3
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        // For MacOS
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        // Don't allow deprecated functions
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    }
}