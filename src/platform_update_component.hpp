#pragma once

#include "update_component.hpp"

#include <SFML/Graphics.hpp>

class PlatformUpdateComponent : public UpdateComponent
{
public:
    PlatformUpdateComponent();
    ~PlatformUpdateComponent();
    PlatformUpdateComponent(const PlatformUpdateComponent& other) = delete;
    void operator=(const PlatformUpdateComponent& other) = delete;

public:
    sf::FloatRect* getPositionPointer();
    void update(float elapsed_time) override;
    void assemble(std::shared_ptr<LevelUpdateComponent> level_update_component,
                    std::shared_ptr<PlayerUpdateComponent> player_update_component) override;
private:
    sf::FloatRect position_;
    sf::FloatRect* player_position_ = nullptr;
    bool* is_player_grounded_ = nullptr;
};