#pragma once

#include "Cocoa/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Cocoa {

	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		void virtual Init() override; 
		void virtual SwapBuffers() override;

	private:
		GLFWwindow* m_WindowHandle;
	};
}