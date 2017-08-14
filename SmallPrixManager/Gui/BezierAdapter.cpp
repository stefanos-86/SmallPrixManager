#include "BezierAdapter.h"

#include <SFML\Graphics\Vertex.hpp>
#include <SFML\Graphics\RenderTarget.hpp>

namespace spm {

    const size_t BezierAdapter::POINT_COUNT = 20;

    BezierAdapter::BezierAdapter(const Bezier& curve) :
        points(sf::LineStrip, BezierAdapter::POINT_COUNT)
    {
        const float step = 1.0f / BezierAdapter::POINT_COUNT;
        float cursor = 0;

        for (size_t i = 0; i < BezierAdapter::POINT_COUNT; ++i){
            this->points[i].position = curve.at(cursor);
            this->points[i].color = sf::Color::White;
            cursor += step;
        }
    }

    BezierAdapter::BezierAdapter(const BezierPath& curve) :
        points(sf::LineStrip, BezierAdapter::POINT_COUNT * curve.size())
    {
        const size_t totalPoints = curve.size() * BezierAdapter::POINT_COUNT;
        const float step = 1.0f / BezierAdapter::POINT_COUNT;
        float cursor = 0;

        for (size_t i = 0; i < totalPoints; ++i){  //TODO: duplicated code
            this->points[i].position = curve.at(cursor);
            this->points[i].color = sf::Color::White;
            cursor += step;
        }
    }


    void BezierAdapter::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(points, states);
    }

}