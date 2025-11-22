#pragma once

#include "graphics_component.hpp"

#include <memory>

class Animator;

class PlayerUpdateComponent;

class PlayerGraphicsComponent : public GraphicsComponent
{
public:
    PlayerGraphicsComponent();
    ~PlayerGraphicsComponent();
    PlayerGraphicsComponent(const PlayerGraphicsComponent& other) = delete;
    void operator=(const PlayerGraphicsComponent& other) = delete;

public:
    void assemble(sf::VertexArray& canvas,
        std::shared_ptr<UpdateComponent> generic_update,
        sf::IntRect tex_coords) override;
    void draw(sf::VertexArray& canvas) override;

private:
    sf::FloatRect* position_ = nullptr;
    int32_t vertex_start_index_ = -999;
    Animator* animator_;
    sf::IntRect* section_to_draw_;
    sf::IntRect* standing_still_section_to_draw_;
    std::shared_ptr<PlayerUpdateComponent> player_update_;
    inline static constexpr int32_t BOOST_TEX_LEFT = 536;
    inline static constexpr int32_t BOOST_TEX_TOP = 0;
    inline static constexpr int32_t BOOST_TEX_WIDTH = 69;
    inline static constexpr int32_t BOOST_TEX_HEIGHT = 100;
    bool is_last_facing_right_ = true;
};