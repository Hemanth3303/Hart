/*
* A game/app that uses the Hart Engine, currently used for testing purpores
*/


#include "Core/Engine.hpp"
#include "Maths/Maths.hpp"

#include <iostream>

using namespace Hart;
using namespace Maths;

int main() {
	
	Mat4 matA(3);
	Mat4 identity(1);

	std::cout << "Matrix A: \n";
	std::cout << matA << "\n\n";

	matA *= identity;
	std::cout << "Matrix A multiplied by Identity Matrix, should be equalt to A itself: \n";
	std::cout << matA << "\n\n";

	Mat4 matB;
	matB.columns[0].x = 1;
	matB.columns[0].y = 2;
	matB.columns[0].z = 3;
	matB.columns[0].w = 4;
	std::cout << "Matrix B: \n";
	std::cout << matB << "\n\n";
	std::cout << "Transpose of Matrix B: \n";
	std::cout << transpose(matB) << "\n\n";

	Mat4 matC = matA * matB;
	std::cout << "Matrix C = Matrix A multiplied by Matrix B: \n";
	std::cout << matC << "\n\n";

	std::cout << "Exp: " << exponential(1) << "\n";
	std::cout << "logBaseE: " << logBaseE(10) << "\n";
	std::cout << "logBaseTen: " << logBaseTen(10) << "\n";
	std::cout << "LogBase2: " << logBaseTwo(10) << "\n\n";

	std::cout << "Lerp: " << lerp(2, 8, 0.5) << "\n";
	std::cout << "Lerp: " << lerp(2, 8, 1.5) << "\n";
	std::cout << "Clamp: " << clamp(5, 10, 20) << "\n";
	std::cout << "Clamp: " << clamp(15, 10, 20) << "\n";
	std::cout << "Clamp: " << clamp(35, 10, 20) << "\n";

	std::cin.get();

	return 0;
}
