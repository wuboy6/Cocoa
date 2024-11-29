#pragma once


#include "Cocoa/Layer.h"

#include "Cocoa/Events/MouseEvent.h"
#include "Cocoa/Events/KeyEvent.h"
#include "Cocoa/Events/ApplicationEvent.h"

namespace Cocoa {

	class COCOA_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};
}