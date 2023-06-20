/*
* class for managing shaders
*/

#pragma once

#include "HartPch.hpp"
#include "Shader.hpp"

namespace Hart {
	namespace Graphics {
		class ShaderLibrary {
		public:
			ShaderLibrary();
			~ShaderLibrary();

			// add existing shader to shader library
			void addShader(const std::shared_ptr<Shader>& shader);
			// create new shader and adds it to library, name is choosen as name of vertex shader
			std::shared_ptr<Shader> loadShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
			// create new shader and adds it to library
			std::shared_ptr<Shader> loadShader(const std::string& name, const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
			std::shared_ptr<Shader> getShader(const std::string& name);
		private:
			bool exists(const std::string& name);
		private:
			std::unordered_map<std::string, std::shared_ptr<Shader>> m_Shaders;
		};
	}
}