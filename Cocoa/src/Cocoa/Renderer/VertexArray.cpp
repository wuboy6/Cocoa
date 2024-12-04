#include "copch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Cocoa/Platform/OpenGL/OpenGLVertexArray.h"

namespace Cocoa {
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: CO_CORE_ASSERT(false, "RendererAPI::None is not currently supported!") return nullptr;
		case RendererAPI::API::OpenGL: return new OpenGLVertexArray();
		}

		CO_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}