#pragma once

#include "HartPch.hpp"
#include "Shader.hpp"

namespace Hart {
	// Class for managing shaders
	class ShaderLibrary {
	public:
		ShaderLibrary();
		~ShaderLibrary();

		// add existing shader to shader library
		void addShader(const std::shared_ptr<Shader>& shader);
		// create new shader and adds it to library, name is choosen as name of vertex shader
		std::shared_ptr<Shader> loadShaderFromDisk(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
		// create new shader and adds it to library
		std::shared_ptr<Shader> loadShaderFromDisk(const std::string& name, const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
		// creates a shader using the provided c-string and adds to library
		std::shared_ptr<Shader> loadShaderFromString(const std::string& name, const char* vertexShaderSource, const char* fragmentShaderSource);
		std::shared_ptr<Shader> getShader(const std::string& name);
		// returns names of all currently stored shaders in the shaderlibrary
		std::vector<std::string_view> getAllShaderNames();
	private:
		bool exists(const std::string& name);
	private:
		std::unordered_map<std::string, std::shared_ptr<Shader>> m_Shaders;
	};
}