#include "HartPch.hpp"
#include "../../Core/HartApplication.hpp"

#include "QuadShader2D.hpp"
#include "LineShader2D.hpp"
#include "TextShader2D.hpp"
#include "CubeShader3D.hpp"

// initializes engine's shader library with some required shaders
namespace Hart {
	void initializeShaderLibrary() {
		Application::Get()->m_ShaderLibrary.loadShaderFromString("QuadShader2D", QuadShader2DVertexSource.c_str(), QuadShader2DFragmentSource.c_str());

		Application::Get()->m_ShaderLibrary.loadShaderFromString("LineShader2D", LineShader2DVertexSource.c_str(), LineShader2DFragmentSource.c_str());

		Application::Get()->m_ShaderLibrary.loadShaderFromString("TextShader2D", TextShader2DVertexSource.c_str(), TextShader2DFragmentSource.c_str());

		Application::Get()->m_ShaderLibrary.loadShaderFromString("CubeShader3D", CubeShader3DVertexSource.c_str(), CubeShader3DFragmentSource.c_str());
	}
}