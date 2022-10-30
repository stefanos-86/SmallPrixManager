#include "PointConversion.h"

namespace spm {
    SDL_Point toGraphic(const Point& p) {
        SDL_Point graphicPoint;
        graphicPoint.x = p.x;
        graphicPoint.y = p.y;
        return graphicPoint;
    }
	
}

