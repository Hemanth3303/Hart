#pragma once

#include "Core/EntryPoint.hpp"

#include "Core/HartApplication.hpp"
#include "Core/Assert.hpp"
#include "Core/Window.hpp"

#include "Graphics/Primitives/Shader.hpp"
#include "Graphics/Primitives/VertexBuffer.hpp"
#include "Graphics/Primitives/IndexBuffer.hpp"
#include "Graphics/Primitives/VertexArray.hpp"
#include "Graphics/Primitives/Image.hpp"
#include "Graphics/Primitives/Texture2D.hpp"
#include "Graphics/Primitives/ShaderLibrary.hpp"
#include "Graphics/Renderer/RenderCommand.hpp"
#include "Graphics/Renderer/Renderer3D.hpp"
#include "Graphics/Camera/OrthographicCamera.hpp"
#include "Graphics/Camera/OrthographicCameraController.hpp"

#include "Maths/MathConstants.hpp"
#include "Maths/MathFunctions.hpp"
#include "Maths/Vec2.hpp"
#include "Maths/Vec3.hpp"
#include "Maths/Vec4.hpp"
#include "Maths/Mat4.hpp"

#include "Events/EventCategory.hpp"
#include "Events/Event.hpp"
#include "Events/WindowEvents.hpp"
#include "Events/WindowEvents.hpp"
#include "Events/MouseEvents.hpp"

#include "Inputs/KeyCodes.hpp"
#include "Inputs/MouseCodes.hpp"
#include "Inputs/InputManager.hpp"

#include "Utils/FileManager.hpp"
#include "Utils/Logger.hpp"
#include "Utils/Random.hpp"
#include "Utils/Timer.hpp"