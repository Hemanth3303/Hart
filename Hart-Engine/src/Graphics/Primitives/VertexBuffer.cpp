#include "HartPch.hpp"
#include "VertexBuffer.hpp"

namespace Hart {
	namespace Graphics {
		BufferElement::BufferElement(ShaderDataType ptype, const std::string& pname, bool pnormalized)
			: type(ptype), name(pname), size(Shader::GetShaderDataTypeSize(ptype)), offset(0), normalized(pnormalized) {

		}

		std::uint32_t BufferElement::getComponentCount() const {
			switch (type) {
				case Hart::Graphics::ShaderDataType::None:
					HART_ENGINE_ERROR("ShaderDataType can't be null");
					return 0;
				case Hart::Graphics::ShaderDataType::Float:
					return 1;
				case Hart::Graphics::ShaderDataType::Float2:
					return 2;
				case Hart::Graphics::ShaderDataType::Float3:
					return 3;
				case Hart::Graphics::ShaderDataType::Float4:
					return 4;
				case Hart::Graphics::ShaderDataType::Mat4:
					return 4 * 4;
				case Hart::Graphics::ShaderDataType::Int:
					return 1;
				case Hart::Graphics::ShaderDataType::Int2:
					return 2;
				case Hart::Graphics::ShaderDataType::Int3:
					return 3;
				case Hart::Graphics::ShaderDataType::Int4:
					return 4;
				case Hart::Graphics::ShaderDataType::Bool:
					return 1;
				default:
					HART_ENGINE_ERROR("Unknown ShaderDataType");
					return 0;
			}
		}

		GLenum BufferElement::getOpenGLType() const {
			return Shader::ShaderDataTypeToOpenGLType(type);
		}

		BufferLayout::BufferLayout() {

		}

		BufferLayout::BufferLayout(const std::initializer_list<BufferElement>& elements) 
			: m_Elements(elements) {

			calculateOffsetAndStride();
		}

		void BufferLayout::calculateOffsetAndStride() {
			uint64_t offset = 0;
			m_Stride = 0;
			for (auto& element : m_Elements) {
				element.offset = offset;
				offset += element.size;
				m_Stride += element.size;
			}
		}

		VertexBuffer::VertexBuffer(std::uint32_t size) {
			glCreateBuffers(1, &m_ID);
			glBindBuffer(GL_ARRAY_BUFFER, m_ID);
			glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		VertexBuffer::VertexBuffer(float* vertices, std::uint32_t size) {
			glCreateBuffers(1, &m_ID);
			glBindBuffer(GL_ARRAY_BUFFER, m_ID);
			glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		VertexBuffer::~VertexBuffer() {
			glDeleteBuffers(1, &m_ID);
		}

		void VertexBuffer::bind() const {
			glBindBuffer(GL_ARRAY_BUFFER, m_ID);
		}

		void VertexBuffer::unbind() const {
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		void VertexBuffer::setData(const void* data, std::uint32_t size, std::uint32_t offset) {
			glBindBuffer(GL_ARRAY_BUFFER, m_ID);
			glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
	}
}