#include "PolyLine.h"

#include <SDL.h>

namespace spm {

	PolyLine::PolyLine(const std::vector<float>& points)
	{
		this->points.reserve(points.size());

		std::vector<float>::const_iterator i = std::begin(points);
		size_t sfPointsCounter = 0;
		while (i != std::end(points)){
			const float x = *i;
			++i;
			const float y = *i;
			++i;

			SDL_Point p;
			p.x = x;
			p.y = y;

			this->points.emplace_back(p);
			++sfPointsCounter;
		}
	}


	PolyLine::~PolyLine()
	{
	}

	
	void PolyLine::draw(SDL_Renderer* renderer) const {
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderDrawLines(renderer, points.data(), points.size());
	}
	
}