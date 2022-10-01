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

// Function prototype
void Adds_Points(vector<Vector2f>&, vector<Vector2f>&);
// void calculate(ComplexPlane& ComplexPlane, VertexArray& vertex_Array);

int main()
{
	// Create a video mode object
	VideoMode vm(1920, 1080);

	// Create and open a window for the game
	RenderWindow window(vm, "Mandelbrot", Style::Fullscreen);

	//Calculates Aspect Ratio
	float aspectRatio = (VideoMode::getDesktopMode().width * 1.0f) / (VideoMode::getDesktopMode().height * 1.0f);

	//Initializes the ComplexPlane Object
	ComplexPlane ComplexPlane(aspectRatio);

	//view for hud
	View hudView(sf::FloatRect(0, 0, 1920, 1080));

	/*used for debugging*/
	RectangleShape rect;
	rect.setSize(Vector2f(800, 800));
	rect.setFillColor(Color::Red);


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
					//ComplexPlane.setCenter(mousePos);
					current_State = CALCULATING;

				}
				else if (event.mouseButton.button == sf::Mouse::Right)
				{
					ComplexPlane.setCenter(mousePos);
					ComplexPlane.zoomOut();
					//ComplexPlane.setCenter(mousePos);
					current_State = CALCULATING;
				}
			}
			if (event.type == sf::Event::MouseMoved)
			{
				/*mousePos.x = sf::Mouse::getPosition(window).x;
				mousePos.y = sf::Mouse::getPosition(window).y;*/
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

		if (current_State == CALCULATING)
		{
			//Calculation 
			//two for-loops to check every pixel accross the screen
			for (int i = 0; i < VideoMode::getDesktopMode().height; i++) // i is for height
			{
				for (int j = 0; j < VideoMode::getDesktopMode().width; j++) // j is for width
				{
					// assign j, i coordinate to vertex_Array position element
					int pixel = j + i * VideoMode::getDesktopMode().width;
					vertex_Array[pixel].position = { (float)j, (float)i };
					// mapping coordinate relative to pixel location j, i
					Vector2f pixelLocation = window.mapPixelToCoords(Vector2i(j, i), ComplexPlane.getView());
					// counter how many times the calculation (iteration) is being done
					size_t iterations = ComplexPlane.countIterations(pixelLocation);
					// store RGB values for current pixelLocation
					Uint8 R, G, B;
					// assign RGB values by reference
					ComplexPlane.iterationsToRGB(iterations, R, G, B);
					// set color variable in vertex_Array as screen coordinate j, i
					vertex_Array[pixel].color = { R, G, B };
					




				}
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

		//window.draw(rect);
		window.setView(hudView);

		window.draw(messageText);

		window.setView(ComplexPlane.getView());
		window.draw(vertex_Array);

		


		// Show everything we just drew
		window.display();

	}

	return 0;
}


