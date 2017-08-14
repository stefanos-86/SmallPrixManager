#include "BezierAdapter.h"

#include <SFML\Graphics\Vertex.hpp>
#include <SFML\Graphics\RenderTarget.hpp>

#include "PointConversion.h"

namespace spm {
    BezierAdapter::BezierAdapter(const Bezier& curve) :
        points(sf::LineStrip, Bezier::RASTER_POINT_COUNT)
    {
        storeRasterizedPoints(curve);
    }

    BezierAdapter::BezierAdapter(const BezierPath& curve) :
        points(sf::LineStrip, Bezier::RASTER_POINT_COUNT * curve.size())
    {
        storeRasterizedPoints(curve);
    }


    void BezierAdapter::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(points, states);
    }

}