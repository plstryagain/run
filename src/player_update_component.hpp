#pragma once

#include "update_component.hpp"
#include "input_receiver.hpp"

#include <SFML/Graphics.hpp>
#include <memory>

class PlayerUpdateComponent : public UpdateComponent
{
public:
    PlayerUpdateComponent();
    ~PlayerUpdateComponent();
    PlayerUpdateComponent(const PlayerUpdateComponent& other) = delete;
    void operator=(const PlayerUpdateComponent& other) = delete;

public:
    sf::FloatRect* getPositionPointer();
    bool* getGroundedPointer();
    void handleInput();
    InputReceiver* getInputReceiver();

    void assemble(
        std::shared_ptr<LevelUpdateComponent> level_update,
        [[maybe_unused]] std::shared_ptr<PlayerUpdateComponent> player_update)
        override;
    
    void update([[maybe_unused]] float elapsed_time) override;

public:
    bool is_right_held_down_ = false;
    bool is_left_held_down_ = false;
    bool is_boost_held_down_ = false;
    bool is_grounded_;
    bool is_in_jump_ = false;

private:
    inline static constexpr float PLAYER_WIDTH = 20.f;
    inline static constexpr float PLAYER_HEIGHT = 16.f;
    sf::FloatRect position_;
    bool* is_paused_ = nullptr;
    float gravity_ = 165;
    float run_speed_ = 150;
    float boost_speed_ = 250;
    InputReceiver input_receiver_;

    sf::Clock jump_clock_;
    bool is_space_held_down_ = false;
    float jump_duration_ = .50;
    float jump_speed_ = 400;
};