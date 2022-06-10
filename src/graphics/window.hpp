#ifndef NRV_WINDOW
#define NRV_WINDOW

#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace NRV::Graphics {

    class Window {
    public:
        typedef std::string name_t;
    private:
        GLFWwindow* pr_glfw_window;
        bool pr_is_closed;
    private:
        void createGLFWWindow(name_t name, int width, int height, bool is_fullscreen);
    public:
        Window(name_t name, bool is_fullscreen);
        Window(name_t name, int width, int height, bool is_fullscreen);
        ~Window();
        void draw();
        void close();
        bool shouldClose();
        GLFWwindow* getGLFWWindow();
    };
}

#endif
