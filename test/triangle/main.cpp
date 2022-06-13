#include "../../src/graphics/gl_session.hpp"
#include "../../src/graphics/window.hpp"
#include "../../src/graphics/gl_object_map.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace NRV::Graphics;

int main()
{
    GLSession f_gl_session = GLSession();
    Window f_window = Window("Triangle");

    //
    // Vertex Array
    //

    VertexArrayMap f_vam = VertexArrayMap();
    VertexArrayMap::id_t f_va_id = f_vam << "vam";
    f_vam.bind(f_va_id);

	static const GLfloat g_vertex_buffer_data[] = { 
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f,
	};

    VertexBufferMap f_vbm = VertexBufferMap();
    VertexBufferMap::id_t f_vb_id = f_vbm << "vb";
    f_vbm.bind(f_vb_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    //
    // Shader
    //

    ShaderMap f_sm_vertex(ShaderMap::vertex);
    ShaderMap::id_t f_vs_id = f_sm_vertex << "vs";
    f_sm_vertex.load(f_vs_id, "shaders/test.vertex.glsl");

    ShaderMap f_sm_fragment(ShaderMap::fragment);
    ShaderMap::id_t f_fs_id = f_sm_fragment << "fs";
    f_sm_fragment.load(f_fs_id, "shaders/test.fragment.glsl");

    ProgramMap f_pm = ProgramMap();
    ProgramMap::id_t f_p_id = f_pm << "p";

    f_pm.attach(f_p_id, f_vs_id);
    f_pm.attach(f_p_id, f_fs_id);
    f_pm.finalize(f_p_id);
    f_pm.detach(f_p_id, f_vs_id);
    f_pm.detach(f_p_id, f_fs_id);

    f_sm_vertex >> "vs";
    f_sm_fragment >> "fs";

    f_pm.bind(f_p_id);
    glUniform2f(glGetUniformLocation(f_p_id, "screenSize"), f_window.getWidth(), f_window.getHeight());

    //
    // Draw Loop
    //

	while( glfwGetKey(f_window.getGLFWWindow(), GLFW_KEY_ESCAPE ) != GLFW_PRESS
        && !glfwWindowShouldClose(f_window.getGLFWWindow()) ) {
        // Shader
        f_pm.bind(f_p_id);
        
        // Layout of the data
        f_vbm.bind(f_vb_id);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(
			0,          // Attribute 0
			3,          // Count
			GL_FLOAT,   // Type
			GL_FALSE,   // Not normalized
			0,          // Stride
			(void*)0    // Offset
		);
        // Draw triangles, offset, 3 vertices (1 triangle)
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableVertexAttribArray(0);

        f_window.draw();
	}

    //
    // Clean Maps
    //

	glDeleteVertexArrays(1, &f_va_id);
	glDeleteBuffers(1, &f_vb_id);
    glDeleteProgram(f_p_id);
}
