#include "factory.hpp"
#include "level_update_component.hpp"
#include "player_graphics_component.hpp"
#include "player_update_component.hpp"
#include "input_dispatcher.hpp"
#include "camera_update_component.hpp"
#include "camera_graphics_component.hpp"
#include "platform_update_component.hpp"
#include "platform_graphics_component.hpp"
#include "menu_update_component.hpp"
#include "menu_graphics_component.hpp"
#include "rain_graphics_component.hpp"
#include "fireball_graphics_component.hpp"
#include "fireball_update_component.hpp"

#include <iostream>
#include <memory>

Factory::Factory(sf::RenderWindow* window)
    : window_{window},texture_{new sf::Texture{}}
{
    if (!texture_->loadFromFile("assets/graphics/texture.png")) {
        std::cout << "Texture not loaded!" << std::endl;
        return;
    }
}

Factory::~Factory()
{

}

void Factory::loadLevel(std::vector<GameObject>& game_objects, sf::VertexArray& canvas, InputDispatcher& input_dispatcher)
{
    GameObject level;
    std::shared_ptr<LevelUpdateComponent> level_update_component = std::make_shared<LevelUpdateComponent>();
    level.addComponent(level_update_component);
    game_objects.push_back(level);

    GameObject player;
    std::shared_ptr<PlayerUpdateComponent> player_update_component = 
        std::make_shared<PlayerUpdateComponent>();
    player_update_component->assemble(level_update_component, nullptr);
    player.addComponent(player_update_component);
    input_dispatcher.registerNewInputReceiver(player_update_component->getInputReceiver());

    std::shared_ptr<PlayerGraphicsComponent> player_graphics_component = 
        std::make_shared<PlayerGraphicsComponent>();
    player_graphics_component->assemble(canvas, player_update_component, 
        sf::IntRect{PLAYER_TEX_LEFT, PLAYER_TEX_TOP, PLAYER_TEX_WIDTH, PLAYER_TEX_HEIGHT});
    player.addComponent(player_graphics_component);
    game_objects.push_back(player);

    level_update_component->assemble(nullptr, player_update_component);

    for (int32_t i = 0; i < 8; ++i) {
        GameObject platform;
        std::shared_ptr<PlatformUpdateComponent> platform_update_component = 
            std::make_shared<PlatformUpdateComponent>();
        platform_update_component->assemble(nullptr, player_update_component);
        platform.addComponent(platform_update_component);

        std::shared_ptr<PlatformGraphicsComponent> platform_graphics_component = 
            std::make_shared<PlatformGraphicsComponent>();
        platform_graphics_component->assemble(canvas, platform_update_component, 
            sf::IntRect{PLATFORM_TEX_LEFT, PLATFORM_TEX_TOP, 
                                    PLATFORM_TEX_WIDTH, PLATFORM_TEX_HEIGHT});
        platform.addComponent(platform_graphics_component);
        game_objects.push_back(platform);

        level_update_component->addPlatformPosition(platform_update_component->getPositionPointer());
    }

    for (int32_t i = 0; i < 12; ++i) {
        GameObject fireball;
        auto fireball_update_component = std::make_shared<FireballUpdateComponent>(level_update_component->getIsPausedPointer());
        fireball_update_component->assemble(level_update_component, player_update_component);
        fireball.addComponent(fireball_update_component);

        auto fireball_graphics_component = std::make_shared<FireballGraphicsComponent>();
        fireball_graphics_component->assemble(canvas, fireball_update_component, 
            sf::IntRect{870, 0, 32, 32});
        fireball.addComponent(fireball_graphics_component);
        game_objects.push_back(fireball);
    }

    int32_t rain_coverage_per_object = 25;
    int32_t area_to_cover = 350;

    for (int32_t h = -area_to_cover / 2; h < area_to_cover / 2; h+= rain_coverage_per_object) {
        for (int32_t v = -area_to_cover / 2; v < area_to_cover / 2; v += rain_coverage_per_object) {
            GameObject rain;
            std::shared_ptr<RainGraphicsComponent> rain_graphics_component = 
                std::make_shared<RainGraphicsComponent>(player_update_component->getPositionPointer(), h, v, rain_coverage_per_object);
            rain_graphics_component->assemble(canvas, nullptr, 
                sf::IntRect{RAIN_TEX_LEFT, RAIN_TEX_TOP, RAIN_TEX_WIDTH, RAIN_TEX_HEIGHT});
            rain.addComponent(rain_graphics_component);
            game_objects.push_back(rain);
        }
    }

    const float width = static_cast<float>(sf::VideoMode::getDesktopMode().width);
    const float height = static_cast<float>(sf::VideoMode::getDesktopMode().height);
    const float ratio = width / height;

    GameObject camera;
    std::shared_ptr<CameraUpdateComponent> camera_update_component = 
        std::make_shared<CameraUpdateComponent>();
    camera_update_component->assemble(nullptr, player_update_component);
    camera.addComponent(camera_update_component);
    std::shared_ptr<CameraGraphicsComponent> camera_graphics_component = 
        std::make_shared<CameraGraphicsComponent>(window_, texture_,
                                                    sf::Vector2f{CAM_VIEW_WIDTH, CAM_VIEW_WIDTH / ratio},
                                                sf::FloatRect{CAM_SCREEN_RATIO_LEFT, CAM_SCREEN_RATIO_TOP,
                                                CAM_SCREEN_RATIO_WIDTH, CAM_SCREEN_RATIO_HEIGHT});
    camera_graphics_component->assemble(canvas, camera_update_component, 
                                       sf::IntRect{CAM_TEX_LEFT, CAM_TEX_TOP, CAM_TEX_WIDTH, CAM_TEX_HEIGHT});
    camera.addComponent(camera_graphics_component);
    game_objects.push_back(camera);
    level_update_component->connectToCameraTime(camera_graphics_component->getTimeConnection());

    GameObject map_camera;
    std::shared_ptr<CameraUpdateComponent> map_camera_update_component = 
        std::make_shared<CameraUpdateComponent>();
    map_camera_update_component->assemble(nullptr, player_update_component);
    map_camera.addComponent(map_camera_update_component);

    input_dispatcher.registerNewInputReceiver(map_camera_update_component->getInputReceiver());

    std::shared_ptr<CameraGraphicsComponent> map_camera_graphics_component = 
        std::make_shared<CameraGraphicsComponent>(
            window_, texture_, sf::Vector2f{MAP_CAM_VIEW_WIDTH, MAP_CAM_VIEW_HEIGHT / ratio},
            sf::FloatRect{MAP_CAM_SCREEN_RATIO_LEFT, MAP_CAM_SCREEN_RATIO_TOP,
            MAP_CAM_SCREEN_RATIO_WIDTH, MAP_CAM_SCREEN_RATIO_HEIGHT}
        );
    map_camera_graphics_component->assemble(canvas, map_camera_update_component, 
        sf::IntRect{MAP_CAM_TEX_LEFT, MAP_CAM_TEX_TOP, MAP_CAM_TEX_WIDTH, MAP_CAM_TEX_HEIGHT});
    map_camera.addComponent(map_camera_graphics_component);
    game_objects.push_back(map_camera);

    GameObject menu;
    std::shared_ptr<MenuUpdateComponent> menu_update_component = 
        std::make_shared<MenuUpdateComponent>(window_);
    menu_update_component->assemble(level_update_component, player_update_component);
    input_dispatcher.registerNewInputReceiver(menu_update_component->getInputReceiver());
    menu.addComponent(menu_update_component);
    std::shared_ptr<MenuGraphicsComponent> menu_graphics_component = 
        std::make_shared<MenuGraphicsComponent>();
    menu_graphics_component->assemble(canvas, menu_update_component, 
        sf::IntRect{TOP_MENU_TEX_LEFT, TOP_MENU_TEX_TOP, TOP_MENU_TEX_WIDTH, TOP_MENU_TEX_HEIGHT});
    menu.addComponent(menu_graphics_component);
    game_objects.push_back(menu);
}