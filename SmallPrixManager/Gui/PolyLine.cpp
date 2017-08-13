#include "PolyLine.h"

#include <SFML\Graphics\Vertex.hpp>
#include <SFML\Graphics\RenderTarget.hpp>

namespace spm {

	PolyLine::PolyLine()
	{
	}


	PolyLine::~PolyLine()
	{
	}


	void PolyLine::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		sf::VertexArray triangle(sf::Triangles, 3);

		// define the position of the triangle's points
		triangle[0].position = sf::Vector2f(10, 10);
		triangle[1].position = sf::Vector2f(100, 10);
		triangle[2].position = sf::Vector2f(100, 100);

		// define the color of the triangle's points
		triangle[0].color = sf::Color::Red;
		triangle[1].color = sf::Color::Blue;
		triangle[2].color = sf::Color::Green;
		
		target.draw(triangle, states);
	}
}