#ifndef SPM_BEZIER_ADAPTER
#define SPM_BEZIER_ADAPTER

#include <vector>

#include <SDL.h>

#include "../Simulation/Bezier.h"

namespace spm {

	/** Very simple wrapper to draw one of the Bezier curves used in the simulation.
        Uses the simplest possible algorithm: just compute this many regularly spaced points.
        */
	class BezierAdapter
	{
	public:
        BezierAdapter(const Bezier& curve);
        BezierAdapter(const BezierPath& curve);

        void draw(SDL_Renderer* renderer) const;

	private:
        /** Assumes constant curves, caches the points. */
        std::vector<SDL_Point> points;

  
        template <typename Curve>
        void storeRasterizedPoints(const Curve& c) {
            std::vector<Point> rasterizedPoints;
            c.raster(rasterizedPoints);
        
            for (size_t i = 0; i < rasterizedPoints.size(); ++i) {
               points.emplace_back(toGraphic(rasterizedPoints[i]));
            }
        }
            
    };

}
#endif