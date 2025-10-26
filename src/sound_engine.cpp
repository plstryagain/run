#include "sound_engine.hpp"

SoundEngine::SoundEngine()
{
    click_sound_buffer_.loadFromFile("assets/sound/click.wav");
    click_sound_.setBuffer(click_sound_buffer_);
    jump_sound_buffer_.loadFromFile("assets/sound/jump.wav");
    jump_sound_.setBuffer(jump_sound_buffer_);
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