#include "PostLayer.h"
#include "florp/app/Application.h"
#include "florp/game/SceneManager.h"
#include "FrameState.h"

PostLayer::PostLayer() {
	florp::app::Application* app = florp::app::Application::Get();
	
	// The color buffer should be marked as shader readable, so that we generate a texture for it
	RenderBufferDesc mainColor = RenderBufferDesc();
	mainColor.ShaderReadable = true;
	mainColor.Attachment = RenderTargetAttachment::Color0;
	mainColor.Format = RenderTargetType::Color24;

	// Create our fullscreen quad mesh
	{
		float vert[] = {
			-1.0f, -1.0f,  0.0f, 0.0f,
			 1.0f, -1.0f,  1.0f, 0.0f,
			-1.0f,  1.0f,  0.0f, 1.0f,
			 1.0f,  1.0f,  1.0f, 1.0f
		};
		uint32_t indices[] = {
			0, 1, 2,
			1, 3, 2
		};
		florp::graphics::BufferLayout layout = {
			{ "inPosition", florp::graphics::ShaderDataType::Float2 },
			{ "inUV",       florp::graphics::ShaderDataType::Float2 }
		};

		myFullscreenQuad = std::make_shared<florp::graphics::Mesh>(vert, 4, layout, indices, 6);
	}
	
	auto highlight = __CreatePass("shaders/post/bloom_highlight.fs.glsl");
	highlight->Shader->SetUniform("a_BloomThreshold", 0.75f); 
	// Add the pass to the post processing stack
	myPasses.push_back(highlight);
// Horizontal blur pass auto 
	auto hBlur = __CreatePass("shaders/post/blur_gaussian_5.fs.glsl");
	hBlur->Shader->SetUniform("isHorizontal", 1); 
	hBlur->Output->SetDebugName("HorizontalBuffer");
// Vertical blur pass 
	auto vBlur = __CreatePass("shaders/post/blur_gaussian_5.fs.glsl");
	vBlur->Shader->SetUniform("isHorizontal", 0); 
	vBlur->Output->SetDebugName("VerticalBuffer");

	for (int ix = 0; ix < 10; ix++) { 
		myPasses.push_back(hBlur);
		myPasses.push_back(vBlur); 
	}

	// Our additive pass will add the color from the scene, and add the blurred highlight to it 
	auto additive = __CreatePass("shaders/post/additive_blend.fs.glsl"); 
	additive->Inputs.push_back({ nullptr });
	additive->Inputs.push_back({ vBlur });
	// Add the pass to the post processing stack 
	myPasses.push_back(additive); 



	// Our first pass will be to make our checkerboard effect
	//But I don't want it so....
	//It's gone!

	
	auto motionBlur = __CreatePass("shaders/post/motion_blur.fs.glsl"); 
	motionBlur->Inputs.push_back({ nullptr, RenderTargetAttachment::Depth }); 
	// 1 will hold this frame's depth 
	// Add the pass to the post processing stack 
	//myPasses.push_back(motionBlur); 

	

	CubeLUT theCube;

	// Add the pass to the post processing stack 
	auto tint = __CreatePass("shaders/post/warm.fs.glsl");
	theCube.SaveCubeData("Warm.CUBE");
	//tint->Shader->SetUniform("warm", theCube.LUT3D);
	auto hello = theCube.LUT3D;
	tint->Inputs.push_back({ nullptr, RenderTargetAttachment::Depth });
	myPasses.push_back(tint);
	
	
	//florp::graphics::Texture2D();
	//florp::graphics::Texture2D::Sptr albedo = florp::graphics::Texture2D::LoadFromFile("LUT/WarmOut.CUBE");

	//}
	
	//int main(int argc, char* const argv[]) {
	//CubeLUT theCube;
	//enum { OK = 0, ErrorOpenInFile = 100, ErrorOpenOutFile };
	//if (argc < 2 || 3 < argc) {
	//	std::cout << "Usage: " << argv[0] << " cubeFileIn [cubefileOut]" << std::endl;
	//	return OK;
	//}
	//
	////Load a Cube
	//std::ifstream infile(argv[1]);
	//if (!infile.good()) {
	//	std::cout << "Could not open input file " << argv[1] << std::endl;
	//	return ErrorOpenInFile;
	//}
	//int ret = theCube.LoadCubeFile(infile);
	//infile.close();
	//if (ret != OK) {
	//	std::cout << "Could not parse the cube info in the input file. Return code = " << ret << std::endl;
	//	return theCube.status;
	//}
	////Save a Cube
	//if (argc > 2) {
	//	std::ofstream outfile(argv[2], std::fstream::trunc);
	//	if (!outfile.good()) {
	//		std::cout << "Could not open output file " << argv[1] << std::endl;
	//		return ErrorOpenOutFile;
	//	}
	//	int ret = theCube.SaveCubeFile(outfile);
	//	outfile.close();
	//	if (ret != OK) {
	//		std::cout << "Could not write the cube to the output file. Return code = " << ret << std::endl;
	//		return theCube.status;
	//	}
	//}
	//return OK;

}

void PostLayer::OnWindowResize(uint32_t width, uint32_t height) {
	
	for (auto& pass : myPasses) { 
		pass->Output->Resize((uint32_t)(width * pass->ResolutionMultiplier), (uint32_t)(height * pass->ResolutionMultiplier)); 
	}
}

PostLayer::PostPass::Sptr PostLayer::__CreatePass(const char* fragmentShader, float scale) const {
	florp::app::Application* app = florp::app::Application::Get();    
	RenderBufferDesc mainColor = RenderBufferDesc();  
	mainColor.ShaderReadable = true;   
	mainColor.Attachment = RenderTargetAttachment::Color0;  
	mainColor.Format = RenderTargetType::Color24;    
	auto shader = std::make_shared<florp::graphics::Shader>(); 
	shader->LoadPart(florp::graphics::ShaderStageType::VertexShader, "shaders/post/post.vs.glsl"); 
	shader->LoadPart(florp::graphics::ShaderStageType::FragmentShader, fragmentShader);   
	shader->Link();
	// Each pass gets it's own copy of the frame buffer to avoid pipeline stalls
	auto output = std::make_shared<FrameBuffer>(app->GetWindow()->GetWidth() * scale, app->GetWindow()->GetHeight() * scale); 
	output->AddAttachment(mainColor); 
	output->Validate();
	// Return the pass that we just created  
	auto result = std::make_shared<PostPass>(); 
	result->Shader = shader;  
	result->Output = output; 
	return result; 
}


void PostLayer::PostRender() {
	if (GetKeyState(0x38) & 0x8000) {
		if (!buffer8) {
			g_warm = !g_warm;
		}
		buffer8 = true;
	}
	else {
		buffer8 = false;
	}
	if (GetKeyState(0x39) & 0x8000) {
		if (!buffer9) {
			g_cool = !g_cool;
		}
		buffer9 = true;
	}
	else {
		buffer9 = false;
	}
	if (GetKeyState(0x30) & 0x8000) {
		if (!buffer0) {
			g_grey = !g_grey;
		}
		buffer0 = true;
	}
	else {
		buffer0 = false;
	}

	// We grab the application singleton to get the size of the screen
	florp::app::Application* app = florp::app::Application::Get();
	
	// We'll get the back buffer from the frame state const 
	AppFrameState& state = CurrentRegistry().ctx<AppFrameState>(); 
	FrameBuffer::Sptr mainBuffer = state.Current.Output;
	
	// Unbind the main framebuffer, so that we can read from it
	//mainBuffer->UnBind();
	glDisable(GL_DEPTH_TEST);

	// The last output will start as the output from the rendering
	FrameBuffer::Sptr lastPass = mainBuffer;

	for (const PostPass::Sptr& pass : myPasses) {
		// We'll bind our post-processing output as the current render target and clear it    
		pass->Output->Bind(RenderTargetBinding::Draw);
		glClear(GL_COLOR_BUFFER_BIT);
		// Set the viewport to be the entire size of the passes output   
		glViewport(0, 0, pass->Output->GetWidth(), pass->Output->GetHeight());
		// Use the post processing shader to draw the fullscreen quad   
		pass->Shader->Use();
		lastPass->Bind(0);

		pass->Shader->SetUniform("warm", g_warm);
		pass->Shader->SetUniform("cool", g_cool);
		pass->Shader->SetUniform("grey", g_grey);
		pass->Shader->SetUniform("xImage", 0);
		// We'll bind all the inputs as textures in the order they were added (starting at index 1)   
		// We'll iterate over all of our render passes
		for (size_t ix = 0; ix < pass->Inputs.size(); ix++) {
			const auto& input = pass->Inputs[ix];
			if (input.Pass == nullptr) {
				if (input.UsePrevFrame && state.Last.Output != nullptr) {
					state.Last.Output->Bind(ix + 1, input.Attachment);
				}
				else {
					mainBuffer->Bind(ix + 1, input.Attachment);
				}
			}
			else {
				input.Pass->Output->Bind(ix + 1, input.Attachment);
			}
		}
		pass->Shader->SetUniform("xScreenRes", glm::ivec2(pass->Output->GetWidth(), pass->Output->GetHeight()));
		myFullscreenQuad->Draw();
		// Unbind the output pass so that we can read from it    
		pass->Output->UnBind();
		// Update the last pass output to be this passes output   
		lastPass = pass->Output;
		// Expose camera state to shaders 
		pass->Shader->SetUniform("a_View", state.Current.View); 
		pass->Shader->SetUniform("a_Projection", state.Current.Projection); 
		pass->Shader->SetUniform("a_ViewProjection", state.Current.ViewProjection); 
		pass->Shader->SetUniform("a_ViewProjectionInv", glm::inverse(state.Current.ViewProjection));
		pass->Shader->SetUniform("a_PrevView", state.Last.View); 
		pass->Shader->SetUniform("a_PrevProjection", state.Last.Projection); 
		pass->Shader->SetUniform("a_PrevViewProjection", state.Last.ViewProjection); 
		pass->Shader->SetUniform("a_PrevViewProjectionInv", glm::inverse(state.Last.ViewProjection));
	}
	
		


	// Bind the last buffer we wrote to as our source for read operations
	lastPass->Bind(RenderTargetBinding::Read);
	// Copies the image from lastPass into the default back buffer
	FrameBuffer::Blit({ 0, 0, lastPass->GetWidth(), lastPass->GetHeight()},
		{0, 0, app->GetWindow()->GetWidth(), app->GetWindow()->GetHeight()}, BufferFlags::All, florp::graphics::MagFilter::Nearest);

	// Unbind the last buffer from read operations, so we can write to it again later
	lastPass->UnBind();
}
