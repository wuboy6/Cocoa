#include "copch.h"
#include "RenderCommand.h"

#include "Cocoa/Platform/OpenGL/OpenGLRendererAPI.h"

namespace Cocoa {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}