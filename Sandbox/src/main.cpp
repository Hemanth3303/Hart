/*
* A game/app that uses the Hart Engine, currently used for testing purpores
*/

#include "Utils/FileManager.hpp"

using namespace Hart;
using namespace Utils;

int main() {
	
	std::string data = FileManager::ReadFromFile("res/test.txt");
	FileManager::WriteToFile("res/main.txt", data);
	std::cout << data;
	std::cin.get();

	return 0;
}