#pragma once

#include "update_component.hpp"

class LevelUpdateComponent : public UpdateComponent
{
public:
    LevelUpdateComponent();
    ~LevelUpdateComponent();
    LevelUpdateComponent(const LevelUpdateComponent& other) = delete;
    void operator=(const LevelUpdateComponent& other) = delete;

public:
    void addPlatformPosition(sf::FloatRect* new_position);
    void connectToCameraTime(float* camera_time);
    bool* getIsPausedPointer();
    int32_t getRandomNumber(int32_t min_height, int32_t max_height);
    void update(float time_since_last_update) override;
    void assemble(std::shared_ptr<LevelUpdateComponent> level_update_component,
                    std::shared_ptr<PlayerUpdateComponent> player_update_component) override;
private:
    void positionLevelAtStart();
private:
    bool is_paused_ = true;
    std::vector<sf::FloatRect*> platform_positions_;
    float* camera_time_ = nullptr;
    sf::FloatRect* player_position_ = nullptr;
    float platform_creation_interval_ = 0;
    float time_since_last_platform_ = 0;
    int32_t next_platform_to_move_ = 0;
    int32_t number_of_platforms_ = 0;
    int32_t move_relative_to_platform_ = 0;
    bool is_game_over_ = true;
};