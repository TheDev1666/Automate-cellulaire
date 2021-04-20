#include "Grid.hpp"
#include <cassert>
#include <array>

Grid::Grid(sf::Vector2f position, sf::Vector2f gridSize, sf::Vector2u cellsNumber, State initState)
	: m_gridSize(std::move(gridSize)), m_cellsNumber(std::move(cellsNumber))
{
	assert(cellsNumber.x * cellsNumber.y > 0);
	m_vertices.setPrimitiveType(sf::Quads);
	m_vertices.resize(m_cellsNumber.x * m_cellsNumber.y * 4);

	std::array<sf::Color, 6> colors =
	{
		sf::Color( 10, 10, 10 ), //black
		sf::Color(106, 247, 9 ), //light green
		sf::Color(49, 120, 0), //dark green
		sf::Color(255, 255, 0), //yellow
		sf::Color(255, 143, 0), //orange
		sf::Color(255, 0, 0)// red
	};
	 
	sf::Vector2f cellSize( m_gridSize.x / m_cellsNumber.x, m_gridSize.y / m_cellsNumber.y);
	for (std::size_t x = 0; x < m_cellsNumber.x; ++x)
	{
		for (std::size_t y = 0; y < m_cellsNumber.y; ++y)
		{
			std::size_t firstQuadVerticeIndex = (y * m_cellsNumber.x + x) * 4;
			/*
			* Four vertices of each Cell
			*/
			m_vertices[firstQuadVerticeIndex].position = sf::Vector2f(x * cellSize.x, y * cellSize.y); //valid
			m_vertices[firstQuadVerticeIndex + 1].position = sf::Vector2f(x * cellSize.x + cellSize.x, y * cellSize.y);
			m_vertices[firstQuadVerticeIndex + 2].position = sf::Vector2f(x * cellSize.x + cellSize.x, y * cellSize.y + cellSize.y);
			m_vertices[firstQuadVerticeIndex + 3].position = sf::Vector2f(x * cellSize.x, y * cellSize.y + cellSize.y);

			std::vector<sf::Vertex*> quadVertices;

			for (std::size_t i = 0; i < 4; ++i)
			{
				quadVertices.emplace_back(&m_vertices[firstQuadVerticeIndex + i]);
			}

			//initialise and fill the board of Cells
			Cell cell(initState, std::move(quadVertices));
			cell.setColor(colors[static_cast<std::size_t>(initState)]);

			m_cells.emplace_back(std::move(cell));
		}
	}

	setPosition(std::move(position));
}

const sf::Vector2u& Grid::getCellsNumber() const
{
	return m_cellsNumber;
}

Cell& Grid::operator[](std::size_t index)
{
	assert(index < m_cells.size() && "index out of range");
	return m_cells[index];
}

const Cell& Grid::operator[](std::size_t index) const
{
	assert(index < m_cells.size() && "index out of range");
	return m_cells[index];
}

void Grid::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = nullptr;

	target.draw(m_vertices, states);
}

std::vector<State> getNeighbourState(const Grid& grid, const Cell& cell)
{
	//get the position of the cell in the grid
	auto cellIndex = std::distance(grid.m_cells.begin(), std::find(grid.m_cells.begin(), grid.m_cells.end(), cell));

	std::vector<State> neighbourState;
	for (std::size_t y = 0; y < 3; ++y)
	{
		for (std::size_t x = 0; x < 3; ++x)
		{
			if (y != 1 || x != 1)
			{
				auto index = cellIndex - (grid.m_cellsNumber.x + 1) + x + y * grid.m_cellsNumber.x;
				if (index >= 0 && index < grid.m_cells.size())
				{
					neighbourState.emplace_back(grid[index].getState());
				}
			}
		}
	}
	return neighbourState;
}