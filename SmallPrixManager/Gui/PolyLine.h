#ifndef SPM_POLYLINE
#define SPM_POLYLINE

#include <vector>



namespace spm {

	/** Very simple wrapper to draw a line strip. */
	class PolyLine
	{
	public:
		/** Will copy the content and also truncate the decimals.
		    The vector should have the x, y couples one after another.
			They should also be in screen coordinates already. */
		PolyLine(const std::vector<float>& points);
		~PolyLine();

	private:
		//sf::VertexArray points;

		/** Makes it a drawable. */
		//virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	};

}
#endif