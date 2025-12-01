#include "rain_graphics_component.hpp"
#include "animator.hpp"

RainGraphicsComponent::RainGraphicsComponent(sf::FloatRect* player_position, float horizontal_offset,
    float vertical_offset, int32_t rain_coverage_per_object)
    : player_position_{player_position}, horizontal_offset_{horizontal_offset}, vertical_offset_{vertical_offset}, 
        scale_{static_cast<float>(rain_coverage_per_object), static_cast<float>(rain_coverage_per_object)}
{

}

RainGraphicsComponent::~RainGraphicsComponent()
{
    delete animator_;
}

void RainGraphicsComponent::draw(sf::VertexArray& canvas)
{
    const sf::Vector2f& position = player_position_->getPosition() - 
        sf::Vector2f{scale_.x / 2 + horizontal_offset_, scale_.y / 2 + vertical_offset_};
    canvas[vertex_start_index_].position = position;
    canvas[vertex_start_index_ + 1].position = position + sf::Vector2f{scale_.x, 0};
    canvas[vertex_start_index_ + 2].position = position + scale_;
    canvas[vertex_start_index_ + 3].position = position + sf::Vector2f{0, scale_.y};
    section_to_draw_ = animator_->getCurrentFrame(false);
    const int32_t u_pos = section_to_draw_->left;
    const int32_t v_pos = section_to_draw_->top;
    const int32_t tex_width = section_to_draw_->width;
    const int32_t tex_height = section_to_draw_->height;

    canvas[vertex_start_index_].texCoords.x = u_pos;
    canvas[vertex_start_index_].texCoords.y = v_pos;
    canvas[vertex_start_index_ + 1].texCoords.x = u_pos + tex_width;
    canvas[vertex_start_index_ + 1].texCoords.y = v_pos;
    canvas[vertex_start_index_ + 2].texCoords.x = u_pos + tex_width;
    canvas[vertex_start_index_ + 2].texCoords.y = v_pos + tex_height;
    canvas[vertex_start_index_ + 3].texCoords.x = u_pos;
    canvas[vertex_start_index_ + 3].texCoords.y = v_pos + tex_height;
}

void RainGraphicsComponent::assemble(sf::VertexArray& canvas, std::shared_ptr<UpdateComponent> generic_update,
    sf::IntRect tex_coords)
{
    animator_ = new Animator{
        tex_coords.left, tex_coords.top, 4,
        tex_coords.width * 4, tex_coords.height, 8
    };
    vertex_start_index_ = canvas.getVertexCount();
    canvas.resize(vertex_start_index_ + 4);
}