
#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>

using namespace sf;
using namespace std;

#include "ComplexPlane.h"
#include <math.h>

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
	double y = BASE_HEIGHT * m_aspectRatio * (pow(BASE_ZOOM, m_zoomCount));
	//m_view.zoom(-.5f);
	m_view.setSize(x, y);

	//used for debugging
	cout << m_zoomCount << endl;
}

void ComplexPlane::zoomOut()
{
	m_zoomCount = m_zoomCount - 1;
	double x = BASE_WIDTH * (pow(BASE_ZOOM, m_zoomCount));
	double y = BASE_HEIGHT * m_aspectRatio * (pow(BASE_ZOOM, m_zoomCount));
	//m_view.zoom(-.5f);
	m_view.setSize(x, y);
	

	//used for debugging
	cout << m_zoomCount << endl;
}

// The center coordinate of the view is set by the given coordinate
void ComplexPlane::setCenter(Vector2f coord)
{
	m_view.setCenter(Vector2f(coord));
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
    ss << "Mandelbrot\n" << "Center: (" << m_view.getCenter().x << ", " << m_view.getCenter().y << ")\nCursor: (" << m_mouseLocation.x << 
        ", " << m_mouseLocation.y << ")\nLeft - click to zoom in\nRight - click to zoom out";
    text.setString(ss.str());

}

// Counting the # of iterations of the Mandelbrot set for the given coordinate
size_t ComplexPlane::countIterations(Vector2f coord)
{
	size_t iterationCount = 0;
	float x = coord.x;
	float y = coord.y;

	float newX = x;
	float newY = y;

	for (int i = 0; i < MAX_ITER; i++)
	{
		// real number component
		float realNum = x * x - y * y;
		// imaginary number component, i
		float iNum = 2 * x * y;
		// z^2 + c
		x = realNum + newX;
		y = iNum + newY;

		iterationCount++;
 	}
	return iterationCount;
}

// 
void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{
	if (count >= 0 && count <= 16)
	{
		r = 0;
		g = 255;
		b = 0;
	}
	else if (count > 16 && count <= 32)
	{
		r = 255;
		g = 255;
		b = 0;
	}
	else if (count > 32 && count < 64)
	{
		r = 0;
		g = 0;
		b = 255;
	}
	else if (count == 64) // max iteration
	{
		r = 0;
		g = 0;
		b = 0;
	}
}

View ComplexPlane::getView()
{
	return m_view;
}