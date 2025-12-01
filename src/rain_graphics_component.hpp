#pragma once

#include "graphics_component.hpp"

#include <SFML/Graphics.hpp>
#include <memory>

class Animator;

class RainGraphicsComponent : public GraphicsComponent
{
public:
    RainGraphicsComponent(sf::FloatRect* player_position, float horizontal_offset,
        float vertical_offset, int32_t rain_coverage_per_object);
    ~RainGraphicsComponent();
    RainGraphicsComponent(const RainGraphicsComponent& other) = delete;
    void operator=(const RainGraphicsComponent& other) = delete;

public:
    void draw(sf::VertexArray& canvas) override;
    void assemble(sf::VertexArray& canvas, std::shared_ptr<UpdateComponent> generic_update,
        sf::IntRect tex_coords) override;

private:
    sf::FloatRect* player_position_;
    int32_t vertex_start_index_;
    sf::Vector2f scale_;
    float horizontal_offset_;
    float vertical_offset_;
    Animator* animator_;
    sf::IntRect* section_to_draw_;
};