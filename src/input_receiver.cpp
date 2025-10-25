#include "input_receiver.hpp"

InputReceiver::InputReceiver()
{

}

InputReceiver::~InputReceiver()
{

}

void InputReceiver::addEvent(sf::Event event)
{
    events_.push_back(event);
}

std::vector<sf::Event>& InputReceiver::getEvents()
{
    return events_;
}

void InputReceiver::clearEvents()
{
    events_.clear();
}