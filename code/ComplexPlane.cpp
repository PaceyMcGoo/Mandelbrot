#include "ComplexPlane.h"
#include <SFML\Graphics.hpp>

using namespace sf;
using namespace std;

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





