
#include <SFML\Graphics.hpp>
#include <sstream>

using namespace sf;
using namespace std;

#include "ComplexPlane.h"

ComplexPlane::ComplexPlane(float aspectRatio)
{
	m_aspectRatio = aspectRatio;
	m_view.setSize(BASE_WIDTH, -BASE_HEIGHT * m_aspectRatio);
	m_view.setCenter(0.0,0.0);
	m_zoomCount = 0;
}

void ComplexPlane::zoomIn()
{
	m_zoomCount++;
	double x = BASE_WIDTH * (pow(BASE_ZOOM, m_zoomCount));
	double y = BASE_HEIGHT * (pow(BASE_ZOOM, m_zoomCount));
	m_view.setSize(x, y);
}

void ComplexPlane::zoomOut()
{
	m_zoomCount = m_zoomCount - 1;
	double x = BASE_WIDTH * (pow(BASE_ZOOM, m_zoomCount));
	double y = BASE_HEIGHT * (pow(BASE_ZOOM, m_zoomCount));
	m_view.setSize(x, y);
}

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
	/*ss << "(" << (m_view.getCenter()).x << "," << (m_view.getCenter()).y << ")";
	ss << "(" << m_mouseLocation.x << "," << m_mouseLocation.y << ")";
	text.setString("Mandelbrot Set\nCenter: (ss.str())\nCursor: (ss.str())\nLeft-click to zoom in\nRight-click to zoom out");*/
    stringstream ss;    
    ss << "Mandelbrot\n" << "Center: (" << m_view.getCenter().x << ", " << m_view.getCenter().y << ")\nCursor: " << m_mouseLocation.x << 
        ", " << m_mouseLocation.y << ")\nLeft - click to zoom in\nRight - click to zoom out";
    text.setString(ss.str());


}

// Counting the # of iterations of the Mandelbrot set for the given coordinate
size_t ComplexPlane::countIterations(Vector2f coord)
{
	int iterations = 0;
	// need to add more work
	return 22;
}

View ComplexPlane::getView()
{
	return m_view;
}