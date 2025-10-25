#include "input_dispatcher.hpp"

InputDispatcher::InputDispatcher(sf::RenderWindow* window)
    : window_{window}
{
}

InputDispatcher::~InputDispatcher()
{

}

void InputDispatcher::dispatchInputEvents()
{
    sf::Event event;
    while (window_->pollEvent(event)) {
        if (event.type == sf::Event::KeyPressed &&
            event.key.code == sf::Keyboard::Escape) {
                window_->close();
        }
        for (const auto& ir: input_receivers_) {
            ir->addEvent(event);
        }
    }
}

void InputDispatcher::registerNewInputReceiver(InputReceiver* ir)
{
    input_receivers_.push_back(ir);
}