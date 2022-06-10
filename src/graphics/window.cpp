#include "window.hpp"

#include <iostream>

namespace NRV::Graphics {
    //
    // Public methods
    //

    Window::Window(name_t name, bool is_fullscreen) {
        const GLFWvidmode* vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        createGLFWWindow(name, vidmode->width, vidmode->height, is_fullscreen);
    }

    Window::Window(name_t name, int width, int height, bool is_fullscreen) {
        createGLFWWindow(name, width, height, is_fullscreen);
    }

    Window::~Window() {
        close();
    }

    void Window::draw() {
        glfwSwapBuffers(pr_glfw_window);
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Window::close() {
        pr_is_closed = true;
    }

    bool Window::shouldClose() {
        return pr_is_closed;
    }
    
    GLFWwindow* Window::getGLFWWindow() {
        return pr_glfw_window;
    }

    //
    // Private Methods
    //

    void Window::createGLFWWindow(name_t name, int width, int height, bool is_fullscreen) {
        if (is_fullscreen)
            pr_glfw_window = glfwCreateWindow(width, height, name.c_str(), glfwGetPrimaryMonitor(), NULL);
        else
            pr_glfw_window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
        
        if (pr_glfw_window == NULL) {
            std::cout << "Error: Attempt to create window failed" << std::endl;
            exit(EXIT_FAILURE);
        }

        glfwMakeContextCurrent(pr_glfw_window);
        if (glewInit() != GLEW_OK) {
            std::cout << "Error: GLEW Init Failed" << std::endl;
            glfwTerminate();
            exit(EXIT_FAILURE);
        }
        glfwSetInputMode(pr_glfw_window, GLFW_STICKY_KEYS, GL_TRUE);

        glClearColor(0.3f, 0.0f, 0.3f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        pr_is_closed = false;
    }
}