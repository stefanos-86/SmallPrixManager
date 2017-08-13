#ifndef SPM_POLYLINE
#define SPM_POLYLINE

#include <SFML/Graphics/VertexArray.hpp>

namespace spm {

	/** Very simple wrapper to draw a line strip. */
	class PolyLine : public sf::Drawable
	{
	public:
		PolyLine();
		~PolyLine();

	private:
		sf::VertexArray points;

		/** Makes it a drawable. */
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	};

}
#endif