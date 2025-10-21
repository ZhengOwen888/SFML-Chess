// develop branch
#include <SFML/Window.hpp>

int main()
{
	// declare window
	sf::Window window;

	// create and define window
	window.create
	(
		sf::VideoMode({800, 600}), // size: 800 x 600
		"SFML Chess", 			   // title: SFML Chess
		sf::Style::Default, 	   // style: Titlebar | Resize | Close
		sf::State::Windowed		   // state: floating
	);

	// run program as long as the window is open
	while (window.isOpen())
	{
		// check all the window's events that triggered since the last iteration of loop
		while (const std::optional<sf::Event> event = window.pollEvent())
		{
			// "close requested" event: we close the window
			if (event->is<sf::Event::Closed>())
				window.close();
		}
	}


	//  plan to make cmake file
	//  g++ -std=c++17 main.cpp -I/sfml/3.0.2/include -o program -L/sfml/3.0.2/lib -lsfml-graphics -lsfml-window -lsfml-system

	return 0;
}