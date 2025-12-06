#pragma once

#include "update_component.hpp"

#include <SFML/Graphics.hpp>
#include <memory>

class FireballUpdateComponent : public UpdateComponent
{
public:
    FireballUpdateComponent(bool* paused_pointer);
    ~FireballUpdateComponent();
    FireballUpdateComponent(const FireballUpdateComponent& other) = delete;
    void operator=(const FireballUpdateComponent& other) = delete;

public:
    bool* getFacingRightPointer();
    sf::FloatRect* getPositionPointer();
    int32_t getRandomNumber(int32_t min_height, int32_t max_height);
    void update(float elapsed_time) override;
    void assemble(std::shared_ptr<LevelUpdateComponent> level_update,
        std::shared_ptr<PlayerUpdateComponent> player_update) override;

private:
    sf::FloatRect position_;
    sf::FloatRect* player_position_ = nullptr;
    bool* game_is_paused_ = nullptr;
    float speed_ = 250;
    float range_ = 900;
    int32_t max_spawn_distance_from_player_ = 250;
    bool movement_paused_ = true;
    sf::Clock pause_clock_;
    float pause_duration_target_ = 0;
    float max_pause_ = 6;
    float min_pause_ = 1;
    // float time_paused_ = 0;
    bool left_to_right_ = true;
};