// this main file is not final

// this is just for testing that SFML is downloaded properly for now
#include <SFML/Window.hpp>

int main()
{
    sf::Window window;

    window.create(
        sf::VideoMode({800, 800}), // window 800 x 800
        "SFML_CHESS",              // title
        sf::Style::Default,        // Titlebar | Resize | Close
        sf::State::Windowed        // floating window
    );

    // run the program while window is open
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
    }

    return 0;
}