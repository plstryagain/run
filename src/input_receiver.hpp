#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class InputReceiver
{
public:
    InputReceiver();
    ~InputReceiver();
    InputReceiver(const InputReceiver& other) = delete;
    void operator=(const InputReceiver& other) = delete;

public:
    void addEvent(sf::Event event);
    std::vector<sf::Event>& getEvents();
    void clearEvents();

private:
    std::vector<sf::Event> events_;
};