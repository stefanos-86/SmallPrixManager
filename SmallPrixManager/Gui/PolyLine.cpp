#include "PolyLine.h"

#include <SFML\Graphics\Vertex.hpp>
#include <SFML\Graphics\RenderTarget.hpp>

namespace spm {

	PolyLine::PolyLine(const std::vector<float>& points) :
		points(sf::LineStrip, points.size() / 2)
	{
		std::vector<float>::const_iterator i = std::begin(points);
		size_t sfPointsCounter = 0;
		while (i != std::end(points)){
			const float x = *i;
			++i;
			const float y = *i;
			++i;

			this->points[sfPointsCounter].position = sf::Vector2f(x, y);
			this->points[sfPointsCounter].color = sf::Color::White;
			++sfPointsCounter;
		}
	}


	PolyLine::~PolyLine()
	{
	}


	void PolyLine::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(points, states);
	}
}