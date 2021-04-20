#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>
#include <cassert>

#include "Grid.hpp"

void transition(Grid& grid)
{
	std::random_device rnd;
	std::mt19937 randomEngine(rnd());

	auto isEventHappened = [&randomEngine](double probability) -> bool 
	{
		assert(probability >= 0.0 && probability <= 1.0 && "probability out of range !");
		std::bernoulli_distribution d(probability);
		return d(randomEngine);
	};

	for (std::size_t i = 0; i < (grid.getCellsNumber().x * grid.getCellsNumber().y); ++i)
	{
		auto neighbourState = getNeighbourState(grid, grid[i]);
		switch (grid[i].getState())
		{
		case State::youngForest:
			if (isEventHappened(0.01))
			{
				if (std::any_of(neighbourState.begin(), neighbourState.end(), [](State elem)-> bool {return elem == State::sparkles; }))
				{
					grid[i].setState(State::sparkles);
					grid[i].setColor(sf::Color(255, 255, 0));
				}
			}
			else if (std::any_of(neighbourState.begin(), neighbourState.end(), [](State elem)-> bool {return elem == State::fire; }) && isEventHappened(0.02))
			{
				grid[i].setState(State::sparkles);
				grid[i].setColor(sf::Color(255, 255, 0));
			}
			else if (std::any_of(neighbourState.begin(), neighbourState.end(), [](State elem)-> bool {return elem == State::ember; }) && isEventHappened(0.01))
			{
				grid[i].setState(State::sparkles);
				grid[i].setColor(sf::Color(255, 255, 0));
			}
			else if (isEventHappened(0.005))
			{
				grid[i].setState(State::oldForest);
				grid[i].setColor(sf::Color(49, 120, 0));
			}
			break;

		case State::oldForest:
			if (std::any_of(neighbourState.begin(), neighbourState.end(), [](State elem)-> bool {return elem == State::sparkles; }) && isEventHappened(0.1))
			{
				grid[i].setState(State::sparkles);
				grid[i].setColor(sf::Color(255, 255, 0));
			}
			else if (std::any_of(neighbourState.begin(), neighbourState.end(), [](State elem)-> bool {return elem == State::fire; }) && isEventHappened(0.2))
			{
				grid[i].setState(State::sparkles);
				grid[i].setColor(sf::Color(255, 255, 0));
			}
			else if (isEventHappened(0.1))
			{
				if (std::any_of(neighbourState.begin(), neighbourState.end(), [](State elem)-> bool {return elem == State::ember; }))
				{
					grid[i].setState(State::sparkles);
					grid[i].setColor(sf::Color(255, 255, 0));
				}
			}
			else if (std::count(neighbourState.begin(), neighbourState.end(), State::oldForest) >= 5 && isEventHappened(0.00005))
			{
				grid[i].setState(State::sparkles);
				grid[i].setColor(sf::Color(255, 255, 0));
			}
			break;

		case State::sparkles:
			if (isEventHappened(0.1))
			{
				grid[i].setState(State::fire);
				grid[i].setColor(sf::Color(255, 0, 0));
			}
			break;

		case State::fire:
			if (isEventHappened(0.1))
			{
				grid[i].setState(State::ember);
				grid[i].setColor(sf::Color(255, 143, 0));
			}
			break;

		case State::ember:
			if (isEventHappened(0.1))
			{
				grid[i].setState(State::ashes);
				grid[i].setColor(sf::Color(10, 10, 10));
			}
			break;

		case State::ashes:
			if (isEventHappened(0.001))
			{
				grid[i].setState(State::youngForest);
				grid[i].setColor(sf::Color(106, 247, 9));
			}
			break;
		}
	}
}

int main()
{
	//niveau 2
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	
	constexpr std::size_t WINDOW_WIDTH = 800;
	constexpr std::size_t WINDOW_HEIGHT = 800;

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Automate Cellulaire de niveau 2", sf::Style::Titlebar | sf::Style::Close, settings);

	window.setFramerateLimit(10);
	Grid grid(sf::Vector2f(50, 50), sf::Vector2f(700, 700), sf::Vector2u(50, 50));

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		window.clear();
		window.draw(grid);

		transition(grid);

		window.display();
	}
	return 0;
}