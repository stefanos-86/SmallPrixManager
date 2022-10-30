#ifndef SPM_BEZIER_ADAPTER
#define SPM_BEZIER_ADAPTER

#include <vector>

//#include <SFML/Graphics/VertexArray.hpp>

#include "../Simulation/Bezier.h"

namespace spm {

	/** Very simple wrapper to draw one of the Bezier curves used in the simulation.
        Uses the simplest possible algorithm: just compute this many regularly spaced points.
        */
	class BezierAdapter //: public sf::Drawable
	{
	public:
        BezierAdapter(const Bezier& curve);
        BezierAdapter(const BezierPath& curve);

	private:
        /** Assumes constant curves, caches the points. */
       // sf::VertexArray points;

       // virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        template <typename Curve>
        void storeRasterizedPoints(const Curve& c) {
            /*
            std::vector<Point> rasterizedPoints;
            c.raster(rasterizedPoints);
        
        
            for (size_t i = 0; i < rasterizedPoints.size(); ++i) {
                this->points[i].position = toGraphic(rasterizedPoints[i]);
                this->points[i].color = sf::Color::White;
        }
            */
       }; 
	};




}
#endif