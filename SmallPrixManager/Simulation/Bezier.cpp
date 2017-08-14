#include "Bezier.h"

#include "Math.h"

namespace spm {
    Bezier::Bezier(const Point& p0,
                   const Point& p1,
                   const Point& p2,
                   const Point& p3) :
    p0(p0), p1(p1), p2(p2), p3(p3) 
    {    }

    /** Formula is:
        P = (1–t)^3p0 + 3(1–t)^2t p1 + 3(1–t)t^2 p2+ t^3 p3
        simplified to compute stuff just once.
    */
    Point Bezier::at(const float parameter) const {
        // TODO: reject nonsensical parameters

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


    Point Bezier::atLength(const float parameter) const {
        const float uniformParameter = parameter / length();
        return at(uniformParameter);
    }

    float Bezier::length() const {
        std::vector<Point> points;
        raster(points, 10);

        float length = 0;

        auto cursor = std::begin(points);
        auto last = std::end(points) - 1;
        while (cursor != last) {
            length += (*cursor - *(cursor + 1)).magnitude();
            cursor++;
        }

        return length;
    }


    void Bezier::raster(std::vector<Point>& points, const size_t desiredPointCount) const {
        const float step = 1.0f / (desiredPointCount - 1);  // Mind the fencepost: the last point has to be at(1).
        float cursor = 0;

        points = std::vector<Point>(desiredPointCount, Point(0, 0));

        for (size_t i = 0; i <= desiredPointCount - 1; ++i){
            points[i] = at(cursor);
            cursor += step;
        }
    }


    BezierPath::BezierPath(const std::vector<Point>& points) {
        
        static const float scale = 0.0015f;  // Tweak until it works... Very small = precise curves, close to the points.
        std::vector<Point> controlPoints;

        /* TODO
        if (points.size() < 2)
        {
            throw...;
        }*/

        for (size_t i = 0; i < points.size(); ++i)
        {
            if (i == 0) // is first  --- TODO: pull out of the loop, then iterate from 1
            {
                Point p1 = points[i];
                Point p2 = points[i + 1];

                Point tangent = (p2 - p1);
                Point q1 = p1 + scale * tangent;

                controlPoints.push_back(p1);
                controlPoints.push_back(q1);
            }
            else if (i == points.size() - 1) //last  -- TODO: same as above, stop the iteration one short!
            {
                Point p0 = points[i - 1];
                Point p1 = points[i];
                Point tangent = p1 - p0;
                tangent.normalize();
                Point q0 = p1 - scale * tangent;

                controlPoints.push_back(q0);
                controlPoints.push_back(p1);
            }
            else
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

        return Point(-1, -1); //TODO: throw o prevenire parametri assurdi.
    }

    float BezierPath::length() const {
        float length = 0;
        for (const auto& c : elements)
            length += c.length();
        return length;
    }

    size_t BezierPath::size() const {
        return elements.size();
    }



}