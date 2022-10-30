#include "Bezier.h"

#include <stdexcept>

#include "Math.h"

#include <algorithm>
#include <iterator>
#include <iostream>

namespace spm {

    const size_t Bezier::RASTER_POINT_COUNT = 10;

    Bezier::Bezier(const Point& p0,
                   const Point& p1,
                   const Point& p2,
                   const Point& p3) :
    p0(p0), p1(p1), p2(p2), p3(p3) 
    {
        computeRasterPoints();
        computeLength();
    }

    /** Formula is:
        P = (1–t)^3p0 + 3(1–t)^2t p1 + 3(1–t)t^2 p2+ t^3 p3
        simplified to compute stuff just once.
    */
    Point Bezier::at(const float parameter) const {
        stopBadParameters(parameter);

        const float u = 1.0f - parameter;
        const float tt = parameter * parameter;
        const float uu = u*u;
        const float uuu = uu * u;
        const float ttt = tt * parameter;

        Point p = uuu * p0; //first term
        p += 3 * uu * parameter * p1; //second term
        p += 3 * u * tt * p2; //third term
        p += ttt * p3; //fourth term

        return p;
    }


    Point Bezier::atLength(const float length) const {
        return at(lengthToParameter(length));
    }

    float Bezier::length() const {
        return lengthCache;
    }


    void Bezier::raster(std::vector<Point>& points) const {
        // Assume raster points have already been computed. This must be true, as they are "baked" in the constructor.
        std::copy(std::begin(rasterCache), std::end(rasterCache), std::back_inserter(points));
    }


    float Bezier::curvatureRadiusAt(const float parameter) const {
        // Formula is: sqrt( (x1*x1+y1*y1)**3) / (x1*y2-y1*y2); where xi, yi = values of the i-th derivative.

        const Point d0 = (p1 - p0);
        const Point d1 = (p2 - p1);
        const Point d2 = (p3 - p2);

        const float oneMinusT = 1 - parameter;

        const Point firstDerivative = 3 * oneMinusT * oneMinusT * d0 +
                                      6 * oneMinusT * parameter * d1 +
                                      3 * parameter * d2;

        const Point dd0 = p2 - 2 * p1 + p0;
        const Point dd1 = p3 - 2 * p2 + p1;

        const Point secondDerivative = 6 * oneMinusT * dd0 + 
                                       6 * parameter * dd1;

        const float x1 = firstDerivative.x;
        const float y1 = firstDerivative.y;

        const float x2 = secondDerivative.x;
        const float y2 = secondDerivative.y;

        const float k = std::sqrt(x1 * x1 + y1 * y1);

        const float radius =  (k * k * k) / (x1*y2 - y1*x2);
        return radius;
    }


    float Bezier::curvatureRadiusAtLength(const float length) const {
        return curvatureRadiusAt(lengthToParameter(length));
    }


    float Bezier::lengthToParameter(const float l) const{
        return l / length();
    }

    void Bezier::stopBadParameters(const float parameter) const {
        if (parameter < 0 || parameter > 1)
            throw std::runtime_error("Bezier parameter out of interval.");
    }

    void Bezier::computeLength() {
        std::vector<Point> points;
        raster(points);

        lengthCache = 0;

        auto cursor = std::begin(points);
        auto last = std::end(points) - 1;
        while (cursor != last) {
            lengthCache += (*cursor - *(cursor + 1)).magnitude();
            cursor++;
        }
    }

    void Bezier::computeRasterPoints() {
        const size_t intervalCount = RASTER_POINT_COUNT - 1; // Mind the fencepost: n points, n - intervals in between.
        const float step = 1.0f / intervalCount;  
        float cursor = 0;

        // Make room for the new points.
        rasterCache.reserve(RASTER_POINT_COUNT);

        for (size_t i = 0; i <= intervalCount; ++i){
            rasterCache.push_back(at(cursor));
            cursor += step;
        }
    }


    BezierPath::BezierPath(const std::vector<Point>& points) {
        static const float scale = 0.0015f;  // Tweak until it works... Very small = precise curves, close to the points.
        std::vector<Point> controlPoints;

        if (points.size() < 2)
            throw std::runtime_error("Need at least 3 points for a Bezier path.");

        // Special case: 1st point (the block is to re-use variable names and keep consistent with all cases).
        {
            size_t i = 0;
            Point p1 = points[i];
            Point p2 = points[i + 1];

            Point tangent = (p2 - p1);
            Point q1 = p1 + scale * tangent;

            controlPoints.push_back(p1);
            controlPoints.push_back(q1);
        }

        for (size_t i = 1; i < points.size() - 1; ++i)
        {
            Point p0 = points[i - 1];
            Point p1 = points[i];
            Point p2 = points[i + 1];
            Point tangent = (p2 - p0);
            Point q0 = p1 - scale * tangent * (p1 - p0).magnitude();
            Point q1 = p1 + scale * tangent * (p2 - p1).magnitude();

            controlPoints.push_back(q0);
            controlPoints.push_back(p1);
            controlPoints.push_back(q1);
        }

        // Special handling of last point.
        {
            size_t i =  points.size() - 1;
            Point p0 = points[i - 1];
            Point p1 = points[i];
            Point tangent = p1 - p0;
            tangent.normalize();
            Point q0 = p1 - scale * tangent;

            controlPoints.push_back(q0);
            controlPoints.push_back(p1);
        }

        for (size_t i = 0; i < controlPoints.size() - 1; i += 3){
            elements.push_back(Bezier(controlPoints[i], controlPoints[i + 1], controlPoints[i + 2], controlPoints[i + 3]));
        }
        
    }


    Point BezierPath::at(const float parameter) const {
        const size_t integer_part = static_cast<size_t>(parameter);
        const float decimals = parameter - integer_part;

        return elements.at(integer_part).at(decimals);
    }


    Point BezierPath::atLength(const float parameter) const {
        // Don't forget that component curves are not all equals!
        auto cursor = std::begin(elements);
        auto end = std::end(elements);

        float cumulativeLength = 0;
        while (cursor != end) {
            const float lengthOfCurve = cursor->length();
            if (cumulativeLength + lengthOfCurve > parameter) {
                const float lengthInCurve = parameter - cumulativeLength;
                return cursor->atLength(lengthInCurve);
            }
            cumulativeLength += lengthOfCurve;
            cursor++;
        }

        return (cursor -1)->at(1);  //There must be an off by one over there...
            
    }



    float BezierPath::length() const {
        float length = 0;
        for (const auto& c : elements)
            length += c.length();
        return length;
    }


    void BezierPath::raster(std::vector<Point>& points) const {
        const size_t totalPoints = size() * Bezier::RASTER_POINT_COUNT;
        
        for (const Bezier& c: elements)
            c.raster(points);
    }


    size_t BezierPath::size() const {
        return elements.size();
    }

    float BezierPath::curvatureRadiusAtLength(const float parameter) const {
        // Don't forget that component curves are not all equals!   TODO: code that find the spline is duplicated... + there is an off by one at the end!
        auto cursor = std::begin(elements);
        auto end = std::end(elements);

        float cumulativeLength = 0;
        while (cursor != end) {
            const float lengthOfCurve = cursor->length();
            if (cumulativeLength + lengthOfCurve > parameter) {
                const float lengthInCurve = parameter - cumulativeLength;
                return cursor->curvatureRadiusAtLength(lengthInCurve);
            }
            cumulativeLength += lengthOfCurve;
            cursor++;
        }

        return (cursor -1)->curvatureRadiusAtLength(1);  //There must be an off by one over there...
    }



}
