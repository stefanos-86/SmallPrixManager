#ifndef SPM_PARAMETRIC_CURVE
#define SPM_PARAMETRIC_CURVE

#include <vector>

namespace spm {

	class Point {
	public:
		static float Distance(const Point& a, const Point& b);


		Point(const float x, const float y, const float parameter);

		
		float x;
		float y;
		float parameter;
	};

	bool operator==(const Point& lhs, const Point& rhs);

	/**  DA RIFARE --- deve essere basara su Bezier e calcolare i punti al volo.
	
	Parametric curve expressed by some known points.
		The important thing is to be able to know the point at a given parameter
		and the direction of the tangent. Secondarily, if a point is inside/outside the curve
		it it is closed.
		I am too ignorant to do a proper representation (NURBS, Bezier patch...).
	*/
	class ParametricCurve {
	public:
		/** Makes a curve from the given points (x, y) couples. Compute the parameter
			using the distance between points. */
		ParametricCurve(const std::vector<float> points);

		/** Returns the point at a given parameter. Linear interpolation otherwise. */
		Point at(const float parameter) const;
	private:
		std::vector<Point> points;  // Sorted by parameters!
	};
}

#endif