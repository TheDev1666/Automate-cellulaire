#include "Cell.hpp"
#include <cassert>

Cell::Cell(State state, std::vector<sf::Vertex*> quadVertices)
	: m_state(state), m_quadVertices(std::move(quadVertices))
{
	assert(m_quadVertices.size() == 4 && "Bad size !");
}

bool operator==(const Cell& lhs, const Cell& rhs)
{
	return lhs.m_state == rhs.m_state && lhs.m_quadVertices == rhs.m_quadVertices;
}

bool operator!=(const Cell& lhs, const Cell& rhs)
{
	return !(lhs == rhs);
}

void Cell::setColor(const sf::Color& color)
{
	for (sf::Vertex* vertex : m_quadVertices)
	{
		vertex->color = color;
	}
}

const sf::Color& Cell::getColor() const
{
	return m_quadVertices.front()->color;
}

void Cell::setState(State state)
{
	m_state = state;
}

State Cell::getState() const
{
	return m_state;
}