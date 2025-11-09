#pragma once

#include "update_component.hpp"
#include "input_receiver.hpp"

#include <SFML/Graphics.hpp>

#include <memory>

class CameraUpdateComponent : public UpdateComponent
{
public:
    CameraUpdateComponent();
    ~CameraUpdateComponent();
    CameraUpdateComponent(const CameraUpdateComponent& other) = delete;
    void operator=(const CameraUpdateComponent& other) = delete;

public:
    sf::FloatRect* getPositionPointer();
    void handleInput();
    InputReceiver* getInputReceiver();
    void assemble(std::shared_ptr<LevelUpdateComponent> level_update_component,
                    std::shared_ptr<PlayerUpdateComponent> player_update_component) override;
    void update(float time_since_last_update) override;

private:
    sf::FloatRect position_;
    sf::FloatRect* player_position_;
    bool is_receives_input_ = false;
    InputReceiver* input_receiver_ = nullptr;
};