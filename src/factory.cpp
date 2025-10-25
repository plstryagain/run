#include "factory.hpp"

#include <iostream>

Factory::Factory(sf::RenderWindow* window)
    : window_{window},texture_{new sf::Texture{}}
{
    if (!texture_->loadFromFile("assets/graphics/texture.png")) {
        std::cout << "Texture not loaded!" << std::endl;
        return;
    }
}

Factory::~Factory()
{

}

void Factory::loadLevel(std::vector<GameObject>& game_objects, sf::VertexArray& canvas, InputDispatcher& input_dispatcher)
{

}