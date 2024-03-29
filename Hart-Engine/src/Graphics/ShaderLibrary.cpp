#include "HartPch.hpp"
#include "ShaderLibrary.hpp"

namespace Hart {
	ShaderLibrary::ShaderLibrary() {

	}

	ShaderLibrary::~ShaderLibrary() {

	}

	void ShaderLibrary::addShader(const std::shared_ptr<Shader>& shader) {
		HART_ASSERT_NOT_EQUAL(exists(shader->getName()), true, "Reason: Shader with name " + shader->getName() + " already exists");

		m_Shaders[shader->getName()] = shader;
	}

	std::shared_ptr<Shader> ShaderLibrary::loadShaderFromDisk(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
		std::shared_ptr<Shader> shader = std::make_shared<Shader>(vertexShaderPath, fragmentShaderPath);
		addShader(shader);
		return shader;
	}

	std::shared_ptr<Shader> ShaderLibrary::loadShaderFromDisk(const std::string& name, const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
		std::shared_ptr<Shader> shader = std::make_shared<Shader>(name, vertexShaderPath, fragmentShaderPath);
		addShader(shader);
		return shader;
	}

	std::shared_ptr<Shader> ShaderLibrary::loadShaderFromString(const std::string& name, const char* vertexShaderSource, const char* fragmentShaderSource) {
		std::shared_ptr<Shader> shader = std::make_shared<Shader>(name, vertexShaderSource, fragmentShaderSource);
		addShader(shader);
		return shader;
	}

	std::shared_ptr<Shader> ShaderLibrary::getShader(const std::string& name) {
		HART_ASSERT_EQUAL(exists(name), true, "Reason: Shader named " + name + " doesn't exist");
		return m_Shaders[name];
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