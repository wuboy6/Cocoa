#include "copch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Cocoa/Platform/OpenGL/OpenGLShader.h"

namespace Cocoa {
	Shader* Shader::Create(const std::string& filepath)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None: CO_CORE_ASSERT(false, "RendererAPI::None is not currently supported!") return nullptr;
		case RendererAPI::API::OpenGL: return new OpenGLShader(filepath);
		}

		CO_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None: CO_CORE_ASSERT(false, "RendererAPI::None is not currently supported!") return nullptr;
		case RendererAPI::API::OpenGL: return new OpenGLShader(vertexSrc, fragmentSrc);
		}

		CO_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}