#pragma once

#include "component.hpp"

#include <SFML/Graphics.hpp>
#include <memory>

class UpdateComponent;

class GraphicsComponent : public Component
{
public:
    GraphicsComponent();
    virtual ~GraphicsComponent();

public:
    virtual void assemble(sf::VertexArray& canvas, std::shared_ptr<UpdateComponent> generic_update, sf::IntRect tex_coords) = 0;
    virtual void draw(sf::VertexArray& canvas) = 0;
};