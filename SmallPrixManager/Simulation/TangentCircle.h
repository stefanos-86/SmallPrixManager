#ifndef SPM_TANGENT_CIRCLE
#define SPM_TANGENT_CIRCLE

#include <SFML\Graphics\Vertex.hpp>

namespace spm {

    /** In italian is "cerchio osculatore". */
    class TangentCircle {
    public:
        /** Circle passing trough this points. */
        TangentCircle(const sf::Vector2f& p0, const sf::Vector2f& p1, const sf::Vector2f& p2);

        float radius() const;

    private:
        float a, b, c; // Coefficients of the equations.
    };
	
}

#endif