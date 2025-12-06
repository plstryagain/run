#pragma once

#include "graphics_component.hpp"

#include <SFML/Graphics.hpp>
#include <memory>

class Animator;
class PlayerUpdate;

class FireballGraphicsComponent : public GraphicsComponent
{
public:
    FireballGraphicsComponent();
    ~FireballGraphicsComponent();
    FireballGraphicsComponent(const FireballGraphicsComponent& other) = delete;
    void operator=(const FireballGraphicsComponent& other) = delete;

public:
    void draw(sf::VertexArray& canvas) override;
    void assemble(sf::VertexArray& canvas,
        std::shared_ptr<UpdateComponent> generic_update,
        sf::IntRect tex_coords) override;

private:
    sf::FloatRect* position_;
    int32_t vertex_start_index_;
    bool* facing_right_ = nullptr;
    Animator* animator_;
    sf::IntRect* section_to_draw_;
    std::shared_ptr<PlayerUpdate> player_update_;
};