// Include important C++ libraries here
#include <sstream>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <complex>

using namespace sf;
using namespace std;
#include "ComplexPlane.h"

void Adds_Points(vector<Vector2f>&, vector<Vector2f>&);
void calculate(ComplexPlane& ComplexPlane, VertexArray &vertex_Array);

int main()
{
	// Create a video mode object
	VideoMode vm(1920, 1080);
	
	// Create and open a window for the game
	RenderWindow window(vm, "Mandelbrot", Style::Fullscreen);

	float aspectRatio = (VideoMode::getDesktopMode().width * 1.0f) / (VideoMode::getDesktopMode().height * 1.0f);


	ComplexPlane ComplexPlane(aspectRatio);
	
	// Text
	Text messageText;
	// Font
	Font font;
	font.loadFromFile("fonts/KOMIKAP_.ttf");
	// Set the font to our message
	messageText.setFont(font);


	// Assign the size of the text
	messageText.setCharacterSize(25);

	//Choose a color
	messageText.setFillColor(Color::White);

	// Position the text
	FloatRect textRect = messageText.getLocalBounds();
	messageText.setOrigin(textRect.left +
		textRect.width / 2.0f,textRect.top + textRect.height / 2.0f);
	messageText.setPosition(0,0);

	//Vectors
	Vector2f mousePos;

	//Vertex Array
	VertexArray vertex_Array(Points, VideoMode::getDesktopMode().height * VideoMode::getDesktopMode().width);
;

	//State of the loop
	enum State {CALCULATING,DISPLAYING};

	State current_State = CALCULATING;

	while (window.isOpen())
	{
		Event event;
		while(window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			//mouse input
			if(event.type == sf::Event::MouseButtonPressed)
			{
				if(event.mouseButton.button == sf::Mouse::Left)
				{	

					ComplexPlane.zoomIn();
					ComplexPlane.setCenter(mousePos);
					current_State = CALCULATING;

				}
				else if (event.mouseButton.button == sf::Mouse::Right)
				{
					ComplexPlane.zoomOut();
					ComplexPlane.setCenter(mousePos);
					current_State = CALCULATING;
				}
			}
			if (event.type == sf::Event::MouseMoved)
			{
				mousePos.x = sf::Mouse::getPosition(window).x;
				mousePos.y = sf::Mouse::getPosition(window).y;

				ComplexPlane.setMouseLocation(mousePos);
			}
			
		}
		if (current_State == CALCULATING)
		{
			calculate(ComplexPlane,vertex_Array);
		}

		//close the game
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}


		// Clear everything from the last frame
		window.clear();
		ComplexPlane.loadText(messageText);
		window.draw(messageText);
		// Show everything we just drew
		window.display();


	}

	return 0;
}

void calculate(ComplexPlane& ComplexPlane, VertexArray& vertex_Array)
{

}


