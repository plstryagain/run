#pragma once

#include "input_dispatcher.hpp"
#include "game_object.hpp"

#include <SFML/Graphics.hpp>

class Factory
{
public:
    Factory(sf::RenderWindow* window);
    ~Factory();
    Factory(const Factory& other) = delete;
    void operator=(const Factory& other) = delete;

public:
    void loadLevel(std::vector<GameObject>& game_objects, sf::VertexArray& canvas, InputDispatcher& input_dispatcher);
    sf::Texture* texture_;

private:
    sf::RenderWindow* window_;

    inline static constexpr int32_t PLAYER_TEX_LEFT = 0;
    inline static constexpr int32_t PLAYER_TEX_TOP = 0;
    inline static constexpr int32_t PLAYER_TEX_WIDTH = 80;
    inline static constexpr int32_t PLAYER_TEX_HEIGHT = 96;
    inline static constexpr float CAM_VIEW_WITH = 300.f;
    inline static constexpr float CAM_SCREEN_RATIO_LEFT = 0.f;
    inline static constexpr float CAM_SCREEN_RATIO_TOP = 0.f;
    inline static constexpr float CAM_SCREEN_RATIO_WIDTH = 1.f;
    inline static constexpr float CAM_SCREEN_RATIO_HEIGHT = 1.f;
    inline static constexpr int32_t CAM_TEX_LEFT = 610;
    inline static constexpr int32_t CAM_TEX_TOP = 36;
    inline static constexpr int32_t CAM_TEX_WIDTH = 40;
    inline static constexpr int32_t CAM_TEX_HEIGHT = 30;
    inline static constexpr float MAP_CAM_SCREEN_RATIO_LEFT = 0.3f;
    inline static constexpr float MAP_CAM_SCREEN_RATIO_TOP = 0.84f;
    inline static constexpr float MAP_CAM_SCREEN_RATIO_WIDTH = 0.4f;
    inline static constexpr float MAP_CAM_SCREEN_RATIO_HEIGHT = 0.15f;
    inline static constexpr int32_t MAP_CAM_VIEW_WIDTH = 800.f;
    inline static constexpr int32_t MAP_CAM_VIEW_HEIGHT = MAP_CAM_VIEW_WIDTH / 2;
    inline static constexpr int32_t MAP_CAM_TEX_LEFT = 665;
    inline static constexpr int32_t MAP_CAM_TEX_TOP = 0;
    inline static constexpr int32_t MAP_CAM_TEX_WIDTH = 100;
    inline static constexpr int32_t MAP_CAM_TEX_HEIGHT = 70;
    inline static constexpr int32_t PLATFORM_TEX_LEFT = 607;
    inline static constexpr int32_t PLATFORM_TEX_TOP = 0;
    inline static constexpr int32_t PLATFORM_TEX_WIDTH = 10;
    inline static constexpr int32_t PLATFORM_TEX_HEIGHT = 10;
    inline static constexpr int32_t TOP_MENU_TEX_LEFT = 770;
    inline static constexpr int32_t TOP_MENU_TEX_TOP = 0;
    inline static constexpr int32_t TOP_MENU_TEX_WIDTH = 100;
    inline static constexpr int32_t TOP_MENU_TEX_HEIGHT = 100;
    inline static constexpr int32_t RAIN_TEX_LEFT = 0;
    inline static constexpr int32_t RAIN_TEX_TOP = 100;
    inline static constexpr int32_t RAIN_TEX_WIDTH = 100;
    inline static constexpr int32_t RAIN_TEX_HEIGHT = 100;

};