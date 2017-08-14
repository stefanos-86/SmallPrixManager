#include "ParametricCurve.h"

#include <cmath>


namespace spm {

	float Point::Distance(const Point& a, const Point& b) {
		const float deltaX = a.x - b.x;
		const float deltaY = a.y - b.y;
		const float sumSquare = deltaX * deltaX + deltaY * deltaY;
		return std::sqrt(sumSquare);
	}


	Point::Point(const float x, const float y, const float parameter) :
		x(x), y(y), parameter(parameter)
	{

	}

	bool operator==(const Point& lhs, const Point& rhs) {
		return lhs.x == rhs.x && 
			   lhs.y == rhs.y && 
			   lhs.parameter == rhs.parameter;
	}


	ParametricCurve::ParametricCurve(const std::vector<float> points) {
		float curveLentghSoFar = 0;

		// TODO: reject if less than 2 points, if odd number of coordinates.

		std::vector<float>::const_iterator point = std::begin(points);
		float last_x = *point;
		++point;
		const float last_y = *point;
		++point;
		Point last(last_x, last_y, 0);
		
		while (point != std::end(points)) {
			const float current_x = *point;
			++point;
			const float current_y = *point;
			++point;

			
			Point current(current_x, current_y, 0);

			curveLentghSoFar += Point::Distance(last, current);
			current.parameter = curveLentghSoFar;

			last = current;
		}

		// Now normalize the parameters.
		for (Point& p : this->points)
			p.parameter /= curveLentghSoFar;

	}

	Point ParametricCurve::at(const float parameter) const {
		// TODO: reject nonsensical parameter (out of [0, 1]).
		//algoritmo: vai di lower bound. Se esatto, è quello. Alrimenti interpola lui e il successivo.
		Point p{0, 0, 0};
		return p;
	}
}