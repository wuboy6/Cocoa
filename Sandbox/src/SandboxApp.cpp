#include <Cocoa.h>


class ExampleLayer : public Cocoa::Layer
{
public:
	ExampleLayer() :Layer("Example")
	{

	}

	void OnUpdate() override
	{
		if (Cocoa::Input::IsKeyPressed(CO_KEY_TAB))
			CO_TRACE("Tab key is pressed!");
	}


	void OnEvent(Cocoa::Event& event) override
	{
		if (event.GetEventType() == Cocoa::EventType::KeyPressed)
		{
			Cocoa::KeyPressedEvent& e = (Cocoa::KeyPressedEvent&)event;
			CO_TRACE("{0}", (char)e.GetKeyCode());
		}
	}
};

class Sandbox : public Cocoa::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}


};

Cocoa::Application* Cocoa::CreateApplication()
{
	return new Sandbox();
}
