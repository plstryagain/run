#include "sound_engine.hpp"

SoundEngine::SoundEngine()
{
    click_sound_buffer_.loadFromFile("assets/sound/click.wav");
    click_sound_.setBuffer(click_sound_buffer_);
    jump_sound_buffer_.loadFromFile("assets/sound/jump.wav");
    jump_sound_.setBuffer(jump_sound_buffer_);

    sf::Listener::setDirection(1.f, 0.f, 0.f);
    sf::Listener::setUpVector(1.f, 1.f, 0.f);
    sf::Listener::setGlobalVolume(100.f);

    fireball_launch_buffer_.loadFromFile("assets/sound/fireballLaunch.wav");
    fireball_launch_sound_.setBuffer(fireball_launch_buffer_);
}

SoundEngine::~SoundEngine()
{

}

bool SoundEngine::isMusicPlaying() const
{
    return is_music_playing_;
}

void SoundEngine::startMusic()
{
    music_.openFromFile("assets/music/music.wav");
    music_.play();
    music_.setLoop(true);
    is_music_playing_ = true;
}

void SoundEngine::pauseMusic()
{
    music_.pause();
    is_music_playing_ = false;
}

void SoundEngine::resumeMusic()
{
    music_.play();
    is_music_playing_ = true;
}

void SoundEngine::stopMusic()
{
    music_.stop();
    is_music_playing_ = false;
}

void SoundEngine::playClick()
{
    click_sound_.play();
}

void SoundEngine::playJump()
{
    jump_sound_.play();
}

void SoundEngine::playFireballLaunch(sf::Vector2f player_position, sf::Vector2f sound_location)
{
    fireball_launch_sound_.setRelativeToListener(true);
    if (player_position.x > sound_location.x) {
        sf::Listener::setPosition(0, 0, 0.f);
        fireball_launch_sound_.setPosition(-100, 0, 0.f);
        fireball_launch_sound_.setMinDistance(100);
        fireball_launch_sound_.setAttenuation(0);
    } else {
        sf::Listener::setPosition(0, 0, 0.f);
        fireball_launch_sound_.setPosition(100, 0, 0.f);
        fireball_launch_sound_.setMinDistance(100);
        fireball_launch_sound_.setAttenuation(0);
    }
    fireball_launch_sound_.play();
}