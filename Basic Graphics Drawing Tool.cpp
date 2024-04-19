#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Basic Graphics Drawing Tool");
    window.setFramerateLimit(60);

    // Create shapes and text
    sf::RectangleShape rectangle;
    sf::CircleShape circle;
    sf::Vertex line[2];
    sf::Font font;
    sf::Text text;

    // Load font
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Error: Unable to load font." << std::endl;
        return 1;
    }

    // Set up text properties
    text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::Black);

    // Event loop
    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // Draw rectangle
                    rectangle.setSize(sf::Vector2f(100, 50));
                    rectangle.setFillColor(sf::Color::Blue);
                    rectangle.setPosition(event.mouseButton.x, event.mouseButton.y);

                } else if (event.mouseButton.button == sf::Mouse::Right) {
                    // Draw circle
                    circle.setRadius(50);
                    circle.setFillColor(sf::Color::Red);
                    circle.setPosition(event.mouseButton.x - 50, event.mouseButton.y - 50);

                }
            }

            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                // Draw line (left click + drag)
                line[0].position = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
            }

            if (event.type == sf::Event::MouseMoved && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                // Update line endpoint
                line[1].position = sf::Vector2f(event.mouseMove.x, event.mouseMove.y);
                line[1].color = sf::Color::Black;
            }

            if (event.type == sf::Event::KeyPressed) {
                // Draw text (press any key)
                text.setString("Hello, SFML!");
                text.setPosition(event.key.x, event.key.y);
            }
        }

        // Clear the window
        window.clear(sf::Color::White);

        // Draw shapes and text
        window.draw(rectangle);
        window.draw(circle);
        window.draw(line, 2, sf::Lines);
        window.draw(text);

        // Display
        window.display();
    }

    return 0;
}
