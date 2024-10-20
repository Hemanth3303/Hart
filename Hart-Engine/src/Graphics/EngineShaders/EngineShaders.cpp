#include "HartPch.hpp"
#include "../../Core/Application.hpp"

#include "QuadShader2D.hpp"
#include "CubeShader3D.hpp"

// initializes engine's shader library with some required shaders
namespace Hart {
	void initializeShaderLibrary() {
		Application::Get()->m_ShaderLibrary.loadShaderFromString("QuadShader2D", QuadShader2DVertexSource.c_str(), QuadShader2DFragmentSource.c_str());

		Application::Get()->m_ShaderLibrary.loadShaderFromString("CubeShader3D", CubeShader3DVertexSource.c_str(), CubeShader3DFragmentSource.c_str());
	}
}