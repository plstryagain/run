#include "platform_graphics_component.hpp"
#include "platform_update_component.hpp"

PlatformGraphicsComponent::PlatformGraphicsComponent()
{

}

PlatformGraphicsComponent::~PlatformGraphicsComponent()
{

}

void PlatformGraphicsComponent::draw(sf::VertexArray& canvas)
{
    const sf::Vector2f& position = position_->getPosition();
    const sf::Vector2f& scale = position_->getSize();
    canvas[vertex_start_index_].position = position;
    canvas[vertex_start_index_ + 1].position = position + sf::Vector2f{scale.x, 0}; 
    canvas[vertex_start_index_ + 2].position = position + scale; 
    canvas[vertex_start_index_ + 3].position = position + sf::Vector2f{0, scale.y}; 
}

void PlatformGraphicsComponent::assemble(sf::VertexArray& canvas,
                std::shared_ptr<UpdateComponent> generic_update,
                sf::IntRect tex_coords)
{
    std::shared_ptr<PlatformUpdateComponent> platform_update_component = 
        std::static_pointer_cast<PlatformUpdateComponent>(generic_update);
    position_ = platform_update_component->getPositionPointer();
    vertex_start_index_ = canvas.getVertexCount();
    canvas.resize(canvas.getVertexCount() + 4);
    const int32_t u_pos = tex_coords.left;
    const int32_t v_pos = tex_coords.top;
    const int32_t tex_width = tex_coords.width;
    const int32_t tex_height = tex_coords.height;
    
    canvas[vertex_start_index_].texCoords.x = u_pos;
    canvas[vertex_start_index_].texCoords.y = v_pos;
    canvas[vertex_start_index_ + 1].texCoords.x = u_pos + tex_width;
    canvas[vertex_start_index_ + 1].texCoords.y = v_pos;
    canvas[vertex_start_index_ + 2].texCoords.x = u_pos + tex_width;
    canvas[vertex_start_index_ + 2].texCoords.y = v_pos + tex_height;
    canvas[vertex_start_index_ + 3].texCoords.x = u_pos;
    canvas[vertex_start_index_ + 3].texCoords.y = v_pos + tex_height;

}