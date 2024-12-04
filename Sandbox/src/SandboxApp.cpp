#include <Cocoa.h>
#include "imgui/imgui.h"


class ExampleLayer : public Cocoa::Layer
{
public:
	ExampleLayer() 
		:Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{

		//Vertex Array
		m_VertexArray.reset(Cocoa::VertexArray::Create());

		//Vertex Buffer

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f,0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f,0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f,0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<Cocoa::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Cocoa::VertexBuffer::Create(vertices, sizeof(vertices)));

		Cocoa::BufferLayout layout = {
			{ Cocoa::ShaderDataType::Float3, "a_Position"},
			{ Cocoa::ShaderDataType::Float4, "a_Color" }
		};

		vertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(vertexBuffer);
		//Index Buffer

		unsigned int indices[3] = { 0 , 1 , 2 };
		std::shared_ptr<Cocoa::IndexBuffer> indexBuffer;
		indexBuffer.reset(Cocoa::IndexBuffer::Create(indices, 3));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Cocoa::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};

		std::shared_ptr<Cocoa::VertexBuffer> squareVB;
		squareVB.reset(Cocoa::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{Cocoa::ShaderDataType::Float3, "A_position"}
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		unsigned int squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Cocoa::IndexBuffer> squareIB;
		squareIB.reset(Cocoa::IndexBuffer::Create(squareIndices, 6));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;
			
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position =u_ViewProjection * vec4(a_Position , 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;
			
			void main()
			{
				color = vec4(v_Position*0.5 + 0.5,1.0);
				color = v_Color;
			}
		)";

		m_Shader.reset(new Cocoa::Shader(vertexSrc, fragmentSrc));

		std::string blueShadervertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			
			void main()
			{
				v_Position = a_Position;
				gl_Position =u_ViewProjection * vec4(a_Position , 1.0);
			}
		)";

		std::string blueShaderfragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			
			void main()
			{
				color = vec4(v_Position*0.5 + 0.5,1.0);
			}
		)";

		m_BlueShader.reset(new Cocoa::Shader(blueShadervertexSrc, blueShaderfragmentSrc));
	}

	void OnUpdate() override
	{
		if (Cocoa::Input::IsKeyPressed(CO_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed;
		else if (Cocoa::Input::IsKeyPressed(CO_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed;

		if (Cocoa::Input::IsKeyPressed(CO_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed;
		else if (Cocoa::Input::IsKeyPressed(CO_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed;

		if (Cocoa::Input::IsKeyPressed(CO_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed;
		else if (Cocoa::Input::IsKeyPressed(CO_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed;

		Cocoa::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Cocoa::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Cocoa::Renderer::BeginScene(m_Camera);

		Cocoa::Renderer::Submit(m_BlueShader, m_SquareVA);
		Cocoa::Renderer::Submit(m_Shader, m_VertexArray);

		Cocoa::Renderer::EndScene();

	}


	void OnImGuiRender() override
	{

	}

	void OnEvent(Cocoa::Event& event) override
	{
		/*Cocoa::EventDispatcher dispacher(event);
		dispacher.Dispatch<Cocoa::KeyPressedEvent>(CO_BIND_EVENT_FN(ExampleLayer::OnKeyPressedEvent));*/
	}

	//bool OnKeyPressedEvent(Cocoa::KeyPressedEvent& event)
	//{
	//	/*if (event.GetKeyCode() == CO_KEY_LEFT)
	//		m_CameraPosition.x -= m_CameraMoveSpeed;

	//	if (event.GetKeyCode() == CO_KEY_RIGHT)
	//		m_CameraPosition.x += m_CameraMoveSpeed;

	//	if (event.GetKeyCode() == CO_KEY_DOWN)
	//		m_CameraPosition.y -= m_CameraMoveSpeed;

	//	if (event.GetKeyCode() == CO_KEY_UP)
	//		m_CameraPosition.y += m_CameraMoveSpeed;*/

	//	return false;
	//}
private:
	std::shared_ptr<Cocoa::Shader> m_Shader;
	std::shared_ptr<Cocoa::VertexArray> m_VertexArray;

	std::shared_ptr<Cocoa::Shader> m_BlueShader;
	std::shared_ptr<Cocoa::VertexArray> m_SquareVA;

	Cocoa::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 0.06f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 0.2f;
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
