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
    for (const sf::Event& event : input_receiver_.getEvents()) {
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::D) {
                is_right_held_down_ = true;
            }
            if (event.key.code == sf::Keyboard::A) {
                is_left_held_down_ = true;
            }
            if (event.key.code == sf::Keyboard::W) {
                is_boost_held_down_ = true;
            }
            if (event.key.code == sf::Keyboard::Space) {
                is_space_held_down_ = true;
            }
        }
        if (event.type == sf::Event::KeyReleased) {
            if (event.key.code == sf::Keyboard::D) {
                is_right_held_down_ = false;
            }
            if (event.key.code == sf::Keyboard::A) {
                is_left_held_down_ = false;
            }
            if (event.key.code == sf::Keyboard::W) {
                is_boost_held_down_ = false;
            }
            if (event.key.code == sf::Keyboard::Space) {
                is_space_held_down_ = false;
            }
        }
    }
    input_receiver_.clearEvents();
}

void PlayerUpdateComponent::assemble(std::shared_ptr<LevelUpdateComponent> level_update,
    [[maybe_unused]] std::shared_ptr<PlayerUpdateComponent> player_update)
{
    position_.width = PLAYER_WIDTH;
    position_.height = PLAYER_HEIGHT;
    is_paused_ = level_update->getIsPausedPointer();
}

void PlayerUpdateComponent::update([[maybe_unused]] float elapsed_time)
{
    if (!(*is_paused_)) {
        position_.top += gravity_ * elapsed_time;
        handleInput();

        if (is_grounded_) {
            if (is_right_held_down_) {
                position_.left += elapsed_time * run_speed_;
            }
            if (is_left_held_down_) {
                position_.left -= elapsed_time * run_speed_;
            }
        }

        if (is_boost_held_down_) {
            position_.top -= elapsed_time * boost_speed_;
            if (is_right_held_down_) {
                position_.left += elapsed_time * run_speed_ / 4;
            }
            if (is_left_held_down_) {
                position_.left -= elapsed_time * run_speed_ / 4;
            }
        }

        if (is_space_held_down_ && !is_in_jump_ && is_grounded_) {
            SoundEngine::getInstance().playJump();
            is_in_jump_ = true;
            jump_clock_.restart();
        }

        if (is_space_held_down_) {
            //is_in_jump_ = false;
        }

        if (is_in_jump_) {
            if (jump_clock_.getElapsedTime().asSeconds() < jump_duration_ / 2) {
                position_.top -= jump_speed_ * elapsed_time;
            } else {
                position_.top += jump_speed_ * elapsed_time;
            }
            if (jump_clock_.getElapsedTime().asSeconds() > jump_duration_) {
                is_in_jump_ = false;
            }
            if (is_right_held_down_) {
                position_.left += elapsed_time * run_speed_;
            }
            if (is_left_held_down_) {
                position_.left -= elapsed_time * run_speed_;
            }
        }
        is_grounded_ = false;
    }
}
