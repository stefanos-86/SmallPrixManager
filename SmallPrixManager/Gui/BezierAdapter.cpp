#include "BezierAdapter.h"

#include "PointConversion.h"

namespace spm {
    BezierAdapter::BezierAdapter(const Bezier& curve)
    {
        storeRasterizedPoints(curve);
    }

    BezierAdapter::BezierAdapter(const BezierPath& curve)
    {
        storeRasterizedPoints(curve);
    }

    void BezierAdapter::draw(SDL_Renderer* renderer) const {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawLines(renderer, points.data(), points.size());
    }
}