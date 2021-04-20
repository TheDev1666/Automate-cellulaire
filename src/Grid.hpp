#pragma once

#include <SFML/Graphics.hpp>
#include "Cell.hpp"

class Grid : public sf::Drawable, public sf::Transformable
{
public:
	Grid(sf::Vector2f position, sf::Vector2f gridSize, sf::Vector2u cellsNumber, State initState = State::youngForest);
	Grid(const Grid& cpy) = default;
	Grid& operator=(const Grid& cpy) = default;

	Grid(Grid&& move) = default;
	Grid& operator=(Grid&& move) = default;

	virtual ~Grid() noexcept = default;

	const sf::Vector2u& getCellsNumber() const;

	Cell& operator[](std::size_t index);
	const Cell& operator[](std::size_t index) const;

	friend std::vector<State> getNeighbourState(const Grid& grid, const Cell& cell);

private:
	//functions
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	//variables
	sf::Vector2f m_gridSize;
	sf::Vector2u m_cellsNumber;
	sf::VertexArray m_vertices;

	std::vector<Cell> m_cells;
};