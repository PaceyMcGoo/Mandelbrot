#pragma once

#include <SFML\Graphics.hpp>
#include "ComplexPlane.cpp"


using namespace sf;
using namespace std;

class ComplexPlane
{
	private:
		Vector2f m_mouseLocation;
		View m_view;
		int m_zoomCount = 0;
		float m_aspectRatio;

	public:
		ComplexPlane(float aspectRatio);
		void zoomIn();
		void zoomOut();
		void setCenter(Vector2f coord);
		View getView();
		void setMouseLocation(Vector2f coord) { m_mouseLocation = coord; };
		void loadText(Text& text);
		size_t countInterations(Vector2f coord);
		void interationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b);


};
