#pragma once
#include "Shade/Core/CoreAPI.h"
#include "Vendors/glad/glad.h"

namespace se
{
	enum class FrameBufferTextureFormat
	{
		None = 0,
		// Color
		RGBA8,
		// Depth/stencil
		DEPTH24STENCIL8,
		// Defaults
		Depth = DEPTH24STENCIL8
	};
	struct FrameBufferTextureSpec
	{
		FrameBufferTextureSpec() = default;
		FrameBufferTextureSpec(se::FrameBufferTextureFormat format)
			: TextureFormat(format) {}

		se::FrameBufferTextureFormat TextureFormat = se::FrameBufferTextureFormat::None;
		// TODO: filtering/wrap
	};
	struct FramebufferAttachmentSpec
	{
		FramebufferAttachmentSpec() = default;
		FramebufferAttachmentSpec(std::initializer_list<se::FrameBufferTextureSpec> attachments)
			: Attachments(attachments) {}

		std::vector<se::FrameBufferTextureSpec> Attachments;
	};

	struct FramebufferSpec
	{
		FramebufferSpec(const uint32_t& width, const uint32_t& height, const se::FramebufferAttachmentSpec& attachments, const bool& swapChainTarget = false)
			: Width(width), Height(height), Attachments(attachments), SwapChainTarget(swapChainTarget) {}
		uint32_t Width = 0, Height = 0;
		se::FramebufferAttachmentSpec Attachments;
		uint32_t Samples = 1;
		bool SwapChainTarget = false;
	};

	class SE_API FrameBuffer
	{
	public:
		virtual ~FrameBuffer();
		static se::FrameBuffer* Create(const se::FramebufferSpec& spec);

		void Clear();

		void Bind();
		void UnBind();
		void Invalidate();

		virtual void Resize(const unsigned int& width, const unsigned int& height);
		GLuint GetTextureAttachment(const GLuint& index = 0) const;
		const se::FramebufferSpec& GetSpecification() const;

	private:
		FrameBuffer(const se::FramebufferSpec& spec);
		GLuint m_RendererID = 0;
		FramebufferSpec m_Specification;

		std::vector<se::FrameBufferTextureSpec> m_ColorAttachmentSpecifications;
		se::FrameBufferTextureSpec m_DepthAttachmentSpecification = se::FrameBufferTextureFormat::None;

		std::vector<GLuint> m_ColorAttachments;
		GLuint m_DepthAttachment = 0;
	};
}

