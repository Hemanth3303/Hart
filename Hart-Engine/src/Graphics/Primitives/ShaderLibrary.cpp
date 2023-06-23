#include "HartPch.hpp"
#include "ShaderLibrary.hpp"

namespace Hart {
	namespace Graphics {
		ShaderLibrary::ShaderLibrary() {

		}

		ShaderLibrary::~ShaderLibrary() {

		}

		void ShaderLibrary::addShader(const std::shared_ptr<Shader>& shader) {
			if (exists(shader->getName())) {
				HART_ENGINE_ERROR("Shader with name "+ shader->getName() + " already exists");
				HART_ASSERT(false);
			}
			else {
				m_Shaders[shader->getName()] = shader;
			}
		}

		std::shared_ptr<Shader> ShaderLibrary::loadShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
			std::shared_ptr<Shader> shader = std::make_shared<Shader>(vertexShaderPath, fragmentShaderPath);
			addShader(shader);
			return shader;
		}

		std::shared_ptr<Shader> ShaderLibrary::loadShader(const std::string& name, const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
			std::shared_ptr<Shader> shader = std::make_shared<Shader>(name, vertexShaderPath, fragmentShaderPath);
			addShader(shader);
			return shader;
		}

		std::shared_ptr<Shader> ShaderLibrary::getShader(const std::string& name) {
			if (!exists(name)) {
				HART_ENGINE_ERROR("Shader named " + name + " doesn't exist");
				HART_ASSERT(false);
				return nullptr;
			}
			else {
				return m_Shaders[name];
			}
		}

		std::vector<std::string_view> ShaderLibrary::getAllShaderNames() {
			std::vector<std::string_view> shaderNames;
			for (const auto& [key, value] : m_Shaders) {
				shaderNames.push_back(key);
			}
			return shaderNames;
		}


		bool ShaderLibrary::exists(const std::string& name) {
			if (m_Shaders.find(name) == m_Shaders.end()) {
				return false;
			}
			else {
				return true;
			}
		}
	}
}