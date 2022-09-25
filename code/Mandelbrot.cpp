// Include important C++ libraries here
#include <sstream>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <complex>
#include "ComplexPlane.h"


using namespace sf;
using namespace std;

void Adds_Points(vector<Vector2f>&, vector<Vector2f>&);

int main()
{
	// Create a video mode object
	VideoMode vm(1920, 1080);
	
	// Create and open a window for the game
	RenderWindow window(vm, "Mandelbrot", Style::Fullscreen);

	ComplexPlane ComplexPlane(VideoMode::getDesktopMode().height / VideoMode::getDesktopMode().width);



	// Text
	Text messageText;
	// Font
	Font font;
	font.loadFromFile("fonts/KOMIKAP_.ttf");
	// Set the font to our message
	messageText.setFont(font);


	// Assign the actual message
	messageText.setString("Nothing");
	messageText.setCharacterSize(50);

	//Choose a color
	messageText.setFillColor(Color::White);


	// Position the text
	FloatRect textRect = messageText.getLocalBounds();
	messageText.setOrigin(textRect.left +
		textRect.width / 2.0f,textRect.top + textRect.height / 2.0f);
	messageText.setPosition(1920 / 2.0f, 100 / 2.0f);

	//Vectors
	Vector2f mousePos;


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

				}
				else if (event.mouseButton.button == sf::Mouse::Right)
				{
					ComplexPlane.zoomOut();
				}
			}
			if (event.type == sf::Event::MouseMoved)
			{
				mousePos.x = sf::Mouse::getPosition(window).x;
				mousePos.y = sf::Mouse::getPosition(window).y;

				ComplexPlane.setMouseLocation(mousePos);
			}
			
		}

		//close the game
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}


		// Clear everything from the last frame
		window.clear();

			window.draw(messageText);


		// Show everything we just drew
		window.display();


	}

	return 0;
}


