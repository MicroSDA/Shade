#pragma once
#include "Shade/Core/CoreAPI.h"
#include "Shade/Core/Engine/Vertex.h"
#include "Vendors/glad/glad.h"

namespace se
{
	enum class VertexBufferElementType
	{
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};
	struct VertexBufferElement
	{
		std::string				Name       = "Undefined";
		VertexBufferElementType Type	   = VertexBufferElementType::None;
		size_t                  Size       = 0;
		size_t                  Offset     = 0;
		bool                    Normalized = false;
		uint32_t                Id         = 0;

		VertexBufferElement(const VertexBufferElementType& type, const std::string& name) :
			Type(type), Name(name), Size(ElementSize()){};

		GLuint GeElementTypeCount() const
		{
			switch (Type)
			{
			case VertexBufferElementType::None:    return 0;
			case VertexBufferElementType::Float:   return 1;
			case VertexBufferElementType::Float2:  return 2;
			case VertexBufferElementType::Float3:  return 3;
			case VertexBufferElementType::Float4:  return 4;
			case VertexBufferElementType::Mat3:    return 3;
			case VertexBufferElementType::Mat4:    return 4;
			case VertexBufferElementType::Int:     return 1;
			case VertexBufferElementType::Int2:    return 2;
			case VertexBufferElementType::Int3:    return 3;
			case VertexBufferElementType::Int4:    return 4;
			case VertexBufferElementType::Bool:    return 1;

			default: return 0;
			}
		};
		GLuint ToOpenGLNativeType() const
		{
			switch (Type)
			{
			case se::VertexBufferElementType::None:   return GL_NONE;
			case se::VertexBufferElementType::Float:  return GL_FLOAT;
			case se::VertexBufferElementType::Float2: return GL_FLOAT;
			case se::VertexBufferElementType::Float3: return GL_FLOAT;
			case se::VertexBufferElementType::Float4: return GL_FLOAT;
			case se::VertexBufferElementType::Mat3:   return GL_FLOAT;
			case se::VertexBufferElementType::Mat4:   return GL_FLOAT;
			case se::VertexBufferElementType::Int:    return GL_INT;
			case se::VertexBufferElementType::Int2:   return GL_INT;
			case se::VertexBufferElementType::Int3:	  return GL_INT;
			case se::VertexBufferElementType::Int4:	  return GL_INT;
			case se::VertexBufferElementType::Bool:	  return GL_BOOL;

			default: return 0;
			}
		}

	private:
		size_t ElementSize() const
		{
			switch (Type)
			{
			case se::VertexBufferElementType::None:   return 0;
			case se::VertexBufferElementType::Float:  return 4;
			case se::VertexBufferElementType::Float2: return 8;
			case se::VertexBufferElementType::Float3: return 12;
			case se::VertexBufferElementType::Float4: return 16;
			case se::VertexBufferElementType::Mat3:   return 32;
			case se::VertexBufferElementType::Mat4:   return 64;
			case se::VertexBufferElementType::Int:    return 4;
			case se::VertexBufferElementType::Int2:   return 8;
			case se::VertexBufferElementType::Int3:	  return 12;
			case se::VertexBufferElementType::Int4:   return 16;
			case se::VertexBufferElementType::Bool:	  return 1;

			default: return 0;
			}
		}
	};
	class SE_API VertexBufferLayout
	{
	public:
		VertexBufferLayout() : m_Stride(0) {};
		VertexBufferLayout(std::initializer_list<VertexBufferElement> elements) :
			m_Elements(elements), m_Stride(0)
		{
			size_t   offset = 0;
			uint32_t id = 0;
			for (auto& element : m_Elements)
			{
				element.Offset = offset;
				offset        += element.Size;
				m_Stride      += element.Size;
				element.Id     = id;
				id++;
			}
		};
		~VertexBufferLayout() = default;
		size_t GetStride() const { return m_Stride; }

		std::vector<VertexBufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<VertexBufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<VertexBufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<VertexBufferElement>::const_iterator end() const { return m_Elements.end(); }
	private:
		std::vector<VertexBufferElement> m_Elements;
		size_t							 m_Stride;
	};
	class SE_API VertexBuffer
	{
	public:
		VertexBuffer();
		VertexBuffer(const se::VertexBuffer& other) = delete;
		VertexBuffer& operator=(VertexBuffer& other) = delete;
		VertexBuffer(se::VertexBuffer&& other) noexcept
			:m_VAO(NULL),m_VBO(NULL), m_EBO(NULL)
		{
			if (this != &other)
			{
				this->m_VAO = other.m_VAO;
				this->m_VBO = other.m_VBO;
				this->m_EBO = other.m_EBO;

				other.m_VAO = NULL;
				other.m_VBO = NULL;
				other.m_EBO = NULL;
			}
		}
		VertexBuffer& operator=(VertexBuffer&& other) noexcept
		{
			if (this != &other)
			{
				this->m_VAO = other.m_VAO;
				this->m_VBO = other.m_VBO;
				this->m_EBO = other.m_EBO;

				other.m_VAO = NULL;
				other.m_VBO = NULL;
				other.m_EBO = NULL;
			}
			return *this;
		}
		template<typename V, typename I>
		static VertexBuffer Create(const se::VertexBufferLayout& layout, const V* vertices, const size_t& verticesCount, const I* indices, const size_t& indicesCount)
		{
			se::VertexBuffer _Buffer;
			_Buffer.m_Layout = layout;
			glGenVertexArrays(1, &_Buffer.m_VAO);
			glGenBuffers(1, &_Buffer.m_VBO);
			glBindVertexArray(_Buffer.m_VAO);
			glBindBuffer(GL_ARRAY_BUFFER, _Buffer.m_VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(V) * verticesCount, vertices, GL_STATIC_DRAW);

			GLuint index = 0;
			for (auto& element : layout)
			{
				auto v = sizeof(se::Vertex);
				glEnableVertexAttribArray(index);
				glVertexAttribPointer(index, element.GeElementTypeCount(), element.ToOpenGLNativeType(), element.Normalized, layout.GetStride(), (const void*)(element.Offset));
				index++;
			}

			glGenBuffers(1, &_Buffer.m_EBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _Buffer.m_EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(I) * indicesCount, indices, GL_STATIC_DRAW);

			glBindVertexArray(0); // just for save

			return std::move(_Buffer);
		}
		template<typename V>
		static VertexBuffer Create(const se::VertexBufferLayout& layout, const V* vertices, const size_t& verticesCount)
		{
			se::VertexBuffer _Buffer;
			_Buffer.m_Layout = layout;
			glGenVertexArrays(1, &_Buffer.m_VAO);
			glGenBuffers(1, &_Buffer.m_VBO);
			glBindVertexArray(_Buffer.m_VAO);
			glBindBuffer(GL_ARRAY_BUFFER, _Buffer.m_VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(V) * verticesCount, vertices, GL_STATIC_DRAW);

			GLuint index = 0;
			for (auto& element : layout)
			{
				auto v = sizeof(se::Vertex);
				glEnableVertexAttribArray(index);
				glVertexAttribPointer(index, element.GeElementTypeCount(), element.ToOpenGLNativeType(), element.Normalized, layout.GetStride(), (const void*)(element.Offset));
				index++;
			}
			glBindVertexArray(0); // just for save

			return std::move(_Buffer);
		}

		inline const GLuint& GetVAO() const { return m_VAO; }
		inline const GLuint& GetVBO() const { return m_VBO; }
		inline const GLuint& GetEBO() const { return m_EBO; }
		inline const se::VertexBufferLayout& GetLayout() const { return m_Layout; }
		virtual ~VertexBuffer();
	private:
		se::VertexBufferLayout m_Layout;
		GLuint m_VAO, m_VBO, m_EBO;
		
	};
}