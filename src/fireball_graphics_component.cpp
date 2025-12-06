#include "fireball_graphics_component.hpp"
#include "fireball_update_component.hpp"
#include "animator.hpp"

FireballGraphicsComponent::FireballGraphicsComponent()
{

}

FireballGraphicsComponent::~FireballGraphicsComponent()
{
    delete animator_;
}

void FireballGraphicsComponent::draw(sf::VertexArray& canvas)
{
    const sf::Vector2f& position = position_->getPosition();
    const sf::Vector2f& scale = position_->getSize();

    canvas[vertex_start_index_].position = position;
    canvas[vertex_start_index_ + 1].position = position + sf::Vector2f{scale.x, 0};
    canvas[vertex_start_index_ + 2].position = position + scale;
    canvas[vertex_start_index_ + 3].position = position + sf::Vector2f{0, scale.y};

    if (*facing_right_) {
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
    } else {
        section_to_draw_ = animator_->getCurrentFrame(true);

        const int32_t u_pos = section_to_draw_->left;
        const int32_t v_pos = section_to_draw_->top;
        const int32_t tex_width = section_to_draw_->width;
        const int32_t tex_height = section_to_draw_->height;

        canvas[vertex_start_index_].texCoords.x = u_pos;
        canvas[vertex_start_index_].texCoords.y = v_pos;
        canvas[vertex_start_index_ + 1].texCoords.x = u_pos - tex_width;
        canvas[vertex_start_index_ + 1].texCoords.y = v_pos;
        canvas[vertex_start_index_ + 2].texCoords.x = u_pos - tex_width;
        canvas[vertex_start_index_ + 2].texCoords.y = v_pos + tex_height;
        canvas[vertex_start_index_ + 3].texCoords.x = u_pos;
        canvas[vertex_start_index_ + 3].texCoords.y = v_pos + tex_height; 
    }
}

void FireballGraphicsComponent::assemble(sf::VertexArray& canvas,
    std::shared_ptr<UpdateComponent> generic_update, sf::IntRect tex_coords)
{
    auto fu = std::static_pointer_cast<FireballUpdateComponent>(generic_update);
    position_ = fu->getPositionPointer();
    facing_right_ = fu->getFacingRightPointer();

    animator_ = new Animator{
        tex_coords.left, tex_coords.top, 3,
        tex_coords.width, tex_coords.height, 6
    };
    section_to_draw_ = animator_->getCurrentFrame(false);

    vertex_start_index_ = canvas.getVertexCount();
    canvas.resize(vertex_start_index_ + 4);
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