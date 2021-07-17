#pragma once

#include <SFML/Graphics.hpp>

enum class State
{
	ashes, //cendres
	youngForest, //jeune forêt
	oldForest, // vieille forêt
	sparkles, // debut de combustion
	ember, //fin de combustion
	fire // combustion
};

class Cell
{
public:
	explicit Cell(State state, std::vector<sf::Vertex*> quadVertices);
	Cell() = default;
	Cell(const Cell& cpy) = default;
	Cell& operator=(const Cell& cpy) = default;
	Cell(Cell&& move) = default;
	Cell& operator=(Cell&& move) = default;

	virtual ~Cell() = default;

	friend bool operator==(const Cell& lhs, const Cell& rhs);

	/*
	* Getters and setters
	*/
	void setColor(const sf::Color& color);
	const sf::Color& getColor() const;

	void setState(State state);
	State getState() const;

private:
	State m_state;
	std::vector<sf::Vertex*> m_quadVertices;
};

bool operator!=(const Cell& lhs, const Cell& rhs);