#ifndef SPM_BEZIER
#define SPM_BEZIER

#include <vector>

#include "Math.h"

namespace spm {

	/** Poor man's implementation of a cubic Bezier curve.

	    Credits to http://devmag.org.za/2011/04/05/bzier-curves-a-tutorial/ 
        Useful math at: http://digilander.libero.it/b.dellavecchia/cagd/spline/Bezier/bezier-der.html
        More useful math at: http://www.kino3d.com/forum/viewtopic.php?f=7&t=8806 (look for "cerchio osculatore").
        The above has an error in the formula: compare with http://mathworld.wolfram.com/RadiusofCurvature.html.
        Derivative formula from https://en.wikipedia.org/wiki/B%C3%A9zier_curve#Cubic_B.C3.A9zier_curves.
        */
	class Bezier {
	public:

		/** Makes a curve from the 4 control points. 
		    The curve starts at p0 and ends at p3. Endpoint tangents go from p0 to p1 and from p2 to p3. */
		Bezier(const Point& p0, 
               const Point& p1,
			   const Point& p2, 
			   const Point& p3 );


		/** Returns the point for a given vaule of the parameter. */
		Point at(const float parameter) const;

        /** Returns the point for a given value of the parameter as expressed in distance units, not between 0 and 1. */
        Point atLength(const float parameter) const;

        /** Returns an approximate length of the curve. */
        float length() const;

        /** Rasterization of the curve, creates a polyline which has the given amount of points. 
            Points are equally spaced (the most simple algorithm). */
        void raster(std::vector<Point>& points, const size_t desiredPointCount) const;  // TODO: direct tests

        /** Radius of the circle tangent to the curve at that point. */
        float curvatureRadiusAt(const float parameter) const;

        
        /** Radius of the circle tangent to the curve at that point, parameter expressed as metric distance. */
        float curvatureRadiusAtLength(const float parameter) const;

	private:
        const Point p0;
		const Point p1;
		const Point p2;
		const Point p3;
	};


    /** Set of Bezier curves attached one after the other to form a complicated path. */
    class BezierPath {
    public:
        BezierPath(const std::vector<Point>& points);

        /** Returns the point for a given vaule of the parameter.
            The parameter goes from 1 to size(), then it hits the right curve inside the path. */
        Point at(const float parameter) const;

        /** Returns the point for a given value of the parameter as expressed in distance units, not between 0 and size(). */
        Point atLength(const float parameter) const;

        /** Approximate total length of the path. */
        float length() const;

        /** Returns the maximum value that you can give to the parameter. Which also is the number of curves in the path.
            This path is made of many curves. The point at, say, 1.5, is the point at 0.5 in the second curve.*/
        size_t size() const;

        /** Curvature radius of the spline at that particular distance. */
        float curvatureRadiusAtLength(const float parameter) const;


    private:
        std::vector <Bezier> elements;
    };
}

#endif