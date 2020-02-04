#include "SceneBuildLayer.h"


void SceneBuilder::Initialize()
{
	florp::app::Application* app = florp::app::Application::Get();
	
	using namespace florp::game;
	using namespace florp::graphics;
	
	auto* scene = SceneManager::RegisterScene("main");
	SceneManager::SetCurrentScene("main");

	MeshData data = ObjLoader::LoadObj("monkey.obj", glm::vec4(1.0f));
	MeshData data2 = ObjLoader::LoadObj("note.obj", glm::vec4(1.0f));

	Shader::Sptr shader = std::make_shared<Shader>();
	shader->LoadPart(ShaderStageType::VertexShader, "shaders/lighting.vs.glsl");
	shader->LoadPart(ShaderStageType::FragmentShader, "shaders/blinn-phong-multi.fs.glsl"); 
	shader->Link();

	Material::Sptr mat = std::make_shared<Material>(shader);
	mat->Set("a_AmbientColor", { 1.0f, 1.0f, 1.0f });
	mat->Set("a_AmbientPower", 0.1f);
	mat->Set("a_MatShininess", 256.0f);
	mat->Set("a_Lights[0].Pos", { 2, 0, 0 });
	mat->Set("a_Lights[0].Color", { 1.0f, 0.0f, 1.0f });  
	mat->Set("a_Lights[0].Attenuation", 1.0f / 100.0f);
	mat->Set("a_Lights[1].Pos", { -2, 0, 0 });
	mat->Set("a_Lights[1].Color", { 0.0f, 1.0f, 0.0f });
	mat->Set("a_Lights[1].Attenuation", 1.0f / 100.0f);
	mat->Set("a_Lights[2].Pos", { 2, 0, 0, });
	mat->Set("a_Lights[2].Color", { 0.25f, 0.75f, 0.25f });
	mat->Set("a_Lights[2].Attenuation", 1.0f / 100.0f);
	mat->Set("a_Lights[3].Pos", { -1, 1, 0});
	mat->Set("a_Lights[3].Color", { 0.5f, 0.0f, 0.5f });
	mat->Set("a_Lights[3].Attenuation", 1.0f / 100.0f);
	mat->Set("a_Lights[4].Pos", { -2, 1, -2 });
	mat->Set("a_Lights[4].Color", { 0.32f, 1.0f, 0.7f });
	mat->Set("a_Lights[4].Attenuation", 1.0f / 100.0f);


	mat->Set("a_EnabledLights", 5);

	mat->Set("a_ambient", false);
	mat->Set("a_diffuse", false);
	mat->Set("a_specular", false);
	mat->Set("a_rimLighting", false);
	mat->Set("a_diffuseWarp", false);
	mat->Set("a_specularWarp", false);

	// Our spinning monkey head
	//{
	//	entt::entity test = scene->CreateEntity();
	//	//scene->AddBehaviour<SampleBehaviour>(test, "Hello world!");
	//	RenderableComponent& renderable = scene->Registry().assign<RenderableComponent>(test);
	//	renderable.Mesh = MeshBuilder::Bake(data);
	//	renderable.Material = mat;
	//	Transform& t = scene->Registry().get<Transform>(test);
	//	scene->AddBehaviour<SampleBehaviour>(test, glm::vec3(0,45.0f,90.0f));
	//	
	//	t.SetPosition(glm::vec3(0, 0.0f, 0.0f));
	//}

	// Creates our main camera
	{
		// The color buffer should be marked as shader readable, so that we generate a texture for it
		RenderBufferDesc mainColor = RenderBufferDesc();
		mainColor.ShaderReadable = true;
		mainColor.Attachment = RenderTargetAttachment::Color0;
		mainColor.Format = RenderTargetType::Color24;

		// The depth attachment does not need to be a texture (and would cause issues since the format is DepthStencil)
		RenderBufferDesc depth = RenderBufferDesc();
		depth.ShaderReadable = true; 
		depth.Attachment = RenderTargetAttachment::Depth; 
		depth.Format = RenderTargetType::Depth32;


		// Our main frame buffer needs a color output, and a depth output
		FrameBuffer::Sptr buffer = std::make_shared<FrameBuffer>(app->GetWindow()->GetWidth(), app->GetWindow()->GetHeight());
		buffer->AddAttachment(mainColor);
		buffer->AddAttachment(depth);
		buffer->Validate();
		buffer->SetDebugName("MainBuffer");
		
		entt::entity camera = scene->CreateEntity();
		CameraComponent& cam = scene->Registry().assign<CameraComponent>(camera);
		cam.BackBuffer = buffer;
		cam.FrontBuffer = buffer->Clone();
		cam.IsMainCamera = true;
		cam.Projection = glm::perspective(glm::radians(60.0f), 1.0f, 0.01f, 1000.0f);
		Transform& t = scene->Registry().get<Transform>(camera);
		t.SetPosition(glm::vec3(0.0f, -10.0f, 0.0f)); 
		t.LookAt(glm::vec3(0.8f, 0.0f, 0.0f), glm::vec3(0.5f, 0.1f, 0.0f));
		scene->AddBehaviour<MovingBehaviour>(camera, glm::vec3(0.0f, 0.5f, 0.0f));
	}
	{    
		entt::entity test2 = scene->CreateEntity();
		RenderableComponent& renderable = scene->Registry().assign<RenderableComponent>(test2);
		renderable.Mesh = MeshBuilder::Bake(data2);
		renderable.Material = mat;
		Transform& n = scene->Registry().get<Transform>(test2);
		n.SetPosition(glm::vec3(0,0,0));
		n.SetEulerAngles(glm::vec3(0,0,0));


		float step = glm::two_pi<float>() / 10.0f; 
		// We'll create a ring of monkeys 
		for (int ix = 0; ix < 10; ix++) {
			entt::entity test = scene->CreateEntity();
			RenderableComponent& renderable = scene->Registry().assign<RenderableComponent>(test);
			renderable.Mesh = MeshBuilder::Bake(data);
			renderable.Material = mat;
			Transform& t = scene->Registry().get<Transform>(test);
			t.SetPosition(glm::vec3(glm::cos(step * ix) * 5.0f, 0.0f, glm::sin(step * ix) * 5.0f));
			t.SetEulerAngles(glm::vec3(-90.0f, glm::degrees(-step * ix), (ix < 3 ? (90.0f * step) : (ix > 7 ? 90.0f * step : -90.0f * step))));
			//t.Rotate(glm::vec3(10.0f, 10.0f, 10.0f));
			scene->AddBehaviour<RotateAround>(test, glm::vec3(0, 0, 0), glm::vec3(glm::cos(step * ix), 0.0f, glm::sin(step * ix)), 
												glm::vec3(1.0, 0.0, 1.0), 5.0, 2);
		}
	} 

	
}


