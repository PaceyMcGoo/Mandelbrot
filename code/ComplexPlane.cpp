#include "ComplexPlane.h"
#include <SFML\Graphics.hpp>

using namespace sf;
using namespace std;

// The center coordinate of the view is set by the given coordinate
void ComplexPlane::setCenter(Vector2f coord)
{
	m_view.setCenter(Vector2f(coord));
	m_view.setSize(Vector2f(1980.f, 1080.f));
}

// Update the mouse cursor position with the given coordinate value
void ComplexPlane::setMouseLocation(Vector2f coord)
{
	m_mouseLocation = coord;
}

// Loads the information text (center, cursor, instructions) to the screen
void ComplexPlane::loadText(Text& text)
{
	text.setString("Mandelbrot Set\nCenter: (");
	// need to add more work
}

// Counting the # of iterations of the Mandelbrot set for the given coordinate
size_t ComplexPlane::countIterations(Vector2f coord)
{
	int iterations = 0;
	// need to add more work
}