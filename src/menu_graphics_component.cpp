#include "menu_graphics_component.hpp"
#include "menu_update_component.hpp"

MenuGraphicsComponent::MenuGraphicsComponent()
{

}

MenuGraphicsComponent::~MenuGraphicsComponent()
{

}

void MenuGraphicsComponent::draw(sf::VertexArray& canvas)
{
    if (*is_game_over_ && !current_status_) {
        current_status_ = *is_game_over_;
        canvas[vertex_start_index].texCoords.x = u_pos_;
        canvas[vertex_start_index].texCoords.y = v_pos_ + tex_height_;
        canvas[vertex_start_index + 1].texCoords.x = u_pos_ + tex_width_;
        canvas[vertex_start_index + 1].texCoords.y = v_pos_ + tex_height_;
        canvas[vertex_start_index + 2].texCoords.x = u_pos_ + tex_width_;
        canvas[vertex_start_index + 2].texCoords.y = v_pos_ + tex_height_ + tex_height_;
        canvas[vertex_start_index + 3].texCoords.x = u_pos_;
        canvas[vertex_start_index + 3].texCoords.y = v_pos_ + tex_height_ + tex_height_;
    } else if (!*is_game_over_ && current_status_) {
        current_status_ = *is_game_over_;
        canvas[vertex_start_index].texCoords.x = u_pos_;
        canvas[vertex_start_index].texCoords.y = v_pos_;
        canvas[vertex_start_index + 1].texCoords.x = u_pos_ + tex_width_;
        canvas[vertex_start_index + 1].texCoords.y = v_pos_;
        canvas[vertex_start_index + 2].texCoords.x = u_pos_ + tex_width_;
        canvas[vertex_start_index + 2].texCoords.y = v_pos_ + tex_height_;
        canvas[vertex_start_index + 3].texCoords.x = u_pos_;
        canvas[vertex_start_index + 3].texCoords.y = v_pos_ + tex_height_;
    }
    const sf::Vector2f& position = menu_position_->getPosition();
    canvas[vertex_start_index].position = position;
    canvas[vertex_start_index + 1].position = position + sf::Vector2f{menu_position_->getSize().x, 0};
    canvas[vertex_start_index + 2].position = position + menu_position_->getSize();
    canvas[vertex_start_index + 3].position = position + sf::Vector2f{0, menu_position_->getSize().y};

}

void MenuGraphicsComponent::assemble(sf::VertexArray& canvas, std::shared_ptr<UpdateComponent> generic_update,
    sf::IntRect tex_coords)
{
    menu_position_ = std::static_pointer_cast<MenuUpdateComponent>(generic_update)->getPositionPointer();
    is_game_over_ = std::static_pointer_cast<MenuUpdateComponent>(generic_update)->getGameOverPointer();
    current_status_ = *is_game_over_;

    vertex_start_index = canvas.getVertexCount();
    canvas.resize(canvas.getVertexCount() + 4);

    u_pos_ = tex_coords.left;
    v_pos_ = tex_coords.top;
    tex_width_ = tex_coords.width;
    tex_height_ = tex_coords.height;

    canvas[vertex_start_index].texCoords.x = u_pos_;
    canvas[vertex_start_index].texCoords.y = v_pos_ + tex_height_;
    canvas[vertex_start_index + 1].texCoords.x = u_pos_ + tex_width_;
    canvas[vertex_start_index + 1].texCoords.y = v_pos_ + tex_height_;
    canvas[vertex_start_index + 2].texCoords.x = u_pos_ + tex_width_;
    canvas[vertex_start_index + 2].texCoords.y = v_pos_ + tex_height_ + tex_height_;
    canvas[vertex_start_index + 3].texCoords.x = u_pos_;
    canvas[vertex_start_index + 3].texCoords.y = v_pos_ + tex_height_ + tex_height_;
}