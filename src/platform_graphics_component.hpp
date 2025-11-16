#pragma once

#include "graphics_component.hpp"

#include <SFML/Graphics.hpp>

class PlatformGraphicsComponent : public GraphicsComponent
{
public:
    PlatformGraphicsComponent();
    ~PlatformGraphicsComponent();
    PlatformGraphicsComponent(const PlatformGraphicsComponent& other) = delete;
    void operator=(const PlatformGraphicsComponent& other) = delete;

public:
    void draw(sf::VertexArray& canvas) override;
    void assemble(sf::VertexArray& canvas,
                    std::shared_ptr<UpdateComponent> generic_update,
                    sf::IntRect tex_coords) override;
private:
    sf::FloatRect* position_ = nullptr;
    int32_t vertex_start_index_ = -1;
};