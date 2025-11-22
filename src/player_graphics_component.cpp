#include "player_graphics_component.hpp"
#include "player_update_component.hpp"
#include "animator.hpp"


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
    animator_ = new Animator{
        tex_coords.left, tex_coords.top,
        6,
        tex_coords.width * 6,
        tex_coords.height,
        12
    };
    section_to_draw_ = animator_->getCurrentFrame(false);
    standing_still_section_to_draw_ = animator_->getCurrentFrame(false);
    vertex_start_index_ = canvas.getVertexCount();
    canvas.resize(canvas.getVertexCount() + 4);
}

void PlayerGraphicsComponent::draw(sf::VertexArray& canvas)
{
    const sf::Vector2f& position = position_->getPosition();
    const sf::Vector2f& scale = position_->getSize();
    canvas[vertex_start_index_].position = position;
    canvas[vertex_start_index_ + 1].position = position + sf::Vector2f{scale.x, 0};
    canvas[vertex_start_index_ + 2].position = position + scale;
    canvas[vertex_start_index_ + 3].position = position + sf::Vector2f{0, scale.y};

    if (player_update_->is_right_held_down_ && !player_update_->is_in_jump_ &&
            !player_update_->is_boost_held_down_ && player_update_->is_grounded_) {
        section_to_draw_ = animator_->getCurrentFrame(false);
    }
    if (player_update_->is_left_held_down_ && !player_update_->is_in_jump_ &&
            !player_update_->is_boost_held_down_ && player_update_->is_grounded_) {
        section_to_draw_ = animator_->getCurrentFrame(true);
    } else {
        if (player_update_->is_left_held_down_) {
            is_last_facing_right_ = false;
        } else {
            is_last_facing_right_ = true;
        }
    }

    const int32_t u_pos = section_to_draw_->left;
    const int32_t v_pos = section_to_draw_->top;
    const int32_t tex_width = section_to_draw_->width;
    const int32_t tex_height = section_to_draw_->height;

    if (player_update_->is_right_held_down_ && !player_update_->is_in_jump_ &&
            !player_update_->is_boost_held_down_) {
        canvas[vertex_start_index_].texCoords.x = u_pos;
        canvas[vertex_start_index_].texCoords.y = v_pos;
        canvas[vertex_start_index_ + 1].texCoords.x = u_pos + tex_width;
        canvas[vertex_start_index_ + 1].texCoords.y = v_pos;
        canvas[vertex_start_index_ + 2].texCoords.x = u_pos + tex_width;
        canvas[vertex_start_index_ + 2].texCoords.y = v_pos + tex_height;
        canvas[vertex_start_index_ + 3].texCoords.x = u_pos;
        canvas[vertex_start_index_ + 3].texCoords.y = v_pos + tex_height;
    } else if (player_update_->is_left_held_down_ && !player_update_->is_in_jump_ &&
                !player_update_->is_boost_held_down_) {
        canvas[vertex_start_index_].texCoords.x = u_pos;
        canvas[vertex_start_index_].texCoords.y = v_pos;
        canvas[vertex_start_index_ + 1].texCoords.x = u_pos - tex_width;
        canvas[vertex_start_index_ + 1].texCoords.y = v_pos;
        canvas[vertex_start_index_ + 2].texCoords.x = u_pos - tex_width;
        canvas[vertex_start_index_ + 2].texCoords.y = v_pos + tex_height;
        canvas[vertex_start_index_ + 3].texCoords.x = u_pos;
        canvas[vertex_start_index_ + 3].texCoords.y = v_pos + tex_height;
    } else if (player_update_->is_right_held_down_ &&
                player_update_->is_boost_held_down_) {
        canvas[vertex_start_index_].texCoords.x = BOOST_TEX_LEFT;
        canvas[vertex_start_index_].texCoords.y = BOOST_TEX_TOP;
        canvas[vertex_start_index_ + 1].texCoords.x = BOOST_TEX_LEFT + BOOST_TEX_WIDTH;
        canvas[vertex_start_index_ + 1].texCoords.y = BOOST_TEX_TOP;
        canvas[vertex_start_index_ + 2].texCoords.x = BOOST_TEX_LEFT + BOOST_TEX_WIDTH;
        canvas[vertex_start_index_ + 2].texCoords.y = BOOST_TEX_TOP + BOOST_TEX_HEIGHT;
        canvas[vertex_start_index_ + 3].texCoords.x = BOOST_TEX_LEFT;
        canvas[vertex_start_index_ + 3].texCoords.y = BOOST_TEX_TOP + BOOST_TEX_HEIGHT;
    } else if (player_update_->is_left_held_down_ &&
                player_update_->is_boost_held_down_) {
        canvas[vertex_start_index_].texCoords.x = BOOST_TEX_LEFT + BOOST_TEX_WIDTH;
        canvas[vertex_start_index_].texCoords.y = 0;
        canvas[vertex_start_index_ + 1].texCoords.x = BOOST_TEX_LEFT;
        canvas[vertex_start_index_ + 1].texCoords.y = 0;
        canvas[vertex_start_index_ + 2].texCoords.x = BOOST_TEX_LEFT;
        canvas[vertex_start_index_ + 2].texCoords.y = 100;
        canvas[vertex_start_index_ + 3].texCoords.x = BOOST_TEX_LEFT + BOOST_TEX_WIDTH;
        canvas[vertex_start_index_ + 3].texCoords.y = 100;
    } else if (player_update_->is_boost_held_down_) {
        canvas[vertex_start_index_].texCoords.x = BOOST_TEX_LEFT;
        canvas[vertex_start_index_].texCoords.y = BOOST_TEX_TOP;
        canvas[vertex_start_index_ + 1].texCoords.x = BOOST_TEX_LEFT + BOOST_TEX_WIDTH;
        canvas[vertex_start_index_ + 1].texCoords.y = BOOST_TEX_TOP;
        canvas[vertex_start_index_ + 2].texCoords.x = BOOST_TEX_LEFT + BOOST_TEX_WIDTH;
        canvas[vertex_start_index_ + 2].texCoords.y = BOOST_TEX_TOP + BOOST_TEX_HEIGHT;
        canvas[vertex_start_index_ + 3].texCoords.x = BOOST_TEX_LEFT;
        canvas[vertex_start_index_ + 3].texCoords.y = BOOST_TEX_TOP + BOOST_TEX_HEIGHT;
    } else {
        if (is_last_facing_right_) {
            canvas[vertex_start_index_].texCoords.x = standing_still_section_to_draw_->left;
            canvas[vertex_start_index_].texCoords.y = standing_still_section_to_draw_->top;
            canvas[vertex_start_index_ + 1].texCoords.x = standing_still_section_to_draw_->left + tex_width;
            canvas[vertex_start_index_ + 1].texCoords.y = standing_still_section_to_draw_->top;
            canvas[vertex_start_index_ + 2].texCoords.x = standing_still_section_to_draw_->left + tex_width;
            canvas[vertex_start_index_ + 2].texCoords.y = standing_still_section_to_draw_->top + tex_height;
            canvas[vertex_start_index_ + 3].texCoords.x = standing_still_section_to_draw_->left;
            canvas[vertex_start_index_ + 3].texCoords.y = standing_still_section_to_draw_->top + tex_height;
        } else {
            canvas[vertex_start_index_].texCoords.x = standing_still_section_to_draw_->left + tex_width;
            canvas[vertex_start_index_].texCoords.y = standing_still_section_to_draw_->top;
            canvas[vertex_start_index_ + 1].texCoords.x = standing_still_section_to_draw_->left;
            canvas[vertex_start_index_ + 1].texCoords.y = standing_still_section_to_draw_->top;
            canvas[vertex_start_index_ + 2].texCoords.x = standing_still_section_to_draw_->left;
            canvas[vertex_start_index_ + 2].texCoords.y = standing_still_section_to_draw_->top + tex_height;
            canvas[vertex_start_index_ + 3].texCoords.x = standing_still_section_to_draw_->left + tex_width;
            canvas[vertex_start_index_ + 3].texCoords.y = standing_still_section_to_draw_->top + tex_height; 
        }
    }
}