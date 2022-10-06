// C++ libraries
#include <sstream>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <complex>



using namespace sf;
using namespace std;
#include "ComplexPlane.h"

int main()
{
	// Create a video mode object
	VideoMode vm(1920, 1080);

	// Create and open a window for the game
	RenderWindow window(vm, "Mandelbrot", Style::Default);

	//Calculates Aspect Ratio
	float aspectRatio = (VideoMode::getDesktopMode().height * 1.0f) / (VideoMode::getDesktopMode().width * 1.0f);
	cout << aspectRatio << endl;

	//Initializes the ComplexPlane Object
	ComplexPlane ComplexPlane(aspectRatio);

	//view for hud
	View hudView(sf::FloatRect(0.0f, 0.0f, 1920.0f, 1080.0f));
//window.setView(ComplexPlane.getView());
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
		textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	messageText.setPosition(0, 0);

	//Vectors
	Vector2f mousePos;

	//Vertex Array
	VertexArray vertex_Array(Points, VideoMode::getDesktopMode().height * VideoMode::getDesktopMode().width);
	;

	//State of the loop
	enum State { CALCULATING, DISPLAYING };

	State current_State = CALCULATING;

	while (window.isOpen())
	{
		/*
		##############################
		Handle User Input
		##############################
		*/

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			//mouse input
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					ComplexPlane.setCenter(mousePos);
					ComplexPlane.zoomIn();
					current_State = CALCULATING;

				}
				else if (event.mouseButton.button == sf::Mouse::Right)
				{
					ComplexPlane.setCenter(mousePos);
					ComplexPlane.zoomOut();
					current_State = CALCULATING;
				}
			}
			if (event.type == sf::Event::MouseMoved)
			{

				mousePos = window.mapPixelToCoords(Mouse::getPosition(), ComplexPlane.getView());

				ComplexPlane.setMouseLocation(mousePos);
			}

		}

		//close the game
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		/*
		##############################
		Update the Scene
		##############################
		*/

		size_t screenHeight = VideoMode::getDesktopMode().height;
		size_t screenWidth = VideoMode::getDesktopMode().width;

		if (current_State == CALCULATING)
		{
			//Calculation 
			//two for-loops to check every pixel accross the screen
			for (unsigned int i = 0; i < screenHeight; i++) // i is for height
			{
				for (unsigned int j = 0; j < screenWidth; j++) // j is for width
				{

					// assign j, i coordinate to vertex_Array position element
					vertex_Array[j + i * screenWidth].position = { (float)j, (float)i };

					// mapping pixel location j, i relative to complex coordinate
					Vector2f pixelLocation = window.mapPixelToCoords(Vector2i(j, i), ComplexPlane.getView());

					// counter how many times the calculation (iteration) is being done
					size_t iterations = ComplexPlane.countIterations(pixelLocation);

					// store RGB values with current pixelLocation
					Uint8 R = 0;
					Uint8 G = 0;
					Uint8 B = 0;
					// assign RGB values by reference
					ComplexPlane.iterationsToRGB(iterations, R, G, B);
					// set color variable in vertex_Array as screen coordinate j, i
					vertex_Array[j + i * screenWidth].color = { R, G, B };
				}
				//cout << i << " " << endl;
			}
			current_State = DISPLAYING;
		}

		ComplexPlane.loadText(messageText);

		/*
		##############################
		Draw the Scene
		##############################
		*/

		// Clear everything from the last frame
		window.clear();
		window.draw(vertex_Array);

		window.draw(messageText);
				
		// Show everything we just drew
		window.display();

	}

	return 0;
}


