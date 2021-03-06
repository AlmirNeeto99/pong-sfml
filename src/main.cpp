#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "Ball.hpp"
#include "Paddle.hpp"
#include "SFML/Graphics.hpp"
#include "Window.hpp"

int main(int argc, char const *argv[]) {
    srand(time(0));
    sf::RenderWindow window(sf::VideoMode(Window::WIDTH, Window::HEIGHT), "Pong", sf::Style::Titlebar | sf::Style::Close);

    const int yOffset = (Window::HEIGHT / 2) - (Paddle::HEIGHT / 2);
    Paddle p1(Paddle::WIDTH, yOffset), p2(Window::WIDTH - (Paddle::WIDTH * 2), yOffset);

    Ball ball(Window::WIDTH / 2, Window::HEIGHT / 2);
    ball.setFillColor(sf::Color::Green);

    sf::RectangleShape l1(sf::Vector2f(1, Window::HEIGHT));
    l1.setPosition(sf::Vector2f((Window::WIDTH / 2) - .5f, 0));

    sf::Event event;
    const sf::Color clearColor(120, 15, 30, 255);

    sf::Clock clock;
    double dt = 0;

    sf::Font font;
    font.loadFromFile("../resources/arial.ttf");  // ! RELATIVE TO BUILD FOLDER

    const sf::String fpsString = "FPS: ";

    sf::Text fps;
    fps.setFont(font);
    fps.setString(fpsString);
    fps.setFillColor(sf::Color(0, 0, 0, 255));

    std::string fpsValue;
    std::stringstream fpsStream;

    while (window.isOpen()) {
        dt = clock.restart().asSeconds();

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear(clearColor);
        // Update
        p1.update(dt);
        p2.update(dt);
		ball.update(dt);
        // Draw
        window.draw(p1);
        window.draw(p2);
        window.draw(l1);
        window.draw(ball);
        // FPS Logic
        fpsStream << std::fixed << std::setprecision(2) << floor(1.f / dt);
        fpsValue = fpsStream.str();
        fpsStream.str(std::string());
        fps.setString(fpsString + fpsValue);
        window.draw(fps);
        // Swapping buffers
        window.display();
    }

    return 0;
}
