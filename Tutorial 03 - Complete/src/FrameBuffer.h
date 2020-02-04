#pragma once
#include <GLM/vec2.hpp>
#include <GLM/vec4.hpp>
#include <glad/glad.h>
#include "florp/graphics/IGraphicsResource.h"
#include "florp/graphics/TextureEnums.h"
#include "EnumToString.h"
#include <unordered_map>
#include "florp/graphics/Texture2D.h"



ENUM(RenderTargetAttachment, uint32_t,
     Color0       = GL_COLOR_ATTACHMENT0,
     Color1       = GL_COLOR_ATTACHMENT1,
     Color2       = GL_COLOR_ATTACHMENT2,
     Color3       = GL_COLOR_ATTACHMENT3,
     Color4       = GL_COLOR_ATTACHMENT4,
     Color5       = GL_COLOR_ATTACHMENT5,
     Color6       = GL_COLOR_ATTACHMENT6,
     Color7       = GL_COLOR_ATTACHMENT7,
     Depth        = GL_DEPTH_ATTACHMENT,
     DepthStencil = GL_DEPTH_STENCIL_ATTACHMENT,
     Stencil      = GL_STENCIL_ATTACHMENT
);

ENUM(RenderTargetType, uint32_t,
	Color48      = GL_SRGB_ALPHA,
	Color32      = GL_RGBA8,
	Color24      = GL_RGB8,
	Color16      = GL_RG8,
	Color8       = GL_R8,
	DepthStencil = GL_DEPTH24_STENCIL8,
	Depth16      = GL_DEPTH_COMPONENT16,
	Depth24      = GL_DEPTH_COMPONENT24,
	Depth32      = GL_DEPTH_COMPONENT32,
	Stencil4     = GL_STENCIL_INDEX4,
	Stencil8     = GL_STENCIL_INDEX8,
	Stencil16    = GL_STENCIL_INDEX16,
	Default      = 0
	//GL_FRAMEBUFFER_SRGB
);

typedef enum D3DRENDERSTATETYPE {
  D3DRS_ZENABLE = 7,
  D3DRS_FILLMODE = 8,
  D3DRS_SHADEMODE = 9,
  D3DRS_ZWRITEENABLE = 14,
  D3DRS_ALPHATESTENABLE = 15,
  D3DRS_LASTPIXEL = 16,
  D3DRS_SRCBLEND = 19,
  D3DRS_DESTBLEND = 20,
  D3DRS_CULLMODE = 22,
  D3DRS_ZFUNC = 23,
  D3DRS_ALPHAREF = 24,
  D3DRS_ALPHAFUNC = 25,
  D3DRS_DITHERENABLE = 26,
  D3DRS_ALPHABLENDENABLE = 27,
  D3DRS_FOGENABLE = 28,
  D3DRS_SPECULARENABLE = 29,
  D3DRS_FOGCOLOR = 34,
  D3DRS_FOGTABLEMODE = 35,
  D3DRS_FOGSTART = 36,
  D3DRS_FOGEND = 37,
  D3DRS_FOGDENSITY = 38,
  D3DRS_RANGEFOGENABLE = 48,
  D3DRS_STENCILENABLE = 52,
  D3DRS_STENCILFAIL = 53,
  D3DRS_STENCILZFAIL = 54,
  D3DRS_STENCILPASS = 55,
  D3DRS_STENCILFUNC = 56,
  D3DRS_STENCILREF = 57,
  D3DRS_STENCILMASK = 58,
  D3DRS_STENCILWRITEMASK = 59,
  D3DRS_TEXTUREFACTOR = 60,
  D3DRS_WRAP0 = 128,
  D3DRS_WRAP1 = 129,
  D3DRS_WRAP2 = 130,
  D3DRS_WRAP3 = 131,
  D3DRS_WRAP4 = 132,
  D3DRS_WRAP5 = 133,
  D3DRS_WRAP6 = 134,
  D3DRS_WRAP7 = 135,
  D3DRS_CLIPPING = 136,
  D3DRS_LIGHTING = 137,
  D3DRS_AMBIENT = 139,
  D3DRS_FOGVERTEXMODE = 140,
  D3DRS_COLORVERTEX = 141,
  D3DRS_LOCALVIEWER = 142,
  D3DRS_NORMALIZENORMALS = 143,
  D3DRS_DIFFUSEMATERIALSOURCE = 145,
  D3DRS_SPECULARMATERIALSOURCE = 146,
  D3DRS_AMBIENTMATERIALSOURCE = 147,
  D3DRS_EMISSIVEMATERIALSOURCE = 148,
  D3DRS_VERTEXBLEND = 151,
  D3DRS_CLIPPLANEENABLE = 152,
  D3DRS_POINTSIZE = 154,
  D3DRS_POINTSIZE_MIN = 155,
  D3DRS_POINTSPRITEENABLE = 156,
  D3DRS_POINTSCALEENABLE = 157,
  D3DRS_POINTSCALE_A = 158,
  D3DRS_POINTSCALE_B = 159,
  D3DRS_POINTSCALE_C = 160,
  D3DRS_MULTISAMPLEANTIALIAS = 161,
  D3DRS_MULTISAMPLEMASK = 162,
  D3DRS_PATCHEDGESTYLE = 163,
  D3DRS_DEBUGMONITORTOKEN = 165,
  D3DRS_POINTSIZE_MAX = 166,
  D3DRS_INDEXEDVERTEXBLENDENABLE = 167,
  D3DRS_COLORWRITEENABLE = 168,
  D3DRS_TWEENFACTOR = 170,
  D3DRS_BLENDOP = 171,
  D3DRS_POSITIONDEGREE = 172,
  D3DRS_NORMALDEGREE = 173,
  D3DRS_SCISSORTESTENABLE = 174,
  D3DRS_SLOPESCALEDEPTHBIAS = 175,
  D3DRS_ANTIALIASEDLINEENABLE = 176,
  D3DRS_MINTESSELLATIONLEVEL = 178,
  D3DRS_MAXTESSELLATIONLEVEL = 179,
  D3DRS_ADAPTIVETESS_X = 180,
  D3DRS_ADAPTIVETESS_Y = 181,
  D3DRS_ADAPTIVETESS_Z = 182,
  D3DRS_ADAPTIVETESS_W = 183,
  D3DRS_ENABLEADAPTIVETESSELLATION = 184,
  D3DRS_TWOSIDEDSTENCILMODE = 185,
  D3DRS_CCW_STENCILFAIL = 186,
  D3DRS_CCW_STENCILZFAIL = 187,
  D3DRS_CCW_STENCILPASS = 188,
  D3DRS_CCW_STENCILFUNC = 189,
  D3DRS_COLORWRITEENABLE1 = 190,
  D3DRS_COLORWRITEENABLE2 = 191,
  D3DRS_COLORWRITEENABLE3 = 192,
  D3DRS_BLENDFACTOR = 193,
  D3DRS_SRGBWRITEENABLE = 194,
  D3DRS_DEPTHBIAS = 195,
  D3DRS_WRAP8 = 198,
  D3DRS_WRAP9 = 199,
  D3DRS_WRAP10 = 200,
  D3DRS_WRAP11 = 201,
  D3DRS_WRAP12 = 202,
  D3DRS_WRAP13 = 203,
  D3DRS_WRAP14 = 204,
  D3DRS_WRAP15 = 205,
  D3DRS_SEPARATEALPHABLENDENABLE = 206,
  D3DRS_SRCBLENDALPHA = 207,
  D3DRS_DESTBLENDALPHA = 208,
  D3DRS_BLENDOPALPHA = 209,
  D3DRS_FORCE_DWORD = 0x7fffffff
} D3DRENDERSTATETYPE, * LPD3DRENDERSTATETYPE;
ENUM_FLAGS(RenderTargetBinding, GLenum,
	None  = 0,
	Draw  = GL_DRAW_FRAMEBUFFER,
	Write = GL_DRAW_FRAMEBUFFER,
	Read  = GL_READ_FRAMEBUFFER,
	Both  = GL_FRAMEBUFFER
);

ENUM_FLAGS(BufferFlags, GLenum,
	None    = 0,
	Color   = GL_COLOR_BUFFER_BIT,
	Depth   = GL_DEPTH_BUFFER_BIT,
	Stencil = GL_STENCIL_BUFFER_BIT,
	All     = Color | Depth | Stencil
);

struct RenderBufferDesc {
	/*
	 * If this is set to true, we will generate an OpenGL texture instead of a render buffer
	 */
	bool ShaderReadable;
	/*
	 * The format internal format of the render buffer or texture
	 */
	RenderTargetType Format;
	/*
	 * Where the buffer will be attached to
	 */
	RenderTargetAttachment Attachment;
};

/*
 * Represents a buffer that can be rendered into. FrameBuffers can have multiple attachments, so we
 * can attach multiple images or RenderBuffers to it (for instance, depth, stencil, multiple color channels)
 *
 * Note: Sometimes this will be referred to as a RenderTarget (which is a bit more of a succinct description)
 */
class FrameBuffer : public florp::graphics::ITexture {
public:
	typedef std::shared_ptr<FrameBuffer> Sptr;

	/*
	 * Creates a new frame buffer with the given number of dimensions and optionally, a given number of samples (multi-sampling)
	 * @param width The width of the frame buffer, in texels (must be larger than 0)
	 * @param height The height of the frame buffer, in texels (must be larger than 0)
	 * @param numSamples The number of samples to use (must be greater than 0, and less than GL_MAX_SAMPLES). Default is 1
	 */
	FrameBuffer(uint32_t width, uint32_t height, uint8_t numSamples = 1);
	virtual ~FrameBuffer();

	// Gets the width of this frame buffer, in texels
	uint32_t GetWidth() const { return myWidth; }
	// Gets the height of this frame buffer, in texels
	uint32_t GetHeight() const { return myHeight; }
	// Gets the dimensions of this frame buffer, in texels
	glm::ivec2 GetSize() const { return { myWidth, myHeight }; }

	/*
	 * Gets the given attachment as a Texture, or nullptr if the attachment point cannot be retrieved as a texture
	 */
	florp::graphics::Texture2D::Sptr GetAttachment(RenderTargetAttachment attachment);

	/*
	 * Resizes this frame buffer to the new dimensions. Note that this will destroy any data currently stored within it,
	 * and invalidate any texture handles that have been retrieved from this frame buffer
	 * @param width The new width of the frame buffer (must be non-zero)
	 * @param height The new height of the frame buffer (must be non-zero)
	 */
	void Resize(uint32_t newWidth, uint32_t newHeight);

	/*
	 * Adds a new attachment to this frame buffer, with the given description. If a layer it already attached to the binding point
	 * given by the description, it will be destroyed
	 * @param desc The descriptor of the buffer that we want to add
	 */
	void AddAttachment(const RenderBufferDesc& desc);
	
	/*
	 * Validates this FrameBuffer, and returns whether it is in a valid state or not
	 * @returns True if the FrameBuffer is ready for drawing, false if otherwise
	 */
	bool Validate();

	virtual void Bind(uint32_t slot) override;
	virtual void Bind(uint32_t slot, RenderTargetAttachment attachment);
	/*
	 * Binds this frame buffer for usage as either a reading buffer, writing buffer, or both
	 * @param bindMode The slot to bind to (default is Draw/Write)
	 */
	void Bind(RenderTargetBinding bindMode = RenderTargetBinding::Draw) const;
	/*
	 * Unbinds this frame buffer from the slot that it is bound to. Note that you should always call UnBind before calling
	 * Bind on another frame buffer with the same parameters
	 */
	void UnBind() const;

	/*
		Blits (copies) the contents of the read framebuffer into the draw framebuffer
		@param srcBounds Region in the source framebuffer to copy from (left, top, right, bottom)
		@param dstBounds Region in the target framebuffer to copy to   (left, top, right, bottom)
		@param buffers   The buffers to copy
	*/
	Sptr Clone() const;

	static void Blit(
		const glm::ivec4& srcBounds, const glm::ivec4& dstBounds, 
		BufferFlags flags = BufferFlags::All, florp::graphics::MagFilter filterMode = florp::graphics::MagFilter::Linear);

	/*
	 * Overrides SetDebug name, so that we can send the name into OpenGL
	 * @param value The new debug name for this object
	 */
	virtual void SetDebugName(const std::string& value) override;
	
protected:
	// We will store a pointer to another FBO if this one is multisampled    
	Sptr myUnsampledFrameBuffer;
	// The dimensions of this frame buffer
	uint32_t myWidth, myHeight;
	// The number of samples to use if we have multisampling enabled
	uint8_t  myNumSamples;
	// Whether or not this frame buffer is in a valid state
	bool     isValid;
	// The current attachment points that this FrameBuffer is bound to
	mutable RenderTargetBinding myBinding;

	// Stores our attachment information for a given render buffer attachment point
	struct RenderBuffer {
		GLuint           RendererID;
		florp::graphics::IGraphicsResource::Sptr Resource;
		bool             IsRenderBuffer;
		RenderBufferDesc Description;

		RenderBuffer();
	};
	// Stores our buffers per attachment point
	std::unordered_map<RenderTargetAttachment, RenderBuffer> myLayers;
};
