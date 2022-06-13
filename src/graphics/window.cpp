#include "window.hpp"

#include <iostream>

namespace NRV::Graphics {
    //
    // Public methods
    //

    Window::Window(name_t name) {
        createGLFWWindow(name, 0, 0, true);
    }

    Window::Window(name_t name, int width, int height) {
        createGLFWWindow(name, width, height, false);
    }

    Window::~Window() {
        close();
    }

    void Window::draw() {
        glfwSwapBuffers(pr_glfw_window);
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
        if (is_fullscreen) {
            GLFWmonitor* monitor = glfwGetPrimaryMonitor();
            const GLFWvidmode* vidmode = glfwGetVideoMode(monitor);
            pr_glfw_window = glfwCreateWindow(vidmode->width, vidmode->height, name.c_str(), NULL, NULL);
            glfwSetWindowMonitor(pr_glfw_window, monitor, 0, 0, vidmode->width, vidmode->height, vidmode->refreshRate);
            pr_width = vidmode->width;
            pr_height = vidmode->height;
        }
        else {
            pr_glfw_window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
            pr_width = width;
            pr_height = height;
        }
        
        if (pr_glfw_window == NULL) {
            std::cout << "Error: Attempt to create window failed." << std::endl;
            exit(EXIT_FAILURE);
        }

        glfwMakeContextCurrent(pr_glfw_window);
        if (glewInit() != GLEW_OK) {
            std::cout << "Error: GLEW initialization Failed." << std::endl;
            glfwTerminate();
            exit(EXIT_FAILURE);
        }
        glfwSetInputMode(pr_glfw_window, GLFW_STICKY_KEYS, GL_TRUE);

        glClearColor(1.0f, 0.0f, 1.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        pr_is_closed = false;
    }

    float Window::getWidth() {
        return pr_width;
    }

    float Window::getHeight() {
        return pr_height;
    }
}