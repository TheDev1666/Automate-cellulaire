#pragma once

#include <iostream>
#include <limits>

void hideConsole();
void showConsole();

template<typename T>
void userInput(T& var, std::string msg)
{
	while (!(std::cin >> var))
	{
		std::cout << std::move(msg);
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
}