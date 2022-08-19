/*
* A game/app that uses the Hart Engine, currently used for testing purpores
*/


#include "Core/Engine.hpp"
#include "Maths/Maths.hpp"

#include <iostream>

using namespace Hart;
using namespace Maths;

int main() {
	Mat4 mat;

	mat.columns[0].x = 1;
	mat.columns[0].y = 2;
	mat.columns[0].z = 3;
	mat.columns[0].w = 4;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			std::cout << mat.elements[i * 4 + j] << ", ";
		}
		std::cout << "\n";
	}

	std::cout << mat << "\n";
	Mat4 mat2 = transpose(mat);
	std::cout << mat << "\n";
	std::cout << mat.transpose() << "\n";
	std::cout << mat2 << "\n";

	std::cin.get();

	return 0;
}
