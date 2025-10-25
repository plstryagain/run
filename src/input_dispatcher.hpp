#pragma once

#include "input_receiver.hpp"

#include <SFML/Graphics.hpp>
#include <vector>

class InputDispatcher
{
public:
    InputDispatcher(sf::RenderWindow* window);
    ~InputDispatcher();
    InputDispatcher(const InputDispatcher& other) = delete;
    void operator=(const InputDispatcher& other) = delete;

public:
    void dispatchInputEvents();
    void registerNewInputReceiver(InputReceiver* ir);

private:
    sf::RenderWindow* window_;
    std::vector<InputReceiver*> input_receivers_;
};