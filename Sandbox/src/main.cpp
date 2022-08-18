#include "Core/Engine.hpp"
#include "Maths/Maths.hpp"

#include <iostream>

using namespace Hart;
using namespace Maths;

int main() {
	Engine::Init();

	while (Engine::Running()) {
		Engine::Update();
	}

	Vec2 a(3.0f, 2.0f);
	Vec3 b(3.0f, 2.0f, 5.0f);
	Vec3 c(0, 0);
	Vec3 d(a, 8);
	Vec4 e(b);

	std::cout << a << "\n";
	std::cout << b << "\n";
	std::cout << c << "\n";
	std::cout << d << "\n";
	std::cout << e << "\n";

	Engine::DeInit();
	std::cin.get();

	return 0;
}
