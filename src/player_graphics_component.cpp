#include "player_graphics_component.hpp"
#include "player_update_component.hpp"


PlayerGraphicsComponent::PlayerGraphicsComponent()
    : section_to_draw_{new sf::IntRect}, standing_still_section_to_draw_{new sf::IntRect}
{

}

PlayerGraphicsComponent::~PlayerGraphicsComponent()
{

}

void PlayerGraphicsComponent::assemble(sf::VertexArray& canvas,
        std::shared_ptr<UpdateComponent> generic_update,
        sf::IntRect tex_coords)
{
    player_update_ = std::static_pointer_cast<PlayerUpdateComponent>(generic_update);
    position_ = player_update_->getPositionPointer();
    vertex_start_index_ = canvas.getVertexCount();
    canvas.resize(canvas.getVertexCount() + 4);
    canvas[vertex_start_index_].texCoords.x = tex_coords.left;
    canvas[vertex_start_index_].texCoords.y = tex_coords.top;
    canvas[vertex_start_index_ + 1].texCoords.x = tex_coords.left + tex_coords.width;
    canvas[vertex_start_index_ + 1].texCoords.y = tex_coords.top;
    canvas[vertex_start_index_ + 2].texCoords.x = tex_coords.left + tex_coords.width;
    canvas[vertex_start_index_ + 2].texCoords.y = tex_coords.top + tex_coords.height;
    canvas[vertex_start_index_ + 3].texCoords.x = tex_coords.left;
    canvas[vertex_start_index_ + 3].texCoords.y = tex_coords.top + tex_coords.height;
}

void PlayerGraphicsComponent::draw(sf::VertexArray& canvas)
{
    const sf::Vector2f& position = position_->getPosition();
    const sf::Vector2f& scale = position_->getSize();
    canvas[vertex_start_index_].position = position;
    canvas[vertex_start_index_ + 1].position = position + sf::Vector2f{scale.x, 0};
    canvas[vertex_start_index_ + 2].position = position + scale;
    canvas[vertex_start_index_ + 3].position = position + sf::Vector2f{0, scale.y};
}