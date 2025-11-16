#include "game_object.hpp"
#include "factory.hpp"
#include "input_dispatcher.hpp"

#include <SFML/Graphics.hpp>
#include <vector>

int main()
{
    // sf::RenderWindow window{sf::VideoMode::getDesktopMode(), "Booster", sf::Style::Fullscreen};
    sf::RenderWindow window{sf::VideoMode::getDesktopMode(), "Booster", sf::Style::Default};
    sf::VertexArray canvas{sf::Quads, 0};

    InputDispatcher input_dispatcher{&window};
    std::vector<GameObject> game_objects;
    Factory factory{&window};
    factory.loadLevel(game_objects, canvas, input_dispatcher);

    sf::Clock clock;

    const sf::Color  BACKGROUND_COLOR{100, 100, 100, 255};

    while (window.isOpen()) {
        float time_taken_in_seconds = clock.restart().asSeconds();
        input_dispatcher.dispatchInputEvents();
        window.clear(BACKGROUND_COLOR);
        for (auto& game_object : game_objects) {
            game_object.update(time_taken_in_seconds);
        }
        for (auto& game_object : game_objects) {
            game_object.draw(canvas);
        }
        window.display();
    }

    return 0;
}