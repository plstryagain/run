#include "platform_update_component.hpp"
#include "player_update_component.hpp"

PlatformUpdateComponent::PlatformUpdateComponent()
{

}

PlatformUpdateComponent::~PlatformUpdateComponent()
{

}

sf::FloatRect* PlatformUpdateComponent::getPositionPointer()
{
    return &position_;
}

void PlatformUpdateComponent::update(float elapsed_time)
{
    if (position_.intersects(*player_position_)) {
        sf::Vector2f player_feet{
            player_position_-> left + player_position_->width / 2,
            player_position_->top + player_position_->height
        };
        sf::Vector2f player_right{
            player_position_->left + player_position_->width,
            player_position_->top + player_position_->height / 2
        };
        sf::Vector2f player_left{
            player_position_->left,
            player_position_->top + player_position_->height / 2
        };
        sf::Vector2f player_head{
            player_position_->left + player_position_->width / 2,
            player_position_->top
        };
        if (position_.contains(player_feet)) {
            if (player_feet.y > position_.top) {
                player_position_->top = position_.top - player_position_->height;
                *is_player_grounded_ = true;
            }
        } else if (position_.contains(player_right)) {
            player_position_->left = position_.left - player_position_->width;
        } else if (position_.contains(player_left)) {
            player_position_->left = position_.left + position_.width;
        } else if (position_.contains(player_head)) {
            player_position_->top = position_.top + position_.height;
        }
    }
}

void PlatformUpdateComponent::assemble(std::shared_ptr<LevelUpdateComponent> level_update_component,
                                        std::shared_ptr<PlayerUpdateComponent> player_update_component)
{
    player_position_ = player_update_component->getPositionPointer();
    is_player_grounded_ = player_update_component->getGroundedPointer();
}