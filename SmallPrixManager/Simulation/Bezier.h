#ifndef SPM_BEZIER
#define SPM_BEZIER

#include <vector>

/** There is no plan to ever port this code to other GUIs, so I recycle the "math" library. */
#include <SFML\Graphics\Vertex.hpp>

namespace spm {

	/** Poor man's implementation of a cubic Bezier curve.
	    Largely stolen from http://devmag.org.za/2011/04/05/bzier-curves-a-tutorial/ */
	class Bezier {
	public:
		/** Makes a curve from the 4 control points. 
		    The curve starts at p0 and ends at p3. Endpoint tangents go from p0 to p1 and from p2 to p3. */
		Bezier(const sf::Vector2f p0, 
			   const sf::Vector2f p1, 
			   const sf::Vector2f p2, 
			   const sf::Vector2f p3 );


		/** Returns the point for a given vaule of the parameter. */
		sf::Vector2f at(const float parameter) const;

        /** Returns the point for a given value of the parameter as expressed in distance units, not between 0 and 1. */
        sf::Vector2f atLength(const float parameter) const;

        /** Returns an approximate length of the curve. */
        float length() const;

        /** Rasterization of the curve, creates a polyline which has the given amount of points. 
            Points are equally spaced (the most simple algorithm). */
        void raster(std::vector<sf::Vector2f>& points, const size_t desiredPointCount) const;  // TODO: direct tests

	private:
        const sf::Vector2f p0;
		const sf::Vector2f p1;
		const sf::Vector2f p2;
		const sf::Vector2f p3;
	};


    /** Set of Bezier curves attached one after the other. */
    class BezierPath {
    public:
        BezierPath(const std::vector<sf::Vector2f>& points);

        /** Returns the point for a given vaule of the parameter.
            The parameter goes from 1 to size(), then it hits the right curve inside the path. */
        sf::Vector2f at(const float parameter) const;

        /** Returns the point for a given value of the parameter as expressed in distance units, not between 0 and size(). */
        sf::Vector2f atLength(const float parameter) const;

        /** Approximate total length of the path. */
        float length() const;

        /** Returns the maximum value that you can give to the parameter. Which also is the number of curves in the path.
            This path is made of many curves. The point at, say, 1.5, is the point at 0.5 in the second curve.*/
        size_t size() const;


    private:
        std::vector <Bezier> elements;
    };
}

#endif