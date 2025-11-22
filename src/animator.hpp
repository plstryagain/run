#pragma once

#include <SFML/Graphics.hpp>

class Animator
{
public:
    Animator(int32_t left_offset, int32_t top_offset, int32_t frame_count,
             int32_t texture_width, int32_t texture_height, int32_t fps);
    ~Animator();
    Animator(const Animator& other) = delete;
    void operator=(const Animator& other) = delete;

public:
    sf::IntRect* getCurrentFrame(bool reversed);

private:
    sf::IntRect source_rect_;
    int32_t left_offset_;
    int32_t frame_count_;
    int32_t current_frame_;
    int32_t frame_period_;
    int32_t frame_width_;
    int32_t fps_ = 12;
    sf::Clock clock_;
};