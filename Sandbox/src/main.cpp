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

	Vec3 a(3.0f, 2.0f, 0);
	Vec2 b(3.0f, 2.0f);
	Vec3 c = a + b;
	Vec3 d(b, 8);

	a.normalize();

	std::cout << a << "\n" << b << "\n" << c << "\n";
	std::cout << d << "\n";
	std::cout << (b+a+c-d) << "\n";

	Engine::DeInit();
	std::cin.get();

	return 0;
}
