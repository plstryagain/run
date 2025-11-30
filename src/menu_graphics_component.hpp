#pragma once

#include "graphics_component.hpp"

#include <SFML/Graphics.hpp>
#include <memory>

class MenuGraphicsComponent : public GraphicsComponent
{
public:
    MenuGraphicsComponent();
    ~MenuGraphicsComponent();
    MenuGraphicsComponent(const MenuGraphicsComponent& other) = delete;
    void operator=(const MenuGraphicsComponent& other) = delete;

public:
    void draw(sf::VertexArray& canvas) override;
    void assemble(sf::VertexArray& canvas, std::shared_ptr<UpdateComponent> generic_update,
        sf::IntRect tex_coords) override;

private:
    sf::FloatRect* menu_position_ = nullptr;
    int32_t vertex_start_index;
    bool* is_game_over_;
    bool current_status_;

    int32_t u_pos_;
    int32_t v_pos_;
    int32_t tex_width_;
    int32_t tex_height_;
};