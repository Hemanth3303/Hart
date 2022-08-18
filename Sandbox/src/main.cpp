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
	Vec2 b(3.0f, 2.0f);
	Vec2 c = a + b;

	a.normalize();

	std::cout << a << "\n" << b << "\n" << c << "\n";
	std::cout << a << "\n";
	std::cout << normalize(b) << "\n";

	Engine::DeInit();
	std::cin.get();

	return 0;
}
