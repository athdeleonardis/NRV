#include "../../src/graphics/window.hpp"
#include "../../src/graphics/gl_session.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace NRV::Graphics;

int main() {
    GLSession f_gl_session = GLSession();
    Window f_window = Window("Hello World!", 640, 480);
    while (!f_window.shouldClose()) {
        f_window.draw();
        if (glfwGetKey(f_window.getGLFWWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
            f_window.close();
    }
    // GLSession destructor closes the active window and etc
}