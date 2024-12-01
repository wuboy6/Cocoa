#include "copch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <GL/GL.h>

namespace Cocoa {



	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		:m_WindowHandle(windowHandle)
	{
		CO_CORE_ASSERT(windowHandle, "Window handle is null")
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		CO_CORE_ASSERT(status, "Failed to initailize Glad!");

		CO_CORE_INFO("OpenGL Info:");
		CO_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		CO_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		CO_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
	}
	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}