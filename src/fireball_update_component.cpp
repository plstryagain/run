#include "fireball_update_component.hpp"
#include "sound_engine.hpp"
#include "player_update_component.hpp"

#include <random>

FireballUpdateComponent::FireballUpdateComponent(bool* paused_pointer)
{
    game_is_paused_ = paused_pointer;
    pause_duration_target_ = getRandomNumber(min_pause_, max_pause_);
}

FireballUpdateComponent::~FireballUpdateComponent()
{

}

bool* FireballUpdateComponent::getFacingRightPointer()
{
    return &left_to_right_;
}

sf::FloatRect* FireballUpdateComponent::getPositionPointer()
{
    return &position_;
}

int32_t FireballUpdateComponent::getRandomNumber(int32_t min_height, int32_t max_height)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int32_t> distribution{min_height, max_height};
    return distribution(gen);
}

void FireballUpdateComponent::update(float elapsed_time)
{
    if (!*game_is_paused_) {
        if (!movement_paused_) {
            if (left_to_right_) {
                position_.left += speed_ * elapsed_time;
                if (position_.left - player_position_->left > range_) {
                    movement_paused_ = true;
                    pause_clock_.restart();
                    left_to_right_ = !left_to_right_;
                    position_.top = getRandomNumber(player_position_->top - max_spawn_distance_from_player_,
                        player_position_->top + max_spawn_distance_from_player_);
                    pause_duration_target_ = getRandomNumber(min_pause_, max_pause_);
                }
            } else {
                position_.left -= speed_ * elapsed_time;
                if (player_position_->left - position_.left > range_) {
                    movement_paused_ = true;
                    pause_clock_.restart();
                    left_to_right_ = !left_to_right_;
                    position_.top = getRandomNumber(player_position_->top - max_spawn_distance_from_player_, 
                        player_position_->top + max_spawn_distance_from_player_);
                    pause_duration_target_ = getRandomNumber(min_pause_, max_pause_);
                }
            }
            if (player_position_->intersects(position_)) {
                player_position_->top = player_position_->top + player_position_->height * 2;
            }
        } else {
            if (pause_clock_.getElapsedTime().asSeconds() > pause_duration_target_) {
                movement_paused_ = false;
                SoundEngine::getInstance().playFireballLaunch(player_position_->getPosition(), 
                    position_.getPosition());
            }
        }
    }
}

void FireballUpdateComponent::assemble(std::shared_ptr<LevelUpdateComponent> level_update,
    std::shared_ptr<PlayerUpdateComponent> player_update)
{
    player_position_ = player_update->getPositionPointer();
    position_.top = getRandomNumber(player_position_->top - max_spawn_distance_from_player_, 
        player_position_->top + max_spawn_distance_from_player_);
    position_.left = player_position_->left - getRandomNumber(200, 400);
    position_.width = 10;
    position_.height = 10;
}