#include "level_update_component.hpp"
#include "sound_engine.hpp"
// #include "player_update_component.hpp"

#include <random>

LevelUpdateComponent::LevelUpdateComponent()
{

}

LevelUpdateComponent::~LevelUpdateComponent()
{

}

void LevelUpdateComponent::addPlatformPosition(sf::FloatRect* new_position)
{
    platform_positions_.push_back(new_position);
    ++number_of_platforms_;
}

void LevelUpdateComponent::connectToCameraTime(float* camera_time)
{
    camera_time_ = camera_time;
}

bool* LevelUpdateComponent::getIsPausedPointer()
{
    return &is_paused_;
}

int32_t LevelUpdateComponent::getRandomNumber(int32_t min_height, int32_t max_height)
{
    std::random_device rd;
    std::mt19937 gen{rd()};
    std::uniform_int_distribution<int32_t> distribution{min_height, max_height};
    int32_t random_height = distribution(gen);
    return random_height;
}

void LevelUpdateComponent::update(float time_since_last_update)
{
    if (!is_paused_) {
        if (is_game_over_) {
            is_game_over_ = false;
            *camera_time_ = 0;
            time_since_last_platform_ = 0;
            positionLevelAtStart();
        }
        *camera_time_ += time_since_last_update;
        time_since_last_platform_ += time_since_last_update;
        if (time_since_last_platform_ > platform_creation_interval_) {
            platform_positions_[next_platform_to_move_]->top =
                platform_positions_[move_relative_to_platform_]->top + getRandomNumber(-40, 40);
            if (platform_positions_[move_relative_to_platform_].top <
                platform_positions_[next_platform_to_move_]->top) {
                    platform_positions_[next_platform_to_move_]->left = 
                        platform_positions_[move_relative_to_platform_]->left +
                        platform_positions_[move_relative_to_platform_]->width +
                        getRandomNumber(20, 40);
            } else {
                platform_positions_[next_platform_to_move_]->left =
                    platform_positions_[move_relative_to_platform_]->left +
                    platform_positions_[move_relative_to_platform_]->width +
                    getRandomNumber(0, 20);
            }
            
        }
    }
}

void LevelUpdateComponent::assemble(std::shared_ptr<LevelUpdateComponent> level_update_component,
                                    std::shared_ptr<PlayerUpdateComponent> player_update_component)
{
    player_position_ = player_update_component->getPosistionPointer();
    SoundEngine::getInstance().startMusic();
}

void LevelUpdateComponent::positionLevelAtStart()
{
    float start_offset = platform_positions_[0]->left;
    for (int32_t i = 0; i < number_of_platforms_; ++i) {
        platform_positions_[i]->left = i * 100 + start_offset;
        platform_positions_[i]->top = 0;
        platform_positions_[i]->width = 100;
        platform_positions_[i]->height = 20;
    }
    player_position_->left = platform_positions_[number_of_platforms_ / 2]->left + 2;
    player_position_->top = platform_positions_[number_of_platforms_ / 2]->top - 22;
    move_relative_to_platform_ = number_of_platforms_ - 1;
    next_platform_to_move_ = 0;
}