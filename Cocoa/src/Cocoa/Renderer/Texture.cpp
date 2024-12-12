#include "copch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Cocoa/Platform/OpenGL/OpenGLTexture.h"

namespace Cocoa {
	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: CO_CORE_ASSERT(false, "RendererAPI::None is not currently supported!") return nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture2D>(path);
		}

		CO_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}