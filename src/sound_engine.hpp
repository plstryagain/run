#pragma once

#include <SFML/Audio.hpp>

class SoundEngine
{
public:
    static SoundEngine& getInstance()
    {
        static SoundEngine instance;
        return instance;
    }
    ~SoundEngine();
    SoundEngine(const SoundEngine& other) = delete;
    void operator=(const SoundEngine& other) = delete;

private:
    SoundEngine();

public:
    bool isMusicPlaying() const;
    void startMusic();
    void pauseMusic();
    void resumeMusic();
    void stopMusic();
    void playClick();
    void playJump();
    void playFireballLaunch(sf::Vector2f player_position, sf::Vector2f sound_location);

private:
    bool is_music_playing_;
    sf::Music music_;
    sf::SoundBuffer click_sound_buffer_;
    sf::Sound click_sound_;
    sf::SoundBuffer jump_sound_buffer_;
    sf::Sound jump_sound_;
    sf::SoundBuffer fireball_launch_buffer_;
    sf::Sound fireball_launch_sound_;
};