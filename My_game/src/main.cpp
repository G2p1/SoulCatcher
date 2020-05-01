#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
    // Load a sprite to display
    sf::CircleShape shape(500,10000);
    shape.setFillColor(sf::Color(255,121,45));
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // Clear screen
        window.clear(sf::Color(128, 106, 89));
        // Draw the sprite
        window.draw(shape);
        // Draw the string
        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}