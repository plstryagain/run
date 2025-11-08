#pragma once

#include "graphics_component.hpp"

#include <SFML/Graphics.hpp>

class CameraGraphicsComponent : public GraphicsComponent
{
public:
    CameraGraphicsComponent(sf::RenderWindow* window, sf::Texture* texture,
                            sf::Vector2f view_size, sf::FloatRect view_port);
    ~CameraGraphicsComponent();
    CameraGraphicsComponent(const CameraGraphicsComponent& other) = delete;
    void operator=(const CameraGraphicsComponent& other) = delete;

public:
    float* getTimeConnection();
    void assemble(sf::VertexArray& canvas,
                    std::shared_ptr<UpdateComponent> generic_update,
                    sf::IntRect text_coords) override;
    void draw(sf::VertexArray& canvas) override;
    
private:
    sf::RenderWindow* window_;
    sf::View view_;
    int32_t vertex_start_index_ = -999;
    sf::Texture* texture_ = nullptr;
    sf::FloatRect* position_ = nullptr;
    bool is_mini_map_ = false;
    inline static constexpr float MIN_WIDTH = 640.0f;
    inline static constexpr float MAX_WIDTH = 2000.0f;
    sf::Text text_;
    sf::Font font_;
    int32_t time_at_end_of_game_ = 0;
    float time_ = 0;
};