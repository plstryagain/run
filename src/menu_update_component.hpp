#pragma once

#include "update_component.hpp"
#include "input_receiver.hpp"

#include <SFML/Graphics.hpp>

#include <memory>

class MenuUpdateComponent : public UpdateComponent
{
public:
    MenuUpdateComponent(sf::RenderWindow* window);
    ~MenuUpdateComponent();
    MenuUpdateComponent(const MenuUpdateComponent& other) = delete;
    void operator=(const MenuUpdateComponent& other) = delete;

public:
    void handleInput();
    sf::FloatRect* getPositionPointer();
    bool* getGameOverPointer();
    InputReceiver* getInputReceiver();

    void update(float elapsed_time) override;
    void assemble(std::shared_ptr<LevelUpdateComponent> level_update_component,
                    std::shared_ptr<PlayerUpdateComponent> player_update_component) override;

private:
    sf::FloatRect position_;
    InputReceiver input_receiver_;
    sf::FloatRect* player_position = nullptr;
    bool is_visible_ = false;
    bool* is_paused_ = nullptr;
    bool is_game_over_;
    sf::RenderWindow* window_;
};