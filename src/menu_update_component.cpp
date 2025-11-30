#include "menu_update_component.hpp"
#include "player_update_component.hpp"
#include "level_update_component.hpp"
#include "sound_engine.hpp"


MenuUpdateComponent::MenuUpdateComponent(sf::RenderWindow* window)
    : window_{window}
{

}

MenuUpdateComponent::~MenuUpdateComponent()
{

}

void MenuUpdateComponent::handleInput()
{
    for (const auto& event : input_receiver_.getEvents()) {
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::F1 && is_visible_) {
                if (SoundEngine::getInstance().isMusicPlaying()) {
                    SoundEngine::getInstance().stopMusic();
                }
                window_->close();
            }
        }
        if (event.type == sf::Event::KeyReleased) {
            if (event.key.code == sf::Keyboard::Escape) {
                is_visible_ = !is_visible_;
                *is_paused_ = !(*is_paused_);
                if (is_game_over_) {
                    is_game_over_ = false;
                }
                if (!*is_paused_) {
                    SoundEngine::getInstance().resumeMusic();
                    SoundEngine::getInstance().playClick();
                } else {
                    SoundEngine::getInstance().pauseMusic();
                    SoundEngine::getInstance().playClick(); 
                }
            }
        }
    }
    input_receiver_.clearEvents();
}

sf::FloatRect* MenuUpdateComponent::getPositionPointer()
{
    return &position_;
}

bool* MenuUpdateComponent::getGameOverPointer()
{
    return &is_game_over_;
}

InputReceiver* MenuUpdateComponent::getInputReceiver()
{
    return &input_receiver_;
}

void MenuUpdateComponent::update(float elapsed_time)
{
    handleInput();

    if (*is_paused_ && !is_visible_) {
        is_visible_ = true;
        is_game_over_ = true;
    }

    if (is_visible_) {
        position_.left = player_position->getPosition().x - position_.width / 2;
        position_.top = player_position->getPosition().y - position_.height / 2;
    } else {
        position_.left = -999;
        position_.top = -999;
    }
}

void MenuUpdateComponent::assemble(std::shared_ptr<LevelUpdateComponent> level_update_component,
    std::shared_ptr<PlayerUpdateComponent> player_update_component)
{
    player_position = player_update_component->getPositionPointer();
    is_paused_ = level_update_component->getIsPausedPointer();

    position_.height = 75;
    position_.width = 75;

    SoundEngine::getInstance().startMusic();
    SoundEngine::getInstance().pauseMusic();
}