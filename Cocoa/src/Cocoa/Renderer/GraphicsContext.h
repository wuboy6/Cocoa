#pragma once

namespace Cocoa {

	class GraphicsContext
	{
	public:
		void virtual Init() = 0;
		void virtual SwapBuffers() = 0;
	};


}