#include "camera_update_component.hpp"
#include "player_update_component.hpp"

CameraUpdateComponent::CameraUpdateComponent()
{

}

CameraUpdateComponent::~CameraUpdateComponent()
{
    delete input_receiver_;
}

sf::FloatRect* CameraUpdateComponent::getPositionPointer()
{
    return &position_;
}

void CameraUpdateComponent::handleInput()
{
    position_.width = 1.0f;
    for (const auto& event : input_receiver_->getEvents()) {
        if (event.type == sf::Event::MouseWheelScrolled) {
            if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
                position_.width *= (event.mouseWheelScroll.delta > 0) ? 0.95f : 1.05f;
            }
        }
    }
    input_receiver_->clearEvents();
}

InputReceiver* CameraUpdateComponent::getInputReceiver()
{
    input_receiver_ = new InputReceiver();
    is_receives_input_ = true;
    return input_receiver_;
}

void CameraUpdateComponent::assemble(std::shared_ptr<LevelUpdateComponent> level_update_component,
                std::shared_ptr<PlayerUpdateComponent> player_update_component)
{
    player_position_ = player_update_component->getPositionPointer();
}

void CameraUpdateComponent::update(float time_since_last_update)
{
    if (is_receives_input_) {
        handleInput();
    } else {
        position_.width = 1;
    }
    position_.left = player_position_->left;
    position_.top = player_position_->top;
}