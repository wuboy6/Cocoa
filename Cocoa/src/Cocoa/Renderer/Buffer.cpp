#include "copch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "Cocoa/Platform/OpenGL/OpenGLBuffer.h"

namespace Cocoa {

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None : CO_CORE_ASSERT(false, "RendererAPI::None is not currently supported!") return nullptr;
		case RendererAPI::API::OpenGL: return new OpenGLVertexBuffer(vertices, size);
		}

		CO_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: CO_CORE_ASSERT(false, "RendererAPI::None is not currently supported!") return nullptr;
		case RendererAPI::API::OpenGL: return new OpenGLIndexBuffer(indices, count);
		}

		CO_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}