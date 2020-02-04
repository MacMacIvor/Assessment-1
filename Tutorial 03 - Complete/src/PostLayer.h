#pragma once
#include "florp/app/ApplicationLayer.h"
#include "FrameBuffer.h"
#include "florp/graphics/Mesh.h"
#include "florp/graphics/Shader.h"
#include "CubeLUT.h"


class PostLayer : public florp::app::ApplicationLayer
{
public:
	PostLayer();
	virtual void OnWindowResize(uint32_t width, uint32_t height) override;
	virtual void PostRender() override;

protected:
	FrameBuffer::Sptr myMainFrameBuffer;
	florp::graphics::Mesh::Sptr myFullscreenQuad;

	struct PostPass {
		typedef std::shared_ptr<PostPass> Sptr;    
		florp::graphics::Shader::Sptr Shader;   
		FrameBuffer::Sptr         Output;  
		
		struct Input { 
			Sptr                      Pass;     
			RenderTargetAttachment    Attachment = RenderTargetAttachment::Color0;   
			bool                   UsePrevFrame = false; 
		}; 
		std::vector<Input>            Inputs;
		float                     ResolutionMultiplier = 1.0f;
	};  
	std::vector<PostPass::Sptr> myPasses;
	PostPass::Sptr __CreatePass(const char* fragmentShader, float scale = 1.0f) const;
private:
	bool g_warm = false;
	bool g_cool = false;
	bool g_grey = false;
	bool buffer8 = false;
	bool buffer9 = false;
	bool buffer0 = false;
};
