#include <Cocoa.h>

#include "Cocoa/Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


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

		Cocoa::Ref<Cocoa::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Cocoa::VertexBuffer::Create(vertices, sizeof(vertices)));

		Cocoa::BufferLayout layout = {
			{ Cocoa::ShaderDataType::Float3, "a_Position"},
			{ Cocoa::ShaderDataType::Float4, "a_Color" }
		};

		vertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(vertexBuffer);
		//Index Buffer

		unsigned int indices[3] = { 0 , 1 , 2 };
		Cocoa::Ref<Cocoa::IndexBuffer> indexBuffer;
		indexBuffer.reset(Cocoa::IndexBuffer::Create(indices, 3));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Cocoa::VertexArray::Create());

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Cocoa::Ref<Cocoa::VertexBuffer> squareVB;
		squareVB.reset(Cocoa::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{Cocoa::ShaderDataType::Float3, "A_Position"},
			{Cocoa::ShaderDataType::Float2, "A_TexCoord"}
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		unsigned int squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Cocoa::Ref<Cocoa::IndexBuffer> squareIB;
		squareIB.reset(Cocoa::IndexBuffer::Create(squareIndices, 6));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;
			
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position =u_ViewProjection * u_Transform * vec4(a_Position , 1.0);
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

		m_Shader.reset(Cocoa::Shader::Create(vertexSrc, fragmentSrc));

		std::string flatColorShadervertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			
			void main()
			{
				v_Position = a_Position;
				gl_Position =u_ViewProjection * u_Transform * vec4(a_Position , 1.0);
			}
		)";

		std::string flatColorShaderfragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			uniform vec3 u_Color;
			
			void main()
			{
				color = vec4(u_Color, 1.0f);
			}
		)";

		m_FlatColorShader.reset(Cocoa::Shader::Create(flatColorShadervertexSrc, flatColorShaderfragmentSrc));

		std::string textureShadervertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec2 v_TexCoord;
			
			void main()
			{
				v_TexCoord = a_TexCoord;
				gl_Position =u_ViewProjection * u_Transform * vec4(a_Position , 1.0);
			}
		)";

		std::string textureShaderfragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec2 v_TexCoord;

			uniform sampler2D u_Texture;
			
			void main()
			{
				color = texture(u_Texture, v_TexCoord);
			}
		)";

		m_TextureShader.reset(Cocoa::Shader::Create(textureShadervertexSrc, textureShaderfragmentSrc));

		m_Texture = Cocoa::Texture2D::Create("assets/textures/naxigui.jpg");

		std::dynamic_pointer_cast<Cocoa::OpenGLShader>(m_TextureShader)->Bind();
		std::dynamic_pointer_cast<Cocoa::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);

	}

	void OnUpdate(Cocoa::Timestep ts) override
	{

		if (Cocoa::Input::IsKeyPressed(CO_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		else if (Cocoa::Input::IsKeyPressed(CO_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;

		if (Cocoa::Input::IsKeyPressed(CO_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;
		else if (Cocoa::Input::IsKeyPressed(CO_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;

		if (Cocoa::Input::IsKeyPressed(CO_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		else if (Cocoa::Input::IsKeyPressed(CO_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed * ts;

		Cocoa::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Cocoa::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Cocoa::Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Cocoa::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Cocoa::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Cocoa::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}

		m_Texture->Bind();
		Cocoa::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		// Triangle
		// Cocoa::Renderer::Submit(m_Shader, m_VertexArray);

		Cocoa::Renderer::EndScene();

	}


	void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
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
	Cocoa::Ref<Cocoa::Shader> m_Shader;
	Cocoa::Ref<Cocoa::VertexArray> m_VertexArray;

	Cocoa::Ref<Cocoa::Shader> m_FlatColorShader, m_TextureShader;
	Cocoa::Ref<Cocoa::VertexArray> m_SquareVA;

	Cocoa::Ref<Cocoa::Texture> m_Texture;

	Cocoa::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 1.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 30.0f;

	glm::vec3 m_SquareColor = { 0.2f , 0.3f, 0.8f };
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
