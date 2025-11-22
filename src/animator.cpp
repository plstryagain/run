#include "animator.hpp"

Animator::Animator(int32_t left_offset, int32_t top_offset, int32_t frame_count,
                    int32_t texture_width, int32_t texture_height, int32_t fps)
{
    left_offset_ = left_offset;
    current_frame_ = 0;
    frame_count_ = frame_count;
    if (frame_count_ == 0) {
        frame_count_ = 1;
    }
    frame_width_ = static_cast<float>(texture_width) / frame_count; 
    source_rect_.left = left_offset;
    source_rect_.top = top_offset;
    source_rect_.width = frame_width_;
    source_rect_.height = texture_height;
    fps_ = fps;
    if (fps_ == 0) {
        fps_ = 1;
    }
    frame_period_ = 1000 / fps;
    clock_.restart();
}

Animator::~Animator()
{

}

sf::IntRect* Animator::getCurrentFrame(bool reversed)
{
    if (clock_.getElapsedTime().asMilliseconds() > frame_period_) {
        ++current_frame_;
        if (current_frame_ >= frame_count_ + reversed) {
            current_frame_ = 0 + reversed;
        }
        clock_.restart();
    }
    source_rect_.left = left_offset_ + current_frame_ * frame_width_;
    return &source_rect_;
}