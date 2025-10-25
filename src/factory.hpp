#pragma once

#include "input_dispatcher.hpp"
#include "game_object.hpp"

#include <SFML/Graphics.hpp>

class Factory
{
public:
    Factory(sf::RenderWindow* window);
    ~Factory();
    Factory(const Factory& other) = delete;
    void operator=(const Factory& other) = delete;

public:
    void loadLevel(std::vector<GameObject>& game_objects, sf::VertexArray& canvas, InputDispatcher& input_dispatcher);
    sf::Texture* texture_;

private:
    sf::RenderWindow* window_;
};