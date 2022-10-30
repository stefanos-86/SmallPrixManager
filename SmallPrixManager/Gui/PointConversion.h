#ifndef SPM_PPINT_CONVERSION
#define SPM_PPINT_CONVERSION

#include <vector>

#include <SDL.h>

#include "../Simulation/Math.h"

/** Convert "our" points into SDLoints. */
namespace spm {
   SDL_Point toGraphic(const Point& p);
}

#endif