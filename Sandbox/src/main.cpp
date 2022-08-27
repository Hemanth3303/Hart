/*
* A game/app that uses the Hart Engine, currently used for testing purpores
*/

#include "Core/Engine.hpp"
#include "Utils/Logger.hpp"
#include "Maths/Maths.hpp"

using namespace Hart;
using namespace Maths;
using namespace Utils;

int main() {

	Engine::Init();

	Mat4 mat(1.f);
	Vec2 vec2(2.f, 3.f);
	Vec3 vec3(2.f, 3.f, 4.f);
	Vec4 vec4(2.f, 3.f, 4.f, 5.f);

	Engine::Update();
	HART_CLIENT_INFO("Game stuff");
	HART_CLIENT_INFO(mat.toString());
	HART_CLIENT_INFO(vec2.toString());
	HART_CLIENT_INFO(vec3.toString());
	HART_CLIENT_INFO(vec4.toString());

	Engine::DeInit();

	std::cin.get();

	return 0;
}