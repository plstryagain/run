#include "player_update_component.hpp"
#include "sound_engine.hpp"
#include "level_update_component.hpp"

PlayerUpdateComponent::PlayerUpdateComponent()
{

}

PlayerUpdateComponent::~PlayerUpdateComponent()
{

}

sf::FloatRect* PlayerUpdateComponent::getPositionPointer()
{
    return &position_;
}

bool* PlayerUpdateComponent::getGroundedPointer()
{
    return &is_grounded_;
}

InputReceiver* PlayerUpdateComponent::getInputReceiver()
{
    return &input_receiver_;
}

void PlayerUpdateComponent::handleInput()
{
    input_receiver_.clearEvents();
}

void PlayerUpdateComponent::assemble(std::shared_ptr<LevelUpdateComponent> level_update,
    [[maybe_unused]] std::shared_ptr<PlayerUpdateComponent> player_update)
{
    position_.width = PLAYER_WIDTH;
    position_.height = PLAYER_HEIGHT;
    is_paused = level_update->getIsPausedPointer();
}

void PlayerUpdateComponent::update([[maybe_unused]] float elapsed_time)
{
    handleInput();
}
