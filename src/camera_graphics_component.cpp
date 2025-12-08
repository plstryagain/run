#include "camera_graphics_component.hpp"
#include "camera_update_component.hpp"

#include <iostream>

CameraGraphicsComponent::CameraGraphicsComponent(sf::RenderWindow* window, sf::Texture* texture,
    sf::Vector2f view_size, sf::FloatRect view_port)
{
    window_ = window;
    texture_ = texture;
    view_.setSize(view_size);
    view_.setViewport(view_port);
    if (view_port.width < 1) {
        is_mini_map_ = true;
    } else {
        font_.loadFromFile("assets/fonts/KOMIKAP_.ttf");
        text_.setFont(font_);
        text_.setFillColor(sf::Color{255, 0, 0, 255});
        text_.setScale(0.2f, 0.2f);
    }
    background_texture_.loadFromFile("assets/graphics/backgroundTexture.png");
    background_sprite_.setTexture(background_texture_);
    background_sprite2_.setTexture(background_texture_);

    background_sprite_.setPosition(0, -200);

    shader_.loadFromFile("assets/shaders/glslsandbox109644", sf::Shader::Fragment);
    if (!shader_.isAvailable()) {
        std::cout << "The shader is not available" <<std::endl;
    }
    shader_.setUniform("resolution", sf::Vector2f(2500, 2500));
    shader_clock_.restart();
}

CameraGraphicsComponent::~CameraGraphicsComponent()
{

}


float* CameraGraphicsComponent::getTimeConnection()
{
    return &time_;
}

void CameraGraphicsComponent::assemble(sf::VertexArray& canvas, std::shared_ptr<UpdateComponent> generic_update, 
    sf::IntRect text_coords)
{
    std::shared_ptr<CameraUpdateComponent> camera_update = 
        std::static_pointer_cast<CameraUpdateComponent>(generic_update);
    position_ = camera_update->getPositionPointer();
    vertex_start_index_ = canvas.getVertexCount();
    canvas.resize(canvas.getVertexCount() + 4);
    const int32_t upos = text_coords.left;
    const int32_t vpos = text_coords.top;
    const int32_t tex_width = text_coords.width;
    const int32_t tex_height = text_coords.height;
    canvas[vertex_start_index_].texCoords.x = upos;
    canvas[vertex_start_index_].texCoords.y = vpos;
    canvas[vertex_start_index_ + 1].texCoords.x = upos + tex_width;
    canvas[vertex_start_index_ + 1].texCoords.y = vpos;
    canvas[vertex_start_index_ + 2].texCoords.x = upos + tex_width;
    canvas[vertex_start_index_ + 2].texCoords.y = vpos + tex_height;
    canvas[vertex_start_index_ + 3].texCoords.x = upos;
    canvas[vertex_start_index_ + 3].texCoords.y = vpos + tex_height;
}

void CameraGraphicsComponent::draw(sf::VertexArray& canvas)
{
    view_.setCenter(position_->getPosition());
    sf::Vector2f start_position;
    start_position.x = view_.getCenter().x - view_.getSize().x / 2;
    start_position.y = view_.getCenter().y - view_.getSize().y / 2;

    sf::Vector2f scale;
    scale.x = view_.getSize().x;
    scale.y = view_.getSize().y;

    canvas[vertex_start_index_].position = start_position;
    canvas[vertex_start_index_ + 1].position = start_position + sf::Vector2f{scale.x, 0};
    canvas[vertex_start_index_ + 2].position = start_position + scale;
    canvas[vertex_start_index_ + 3].position = start_position + sf::Vector2f{0, scale.y};
    if (is_mini_map_) {
        if (view_.getSize().x < MAX_WIDTH && position_->width > 1) {
            view_.zoom(position_->width);
        } else if (view_.getSize().x > MIN_WIDTH && position_->width < 1) {
            view_.zoom(position_->width);
        }
    }
    window_->setView(view_);
    sf::Vector2f movement;
    movement.x = position_->left - players_previous_position_.x;
    movement.y = position_->top - players_previous_position_.y;
    if (is_background_are_flipped_) {
        background_sprite2_.setPosition(
            background_sprite2_.getPosition().x + movement.x / 6,
            background_sprite2_.getPosition().y + movement.y / 6
        );
        background_sprite_.setPosition(
            background_sprite2_.getPosition().x + background_sprite2_.getTextureRect().getSize().x,
            background_sprite2_.getPosition().y);
        if (position_->left > 
            background_sprite_.getPosition().x + (background_sprite_.getTextureRect().getSize().x / 2)) {
            is_background_are_flipped_ = !is_background_are_flipped_;
            background_sprite2_.setPosition(background_sprite_.getPosition());
        }
    } else {
        background_sprite_.setPosition(
            background_sprite_.getPosition().x - movement.x / 6,
            background_sprite_.getPosition().y + movement.y / 6);
        background_sprite2_.setPosition(
            background_sprite_.getPosition().x + background_sprite_.getTextureRect().getSize().x,
            background_sprite_.getPosition().y);
        if (position_->left >
            background_sprite2_.getPosition().x + (background_sprite2_.getTextureRect().getSize().x / 2)) {
            is_background_are_flipped_ = !is_background_are_flipped_;
            background_sprite_.setPosition(
                background_sprite2_.getPosition());
        }
    }
    players_previous_position_.x = position_->left;
    players_previous_position_.y = position_->top;

    shader_.setUniform("time", shader_clock_.getElapsedTime().asSeconds());
    sf::Vector2i mouse_pos = window_->mapCoordsToPixel(position_->getPosition());
    shader_.setUniform("mouse", sf::Vector2f{static_cast<float>(mouse_pos.x), static_cast<float>(mouse_pos.y + 1000)});
    if (shader_clock_.getElapsedTime().asSeconds() > 10) {
        shader_clock_.restart();
        is_show_shader_ = !is_show_shader_;
    }
    // if (!is_show_shader_) {
    //     window_->draw(background_sprite_, &shader_);
    //     window_->draw(background_sprite2_, &shader_);
    // } else {
        window_->draw(background_sprite_);
        window_->draw(background_sprite2_);
    // }
    if (!is_mini_map_) {
        text_.setString(std::to_string(time_));
        text_.setPosition(window_->mapPixelToCoords(sf::Vector2i{5, 5}));
        window_->draw(text_);
    }
    window_->draw(canvas, texture_);
}
