#ifndef SPM_BEZIER_ADAPTER
#define SPM_BEZIER_ADAPTER

#include <vector>

#include <SFML/Graphics/VertexArray.hpp>

#include "../Simulation/Bezier.h"

namespace spm {

	/** Very simple wrapper to draw one of the Bezier curves used in the simulation. */
	class BezierAdapter : public sf::Drawable
	{
	public:
        /** Using the simplest possible algorithm: just compute this many regularly spaced points. */
        static const size_t POINT_COUNT;

        BezierAdapter(const Bezier& curve);
        BezierAdapter(const BezierPath& curve);

	private:
		sf::VertexArray points;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	};




}
#endif