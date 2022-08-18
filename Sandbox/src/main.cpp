/*
* A game/app that uses the Hart Engine, currently used for testing purpores
*/


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

	Vec3 a(3, -3, 1);
	Vec3 b(4, 9, 2);
	Vec3 c = crossProduct(a, b);
	std::cout << "a: " << a << "\n";
	std::cout << "b: " << b << "\n";
	std::cout << "cross product: "<< c << "\n";

	std::cout << "MY PI: " << Hart::Maths::PI << "\n";
	std::cout << "E: " << std::exp(1) << "\n";
	std::cout << "pi radians=" << radiansToDegree(PI) << "\n";
	std::cout << "0 degrees=" << degreeToRadian(0) << "\n";

	std::cout << aTan2D(2, -3) << "\n";

	Engine::DeInit();
	std::cin.get();

	return 0;
}
